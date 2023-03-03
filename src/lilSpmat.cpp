#include "lilSpmat.h"
#include <iostream>

// Constructor
// Same as before but with name
lilSpmat::lilSpmat(unsigned int numRows, unsigned int numCols, const std::string name)
{
  numRows_ = numRows;
  numCols_ = numCols;

  values_.resize(numRows_);
  columns_.resize(numCols_);

  //renames the matrix
  name_ = name;
}

// Returns the sparsity of the matrix
double lilSpmat::sparsity() const
{
  unsigned int nz = 0;
  for(unsigned int i=0;i< numRows_;i++)
  {
    nz += columns_[i].size();
  }
  return (1.0 - ((double)nz / ((double)(numRows_ * numCols_))));
}

// Returns the number of non-zero values in row i
unsigned int lilSpmat::getNumNZ(const unsigned int &i) const
{
  return columns_[i].size();
}

// Returns the j-th non-zero value in row i (j is not the column)
double lilSpmat::getNZValue(const unsigned int &i, const unsigned int &j) const
{
  return values_[i][j];
}

// Returns the column of the j-th non-zero value in row i (j is not the column)
unsigned int lilSpmat::getNZColumn(const unsigned int &i, const unsigned int &j) const
{
  return columns_[i][j];
}

// Sets a value to position (i,j) if exists, otherwise inserts a new value
void lilSpmat::setValue(const unsigned int& i, const unsigned int& j, const double& val)
{
  checkPos(this, i, j);
  for(unsigned int k=0;k<columns_[i].size();k++)
  {
    if(columns_[i][k] == j)
    {
      values_[i][k] = val;
      return;
    }
  }
  columns_[i].push_back(j);
  values_[i].push_back(val);
}

// Adds a value to position (i,j) if exists, otherwise inserts a new value
void lilSpmat::addValue(const unsigned int& i, const unsigned int& j, const double& val)
{
  checkPos(this, i, j);
  for(unsigned int k=0;k<columns_[i].size();k++)
  {
    if(columns_[i][k] == j)
    {
      values_[i][k] += val;
      return;
    }
  }
  columns_[i].push_back(j);
  values_[i].push_back(val);
}

// Subtracts a value to position (i,j) if exists, otherwise inserts a new value
void lilSpmat::subValue(const unsigned int& i, const unsigned int& j, const double& val)
{
  checkPos(this, i, j);
  for(unsigned int k=0;k<columns_[i].size();k++)
  {
    if(columns_[i][k] == j)
    {
      values_[i][k] -= val; 
      return;
    }
  }
  columns_[i].push_back(j);
  values_[i].push_back(-val);
}

// Multiplies a value to position (i,j) if exists
void lilSpmat::mulValue(const unsigned int& i, const unsigned int& j, const double& val)
{
  checkPos(this, i, j);
  for(unsigned int k=0;k<columns_[i].size();k++)
  {
    if(columns_[i][k] == j)
    {
      values_[i][k] *= val;
      return;
    }
  }
}

// Deletes the value in position (i,j) if exists, otherwise does nothing
void lilSpmat::delValue(const unsigned int& i, const unsigned int& j)
{
  checkPos(this, i, j);
  for(unsigned int k=0;k<columns_[i].size();k++)
  {
    if(columns_[i][k] == j)
    {
      columns_[i].erase(columns_[i].begin()+k);
      values_[i].erase(values_[i].begin()+k);
      return;
    }
  }
}

// Returns the value in position (i,j) if exists, otherwise returns 0
double lilSpmat::getValue(const unsigned int& i, const unsigned int& j) const
{
  checkPos(this, i, j);
  for(unsigned int k=0;k<columns_[i].size();k++)
  {
    if(columns_[i][k] == j)
    {
      return values_[i][k];
    }
  }
  return 0.0;
}

// Returns the sparse matrix in a dense format as a vector of vectors
std::vector< std::vector<double> > lilSpmat::dense() const
{
  std::vector<std::vector<double>> denseMatrix(numRows_);
  std::vector<double> temp(numCols_);
  unsigned int id_column = 0;
  for(unsigned int i=0;i<numRows_;i++)
  {
    denseMatrix[i] = temp;
  }
  for(unsigned int i=0;i<numRows_;i++)
  {
    for(unsigned int j=0;j<columns_[i].size();j++)
    {
      id_column = columns_[i][j];
      denseMatrix[i][id_column] = values_[i][j];
    }
  }
  return denseMatrix;
}

// Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
double lilSpmat::vecRowMul(const unsigned int& i, const std::vector<double>& vecPhi) const
{
  double sumProdRow = 0.0;
  unsigned int id_column = 0;
  for(unsigned int j=0;j<columns_[i].size();j++)
  {
    id_column = columns_[i][j];
    sumProdRow += values_[i][j] * vecPhi[id_column];
  }
  return sumProdRow;
}

// Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double excluding the diagonal
double lilSpmat::vecRowMulNoDiagonal(const unsigned int& i, const std::vector<double>& vecPhi) const
{
  double sumProdRow = 0.0;
  unsigned int id_column = 0;
  for(unsigned int j=0;j<columns_[i].size();j++)
  {
    id_column = columns_[i][j];
    if (i != id_column) sumProdRow += values_[i][j] * vecPhi[id_column];
  }
  return sumProdRow;
}

