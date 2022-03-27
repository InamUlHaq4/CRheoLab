#ifndef SPMAT_H
#define SPMAT_H

#include <vector>

// Class to implement an abstract class of a sparse matrix

class spmat {

protected:

  // Number of rows of the stored matrix
  unsigned int numRows_;

  // Number of columns of the stored matrix
  unsigned int numCols_;

public:

  // Returns the sparsity of the matrix
  double virtual sparsity() = 0;

  // Returns the number of rows
  unsigned int getNumRows()
  {
    return numRows_;
  }

  // Returns the number of columns
  unsigned int getNumCols()
  {
    return numCols_;
  }

  // Adds a value to position (i,j) if exists, otherwise inserts a new value
  void addValue(unsigned int i, unsigned int j, double val);

  // Subtracts a value to position (i,j) if exists, otherwise inserts a new value with oposite sign
  void subValue(unsigned int i, unsigned int j, double val);

  // Deletes the value in position (i,j) if exists, otherwise does nothing
  void delValue(unsigned int i, unsigned int j);

  // Returns the value in position (i,j) if exists, otherwise returns 0
  double getValue(unsigned int i, unsigned int j);

  // Returns the sparse matrix in a dense format as a vector of vectors
  std::vector< std::vector<double> > dense();

  // Returns the product matrix-vector as a vector
  //std::vector<double> matMul(std::vector<double> v);
  std::vector<double> matMul(std::vector<double> &v, const std::vector<double> &vecPhi);

  // Group 5
  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double excluding the diagonal
  //double vecMulNoDiagonal(const unsigned int iRow, const std::vector<double> &vecPhi);
  //double vecMulNoDiagonal(const unsigned int iRow, std::vector<double> &vecPhi);

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
  //double vecMul(unsigned int i, std::vector<double> v);
  double vecMul(const unsigned int i, const std::vector<double> &vecPhi);

};

#endif // SPMAT_H
