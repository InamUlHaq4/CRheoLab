#include "spmat.h"
#include <iostream>

// Returns the number of rows
unsigned int spmat::getNumRows() const
{
    return numRows_;
}

// Returns the number of columns
unsigned int spmat::getNumCols() const
{
    return numCols_;
}

// Add a name to a matrix
void spmat::setName(const std::string& name)
{
    name_ = name;
}

// Returns the name of the matrix
std::string spmat::getName() const
{
    return name_;
}

// Check if requested position exists
void checkPos(const spmat* A, const unsigned int& row, const unsigned int& col)
{
  if (row < 0 || A->numRows_-1 < row || col < 0 || A->numCols_-1 < col)
  {
    throw std::runtime_error("ERROR: Cannot perform operation because the desired position does not exist.");
  }
}

// Check if addition/subtraction operation is possible
void checkAdd(const spmat& A,const spmat& B)
{
  if (A.numRows_ != B.numRows_ || A.numCols_ != B.numCols_)
  {
    throw std::runtime_error("ERROR: " +A.name_+ " matrix and " +B.name_+ " cannot be added/subtracted due to size incompatibility.");
  }
}

// Check if multiplication operation is possible (mat-mat)
void checkProd(const spmat& A,const spmat& B)
{
  if (A.numCols_ != B.numRows_)
  {
    throw std::runtime_error("ERROR: " +A.name_+ " matrix and " +B.name_+ " cannot be multiplied due to size incompatibility.");
  }
}
// Check if multiplication operation is possible (mat-vec)
void checkProd(const spmat& A, const std::vector<double>& vec)
{
  if (A.numCols_ != vec.size())
  {
    throw std::runtime_error("ERROR: " +A.name_+ " matrix and vector cannot be multiplied due to size incompatibility.");
  }
}
// Check if multiplication operation is possible (mat-vec(vec))
void checkProd(const spmat& A, const std::vector<std::vector<double>>& vec)
{
  if (A.numCols_ != vec.size())
  {
    throw std::runtime_error("ERROR: " +A.name_+ " matrix and vector of vectores cannot be multiplied due to size incompatibility.");
  }
}

// Dense matrix printing
std::ostream& operator<<(std::ostream& os,const spmat& spmat)
{
  std::vector< std::vector<double> > denseMatrix;
  denseMatrix = spmat.dense();
  os << spmat.name_ << " dense matrix:" << std::endl;
  for (unsigned int i = 0; i < denseMatrix.size(); i++)
    {
          for (unsigned int j = 0; j < denseMatrix[i].size(); j++)
          {
                os << denseMatrix[i][j] << " ";
          }
          os << std::endl;
    }
  return os;
}
// Prints the dense form of a vector
std::ostream& operator<<(std::ostream& os,const std::vector<double>& vec)
{
  os << "Vector: (";
  for (unsigned int i=0; i<vec.size(); i++)
  {
    os << vec[i];
    if (i != vec.size() - 1)
    {
      os << ", "; 
    }
  }
  os << ")" << std::endl;
  return os;
}
// Prints the dense form of a vector of vectors
std::ostream& operator<<(std::ostream& os,const std::vector<std::vector<double>>& vec)
{
  os << "Vector:  (";
  for (unsigned int i=0; i<vec.size(); i++)
  {
    if (i != 0)
    {
      os << "\t (" ;
    }
    for (unsigned int j=0; j<vec[i].size(); j++)
    {
      os << vec[i][j];
      if (j != vec[i].size() - 1)
      {
        os << ", "; 
      }
    }
    os << ")" << std::endl;
  }
  return os;
}