// Returns the sum of the products of a double for the elements of the iRow matrix row
// double valueProduct(const unsigned int& i, const double& val)
// {
//   double sumProdRow = 0.0;
//   for(unsigned int j=0;j<columns_[i].size();j++)
//   {
//     sumProdRow += values_[i][j] * val;
//   }
//   return sumProdRow;
// }

// Addition operator
lilSpmat operator+(const lilSpmat& A,const lilSpmat& B)
{
  checkAdd(A, B); // checks compatibility for operation
  lilSpmat C = A;
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
lilSpmat* operator+(const lilSpmat& A,const lilSpmat* B)
{
  lilSpmat* C = new lilSpmat();
  *C = A + *B;
  return C;
}

// Subtraction operator
lilSpmat operator-(const lilSpmat& A,const lilSpmat& B)
{
  checkAdd(A, B);
  lilSpmat C = A;
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
lilSpmat* operator-(const lilSpmat& A,const lilSpmat* B)
{
  lilSpmat* C = new lilSpmat();
  *C = A - *B;
  return C;
}

// Multiplication operator (mat-scalar)
lilSpmat operator*(const lilSpmat& A,const double& val)
{
  lilSpmat C = A;
  for (unsigned int i = 0; i < C.getNumRows();i++)
  {
    for (unsigned int j = 0; j < C.getNumNZ(i);j++)
    {
      C.mulValue(i,j,val);
    }
  }   
  return C;
}
// Multiplication operator (mat-scalar) (pointer)
lilSpmat* operator*(const lilSpmat& A,const double* val)
{
  lilSpmat* C = new lilSpmat();
  *C = A * *val;
  return C;
}

// Multiplication operator (mat-mat)
lilSpmat operator*(const lilSpmat& A,const lilSpmat& B)
{
  checkProd(A,B);
  lilSpmat C = lilSpmat(A.numRows_, B.numCols_);
  double val;
  for(unsigned int i=0; i<A.numRows_; i++)
  {
    for(unsigned int j=0; j<B.numCols_; j++)
    {
      val = 0.0;
      for(unsigned int k=0; k<B.numRows_; k++)
      {
        for(unsigned int l=0; l<A.columns_[i].size(); l++)
        {
          if(A.columns_[i][l] == k)
          {
            for(unsigned int m=0; m<B.columns_[k].size(); m++)
            {
              if(B.columns_[k][m] == j)
              {
                val += A.values_[i][l] * B.values_[k][m];
                break;
              }
            }
            break;
          }
        }
      }
      C.addValue(i, j, val);
    }
  }
  return C;
}
// Multiplication operator (mat-mat) (pointer)
lilSpmat* operator*(const lilSpmat& A,const lilSpmat* B)
{
  lilSpmat* C = new lilSpmat();
  *C = A * *B;
  return C;
}

// Multiplication operator (mat-vec)
std::vector<double> operator*(const lilSpmat& A,const std::vector<double>& vec)
{
  checkProd(A, vec);
  std::vector<double> v(A.numCols_);
  for(unsigned int i=0; i<A.numRows_; i++)
  {
    v[i] = 0.0;
    for(unsigned int j=0; j<A.columns_[i].size(); j++)
    {
      v[i] += A.values_[i][j] * vec[A.columns_[i][j]];
    }
  }
  return v;
}
// Multiplication operator (mat-vec) (pointer)
std::vector<double>* operator*(const lilSpmat& A,const std::vector<double>* vec)
{
  std::vector<double>* v = new std::vector<double>;
  *v = A * *vec;
  return v;
}
// Multiplication operator (mat-vec) (pointer)
std::vector<double>* operator*(const lilSpmat* A,const std::vector<double>& vec)
{
  std::vector<double>* v = new std::vector<double>;
  *v = *A * vec;
  return v;
}

// Multiplication operator (mat-vec(vec))
std::vector<std::vector<double>> operator*(const lilSpmat& A,const std::vector<std::vector<double>>& vec)
{
  checkProd(A, vec);
  std::vector<std::vector<double>> v(A.numRows_);
  for (unsigned int x=0; x<v.size(); x++)
  {
    v[x].resize(vec[0].size());
  }
  double val;
  for(unsigned int i=0; i<A.numRows_; i++)
  {
    for(unsigned int j=0; j<A.numCols_; j++)
    {
      val = 0.0;
      for(unsigned int k=0; k<vec.size(); k++)
      {
        for(unsigned int l=0; l<A.columns_[i].size(); l++)
        {
          if(A.columns_[i][l] == k)
          {
            val += A.values_[i][l] * vec[A.columns_[i][l]][j];
            break;
          }
        }
        v[i][j] = val;
      }
    }
  }
  return v;
}
// Multiplication operator (mat-vec(vec)) (pointer)
std::vector<std::vector<double>>* operator*(const lilSpmat& A,const std::vector<std::vector<double>>* vec)
{
  std::vector<std::vector<double>>* v = new std::vector<std::vector<double>>;
  *v = A * *vec;
  return v;
}
// Multiplication operator (mat-vec(vec)) (pointer)
std::vector<std::vector<double>>* operator*(const lilSpmat* A,const std::vector<std::vector<double>>& vec)
{
  std::vector<std::vector<double>>* v = new std::vector<std::vector<double>>;
  *v = *A * vec;
  return v;
}