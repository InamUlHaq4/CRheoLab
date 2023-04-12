#include "csrSpmat.h"
#include "Mesh.h"
#include <iostream>

// Constructor
// Constructs an empty sparse matrix and allocates memory for the rows
csrSpmat::csrSpmat(Mesh& mesh)
{
  // Store number of rows and columns
  numRows_ = mesh.nCells_;
  numCols_ = mesh.nCells_;

  // Declaration of variables
  unsigned int nz, aux;
  const Cell *neigh_ptr, *owner_ptr;

  // Determine the total number of non-zeros values (number of cells plus its neighbours)
  nz = 0;
  for (unsigned int i=0;i<mesh.nCells_;i++)
  {
    nz++;
    for (unsigned int j=0;j<mesh.cellList_[i].cellFaces_.size();j++) // getter?
    {
      neigh_ptr = mesh.cellList_[i].cellFaces_[j]->getNeighbour();
      if(neigh_ptr != NULL)
      {
         nz++;
      }
    }
  }

  // Store number of non-null values
  numNZ_ = nz;

  // Allocate memory for the values
  values_.resize(nz);
  columns_.resize(nz);
  rowPtr_.resize(numRows_+1);

  // Clean memory for the values
  // values_ = 0.0;

  // Fill-in the sparse matrix with the positions of the non-null values
  // (number of cells plus their neighbours)
  nz = 0;
  for (unsigned int i=0;i<mesh.nCells_;i++)
  {
    rowPtr_[i] = nz;
    columns_[nz] = i;
    nz++;
    for (unsigned int j=0;j<mesh.cellList_[i].cellFaces_.size();j++) // getter?
    {
      neigh_ptr = mesh.cellList_[i].cellFaces_[j]->getNeighbour();
      owner_ptr = mesh.cellList_[i].cellFaces_[j]->getOwner();
      if(neigh_ptr != NULL)
      {
        if(neigh_ptr->ID_ == i)
        {
          columns_[nz] = owner_ptr->ID_;
          nz++;
        }
        else //if(owner_ptr.ID_ == i)
        {
          columns_[nz] = neigh_ptr->ID_;
          nz++;
        }
      }
    }
    // Reorder the columns
    for (unsigned int j=rowPtr_[i];j<nz-1;j++)
    {
      for (unsigned int k=j+1;k<nz-1;k++)
      {
        if (columns_[j]>columns_[k])
        {
          aux = columns_[j];
          columns_[j] = columns_[k];
          columns_[k] = aux;
        }
      }
    }
  }
  rowPtr_[numRows_] = nz;
}

// Constructor with matrix size and name
csrSpmat::csrSpmat(unsigned int numRows, unsigned int numCols, const std::string name)
{
  numRows_ = numRows;
  numCols_ = numCols;
  name_ = name;

  rowPtr_.resize(numRows+1,0);
}

// Returns the sparsity of the matrix
double csrSpmat::sparsity() const
{
  return (1.0 - ((double)numNZ_ / ((double)(numRows_ * numCols_))));
}

// Returns the number of non-zero values for the row
unsigned int csrSpmat::getNumNZ(const unsigned int &row) const
{
  return (rowPtr_[row+1]-rowPtr_[row]);
}

// Returns the i-th non-zero value for the row 
double csrSpmat::getNZValue(const unsigned int &row, const unsigned int &i) const
{
  return values_[rowPtr_[row]+i];
}

// Returns the colum of the i-th non-zero value for the row 
unsigned int csrSpmat::getNZColumn(const unsigned int &row, const unsigned int &i) const
{
  return columns_[rowPtr_[row]+i];
}

// Sets a value to position (row,col) if exists, otherwise inserts a new value
void csrSpmat::setValue(const unsigned int& row, const unsigned int& col, const double& val)
{
  checkPos(this,row,col);
  for (unsigned int i=rowPtr_[row]; i<rowPtr_[row+1]; i++)
  {
    if (columns_[i] == col)
    {
      values_[i] = val;
      std::cout << values_ << std::endl;
      return;
    } 
  }
  // if the value does not exist, it adds it.
  this->addValue(row,col,val);
}


