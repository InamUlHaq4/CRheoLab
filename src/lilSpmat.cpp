#include "lilSpmat.h"
#include <iostream>

// Constructor
// Constructs an empty sparse matrix and allocates memory for the rows
lilSpmat::lilSpmat(unsigned int numRows, unsigned int numCols)
{
  // Store number of rows and columns
  setNumRows(numRows);
  setNumCols(numCols);

  // Allocate memory for the rows since any row might be accessed at any time
  // Do not do the same for each columns_[i] and values_[i] vector since their size
  // should only increase as new entries are added
  values_.resize(NumRows());
  columns_.resize(NumRows());
}

// Returns the sparsity of the matrix
double lilSpmat::sparsity()
{
  unsigned int nz = 0;
  for(unsigned int i=0;i< NumRows();i++)
  {
     nz += columns_[i].size();
  }
  return (1.0 - ((double)nz / ((double)(NumRows() * NumCols()))));
}

// Sets a value to position (i,j) if exists, otherwise inserts a new value
void lilSpmat::setValue(const unsigned int& i, const unsigned int& j, const double& val)
{
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

// Deletes the value in position (i,j) if exists, otherwise does nothing
void lilSpmat::delValue(const unsigned int& i, const unsigned int& j)
{
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
double lilSpmat::getValue(const unsigned int& i, const unsigned int& j)
{
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
std::vector< std::vector<double> > lilSpmat::dense()
{
  std::vector< std::vector<double> > denseMatrix(NumRows());
  std::vector<double> temp(NumCols());
  unsigned int id_column = 0;
  for(unsigned int i=0;i<NumRows();i++)
  {
    denseMatrix[i] = temp;
  }
  for(unsigned int i=0;i<NumRows();i++)
  {
    for(unsigned int j=0;j<columns_[i].size();j++)
    {
      id_column = columns_[i][j];
      denseMatrix[i][id_column] = values_[i][j];
    }
  }
  return denseMatrix;
}

// Function that returns the product matrix-vector as a vector
std::vector<double> lilSpmat::matMul(const std::vector<double>& vecPhi)
{
  std::vector<double> v(vecPhi.size());
  unsigned int id_column = 0;
  for(unsigned int i=0;i<NumRows();i++)
  {
    v[i] = 0.0;
    for(unsigned int j=0;j<columns_[i].size();j++)
    {
      id_column = columns_[i][j];
      v[i] += values_[i][j] * vecPhi[id_column];
    }
  }
  return v;
}

// Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
double lilSpmat::vecMul(const unsigned int& i, const std::vector<double>& vecPhi)
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
double lilSpmat::vecMulNoDiagonal(const unsigned int& i, const std::vector<double>& vecPhi)
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

// Returns a double given by the sum of the products of xValue (a double) for a specific row of the matrix
double lilSpmat::xValueProduct(const unsigned int& i, const double& xValue)
{
  double sumProdRow = 0.0;
  for(unsigned int j=0;j<columns_[i].size();j++)
  {
    sumProdRow += values_[i][j] * xValue;
  }
  return sumProdRow;
}
