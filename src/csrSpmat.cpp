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
  row_ptr_.resize(numRows_+1);

  // Clean memory for the values
  // values_ = 0.0;

  // Fill-in the sparse matrix with the positions of the non-null values
  // (number of cells plus their neighbours)
  nz = 0;
  for (unsigned int i=0;i<mesh.nCells_;i++)
  {
    row_ptr_[i] = nz;
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
    for (unsigned int j=row_ptr_[i];j<nz-1;j++)
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
  row_ptr_[numRows_] = nz;
}

// Constructor with matrix size and name
csrSpmat::csrSpmat(unsigned int numRows, unsigned int numCols, const std::string name)
{
  numRows_ = numRows;
  numCols_ = numCols;
  name_ = name;
}

// Returns the sparsity of the matrix
double csrSpmat::sparsity() const
{
  return (1.0 - ((double)numNZ_ / ((double)(numRows_ * numCols_))));
}

// Returns the number of non-zero values in row i
unsigned int csrSpmat::getNumNZ(const unsigned int &i) const
{
      return (row_ptr_[i+1]-row_ptr_[i]);
}

// Returns the j-th non-zero value in row i (j is not the column)
double csrSpmat::getNZValue(const unsigned int &i, const unsigned int &j) const
{
      return values_[row_ptr_[i]+j];
}

// Returns the column of the j-th non-zero value in row i (j is not the column)
unsigned int csrSpmat::getNZColumn(const unsigned int &i, const unsigned int &j) const
{
      return columns_[row_ptr_[i]+j];
}

// Sets a value to position (i,j) if exists, otherwise inserts a new value
void csrSpmat::setValue(const unsigned int& i, const unsigned int& j, const double& val)
{
  for (unsigned int k=row_ptr_[i];k<row_ptr_[i+1];k++)
  {
    if (columns_[k] == j)
    {
      values_[k] = val;
      return;
    }
  }
  // Throws exception to stop the program
  throw std::runtime_error("Error: invalid column for sparse structure matrix");
}

// Adds a value to position (i,j) if exists, otherwise inserts a new value
void csrSpmat::addValue(const unsigned int& i, const unsigned int& j, const double& val)
{
  for (unsigned int k=row_ptr_[i];k<row_ptr_[i+1];k++)
  {
    if (columns_[k] == j)
    {
      values_[k] += val;
      return;
    }
  }
  // Throws exception to stop the program
  throw std::runtime_error("Error: invalid column for sparse structure matrix");
}

// Subtracts a value to position (i,j) if exists, otherwise inserts a new value
void csrSpmat::subValue(const unsigned int& i, const unsigned int& j, const double& val)
{
  for (unsigned int k=row_ptr_[i];k<row_ptr_[i+1];k++)
  {
    if (columns_[k] == j)
    {
      values_[k] -= val;
      return;
    }
  }
  // Throws exception to stop the program
  throw std::runtime_error("Error: invalid column for sparse structure matrix");
}

// Deletes the value in position (i,j) if exists, otherwise does nothing
void csrSpmat::delValue(const unsigned int& i, const unsigned int& j)
{
  for (unsigned int k=row_ptr_[i];k<row_ptr_[i+1];k++)
  {
    if (columns_[k] == j)
    {
      values_[k] = 0.0;
      return;
    }
  }
  // Throws exception to stop the program
  throw std::runtime_error("Error: invalid column for sparse structure matrix");
}

// Returns the value in position (i,j) if exists, otherwise returns 0
double csrSpmat::getValue(const unsigned int& i, const unsigned int& j) const
{
  for (unsigned int k=row_ptr_[i];k<row_ptr_[i+1];k++)
  {
    if (columns_[k] == j)
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
    for (unsigned int j=row_ptr_[i];j<row_ptr_[i+1];j++)
    {
      id_column = columns_[j];
      denseMatrix[i][id_column] = values_[j];
    }
  }
  return denseMatrix;
}

// Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
double csrSpmat::vecRowMul(const unsigned int& i, const std::vector<double>& vecPhi) const
{
  double sumProdRow = 0.0;
  unsigned int j = row_ptr_[i];
  while (j<row_ptr_[i+1])
  {
    sumProdRow += values_[j] * vecPhi[columns_[j]];
    j += 1;
  }
  return sumProdRow;
}

// Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double excluding the diagonal
double csrSpmat::vecRowMulNoDiagonal(const unsigned int& i,const std::vector<double>& vecPhi) const
{
  double sumProdRow = 0.0;
  unsigned int j = row_ptr_[i];
  while (j<row_ptr_[i+1])
  {
    if (i != columns_[j])
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
//   unsigned int j = row_ptr_[i];
//   while (j<row_ptr_[i+1])
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
  std::vector<double> v(vec.size());
  for (unsigned int i=0;i<A.numRows_;i++)
  {
    v[i] = 0.0;
    for (unsigned int j=A.row_ptr_[i]; j<A.row_ptr_[i+1]; j++)
    {
      v[i] += A.values_[j] * vec[A.columns_[j]];
    }
  }
  return v;
}

// Multiplication operator (mat-mat)
csrSpmat operator*(const csrSpmat& A, const csrSpmat& B)
{
  csrSpmat C = csrSpmat(A.numRows_, B.numCols_);
  double val;
  for (unsigned int i=0;i<A.numRows_;i++)
  {
    for (unsigned int j=0; j<B.numCols_; j++)
    {
      val = 0.0;
      for (unsigned int k=A.row_ptr_[i]; k<A.row_ptr_[i+1]; k++)
      {
        for (unsigned int l=0; l<B.row_ptr_.size(); l++)
        {
          for (unsigned int m=B.row_ptr_[l]; m<B.row_ptr_[l+1]; m++)
          {
            if (B.columns_[m] == j && B.columns_[m] == A.columns_[k])
            {
              val += A.values_[k] * B.values_[m];
            }
          }
        }
      }
      C.addValue(i,j,val);
    }
  }
  return C;
}