// Adds a value to position (row,col) if exists, otherwise inserts a new value
void csrSpmat::addValue(const unsigned int& row, const unsigned int& col, const double& val)
{
  checkPos(this,row,col);

  if (row == 0)
  {
    columns_.insert(columns_.begin()+col, col);
    values_.insert(values_.begin()+col, val);
    for (int m = row + 1; m < rowPtr_.size(); m++) 
    {
      rowPtr_[m]++;
    }
    return;
  }

  // if the row is empty
  if (rowPtr_[row] == rowPtr_[row+1])
  {
    columns_.insert(columns_.begin()+rowPtr_[row], col);
    values_.insert(values_.begin()+rowPtr_[row], val);
    for (int m = row + 1; m < rowPtr_.size(); m++) 
    {
      rowPtr_[m]++;
    }
    return;
  }
  
  for (unsigned int i=rowPtr_[row]; i<rowPtr_[row+1]; i++)
  {
    // value exists before the first non zero value in that row
    if (columns_[i] > col)
    {
      columns_.insert(columns_.begin()+i, col);
      values_.insert(values_.begin()+i, val);
      for (int m = row + 1; m < rowPtr_.size(); m++) 
      {
        rowPtr_[m]++;
      }
      return;
    } 
    // position already has a non zero value
    if (columns_[i] == col)
    {
      values_[i] += val;
      return;
    } 
    // value exists between the 1st and last non zero value in that row
    if (columns_[i] < col && col < rowPtr_[row+1])
    {
      columns_.insert(columns_.begin()+i+1, col);
      values_.insert(values_.begin()+i+1, val);
      for (int m = row + 1; m < rowPtr_.size(); m++) 
      {
        rowPtr_[m]++;
      }
      return;
    }
  }
}

// Subtracts a value to position (row,col) if exists, otherwise inserts a new value
void csrSpmat::subValue(const unsigned int& row, const unsigned int& col, const double& val)
{
  checkPos(this,row,col);
  for (unsigned int k=rowPtr_[row];k<rowPtr_[row+1];k++)
  {
    if (columns_[k] == col)
    {
      values_[k] -= val;
      return;
    }
  }
  // Throws exception to stop the program
  throw std::runtime_error("Error: invalid column for sparse structure matrix");
}

// Deletes the value in position (row,col) if exists, otherwise does nothing
void csrSpmat::delValue(const unsigned int& row, const unsigned int& col)
{
  checkPos(this,row,col);
  for (unsigned int k=rowPtr_[row];k<rowPtr_[row+1];k++)
  {
    if (columns_[k] == col)
    {
      values_[k] = 0.0;
      return;
    }
  }
}

// Returns the value in position (row,col) if exists, otherwise returns 0
double csrSpmat::getValue(const unsigned int& row, const unsigned int& col) const
{
  checkPos(this,row,col);
  for (unsigned int k=rowPtr_[row];k<rowPtr_[row+1];k++)
  {
    if (columns_[k] == col)
    {
      return values_[k];
    }
  }
  return 0.0;
}

// Returns the sparse matrix in a dense format as a vector of vectors
std::vector< std::vector<double> > csrSpmat::dense() const
{
  std::vector< std::vector<double> > denseMatrix(numCols_, std::vector<double>(numCols_));
  unsigned int id_column = 0;
  for (unsigned int i=0;i<numRows_;i++)
  {
    for (unsigned int j=rowPtr_[i];j<rowPtr_[i+1];j++)
    {
      id_column = columns_[j];
      denseMatrix[i][id_column] = values_[j];
    }
  }
  return denseMatrix;
}

// Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
double csrSpmat::vecRowMul(const unsigned int& row, const std::vector<double>& vecPhi) const
{
  double sumProdRow = 0.0;
  unsigned int j = rowPtr_[row];
  while (j<rowPtr_[row+1])
  {
    sumProdRow += values_[j] * vecPhi[columns_[j]];
    j += 1;
  }
  return sumProdRow;
}

// Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double excluding the diagonal
double csrSpmat::vecRowMulNoDiagonal(const unsigned int& row,const std::vector<double>& vecPhi) const
{
  double sumProdRow = 0.0;
  unsigned int j = rowPtr_[row];
  while (j<rowPtr_[row+1])
  {
    if (row != columns_[j])
    {
      sumProdRow += values_[j] * vecPhi[columns_[j]];
    }
    j += 1;
  }
  return sumProdRow;
}

// Returns the sum of the products of a double for the elements of the iRow matrix row
// double valueProduct(const unsigned int& i, const double& val)
// {
//   double sumProdRow = 0.0;
//   unsigned int j = rowPtr_[i];
//   while (j<rowPtr_[i+1])
//   {
//     sumProdRow += values_[j] * val;
//     j += 1;
//   }
//   return sumProdRow;
// }

