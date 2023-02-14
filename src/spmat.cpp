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

// Check if addition/subtraction operation is possible
// bool checkAdd(const spmat& A,const spmat* B)
// {
//   if (A.numRows_ != B->numRows_)
//   {
//     std::cout << A.name_ << " and " << B->name_ << " cannot be added/subtracted." << std::endl;
//     return false;
//   } else
//     {
//       return true;
//     }
// }
// bool checkAdd(const spmat& A,const spmat& B)
// {
//   if (A.getNumRows() != B.getNumRows() || A.getNumCols() != B.getNumCols())
//   {
//     // Throws exception to stop the program
//     // throw std::runtime_error("Error: invalid column for sparse structure matrix");
//     std::cout << "ERROR: "<< A.name_ << " and " << B.name_ << " cannot be added/subtracted due to size incompatibility." << std::endl;
//     return false;
//   } else
//     {
//       return true;
//     }
// }

// // Addition operator
// spmat operator+(const spmat& A,const spmat& B)
// {
//   if (checkAdd(A, B))
//   {
//     spmat C = A;
//     for(unsigned int i=0;i<B.getNumRows();i++)
//     {
//       for(unsigned int j=0;j<B.getNumNZ(i);j++)
//       {
//         C.addValue(i,B.getNZColumn(i,j),B.getNZValue(i,j));
//       }
//     }
//     return C;
//   }
// }
// spmat* operator+(const spmat& A,const spmat* B)
// {
//   if (checkAdd(A,*B) == true)
//   {
//     spmat* C = new lilSpmat(A);
//     for(unsigned int i=0;i<B->getNumRows();i++)
//     {
//       for(unsigned int j=0;j<B->getNumNZ(i);j++)
//       {
//         C->addValue(i,B->getNZColumn(i,j),B->getNZValue(i,j));
//       }
//     }
//     return C;
//   }
// }