// Addition operator
csrSpmat operator+(const csrSpmat& A,const csrSpmat& B)
{
  csrSpmat C = A;
  for(unsigned int i=0;i<B.getNumRows();i++)
  {
    for(unsigned int j=0;j<B.getNumNZ(i);j++)
    {
      C.addValue(i,B.getNZColumn(i,j),B.getNZValue(i,j));
    }
  }
  return C;
}
// Addition operator (pointer)
csrSpmat* operator+(const csrSpmat& A,const csrSpmat* B)
{
  csrSpmat* C = new csrSpmat(A);
  for(unsigned int i=0;i<B->getNumRows();i++)
  {
    for(unsigned int j=0;j<B->getNumNZ(i);j++)
    {
      C->addValue(i,B->getNZColumn(i,j),B->getNZValue(i,j));
    }
  }
  return C;
}

// Subtraction operator
csrSpmat operator-(const csrSpmat& A,const csrSpmat& B)
{
  csrSpmat C = A;
  for(unsigned int i=0;i<B.getNumRows();i++)
  {
    for(unsigned int j=0;j<B.getNumNZ(i);j++)
    {
      C.subValue(i,B.getNZColumn(i,j),B.getNZValue(i,j));
    }
  }
  return C;
}
// Subtraction operator (pointer)
csrSpmat* operator-(const csrSpmat& A,const csrSpmat* B)
{
  csrSpmat* C = new csrSpmat(A);
  for(unsigned int i=0;i<B->getNumRows();i++)
  {
    for(unsigned int j=0;j<B->getNumNZ(i);j++)
    {
      C->subValue(i,B->getNZColumn(i,j),B->getNZValue(i,j));
    }
  }

  return C;
}

// Multiplication operator (mat-scalar)
csrSpmat operator*(const csrSpmat& A, const double& val)
{
  csrSpmat C = A;
  for(unsigned int i=0; i<C.numNZ_;i++)
  {
    C.values_[i] *= val;
  }
  return C;
}
// Multiplication operator (mat-scalar) (pointer)
csrSpmat* operator*(const csrSpmat& A, const double* val)
{
  csrSpmat* C = new csrSpmat(A);
  for(unsigned int i=0; i<C->numNZ_;i++)
  {
    C->values_[i] *= *val;
  }
  return C;
}

// Multiplication operator (mat-vec)
std::vector<double> operator*(const csrSpmat& A, const std::vector<double>& vec)
{
  checkProd(A,vec);
  std::vector<double> v(vec.size());
  for (unsigned int i=0;i<A.numRows_;i++)
  {
    v[i] = 0.0;
    for (unsigned int j=A.rowPtr_[i]; j<A.rowPtr_[i+1]; j++)
    {
      v[i] += A.values_[j] * vec[A.columns_[j]];
    }
  }
  return v;
}

// Multiplication operator (mat-vec) (pointer)
std::vector<double>* operator*(const csrSpmat* A, const std::vector<double>& vec)
{
  std::vector<double>* v = new std::vector<double>;
  *v = *A * vec;
  return v;
}

// Multiplication operator (mat-vec) (pointer)
std::vector<double>* operator*(const csrSpmat& A, const std::vector<double>* vec)
{
  std::vector<double>* v = new std::vector<double>;
  *v = A * *vec;
  return v;
}

// Multiplication operator (mat-mat)
csrSpmat operator*(const csrSpmat& A, const csrSpmat& B)
{
  checkProd(A,B);
  csrSpmat C(A.numRows_,B.numCols_);
  double val;
  // loop over each row of A mat
  for (unsigned int i=0; i<A.numRows_; i++)
  {
    // loop over each column of B mat
    for (unsigned int j=0; j<B.numCols_; j++)
    {
      val = 0.0;
      // loop over each non zero entry of i row of A mat
      for (unsigned int k=A.rowPtr_[i]; k<A.rowPtr_[i+1]; k++)
      {
        // loop over each non zero entry in A.columns_[k] col of B mat before or at column j
        for (unsigned int l=B.rowPtr_[A.columns_[k]]; l<B.rowPtr_[A.columns_[k]+1]; l++)
        {
          if (B.columns_[l] == j)
          {
            val += A.values_[k] * B.values_[l];
            break;
          }
        }
      }
      if (val != 0.0)
      {
        C.addValue(i,j,val);
      }
    }
  }
  return C;
}

// Multiplication operator (mat-mat) (pointer)
csrSpmat* operator*(const csrSpmat& A,const csrSpmat* B)
{
  csrSpmat* C = new csrSpmat();
  *C = A * *B;
  return C;
}