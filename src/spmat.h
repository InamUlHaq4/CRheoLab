#ifndef SPMAT_H
#define SPMAT_H

#include <vector>

// Class to implement an abstract class of a sparse matrix

class spmat {

private: //public before

  // Number of rows of the stored matrix
  unsigned int numRows_;

  // Number of columns of the stored matrix
  unsigned int numCols_;

public:

  // Returns the sparsity of the matrix
  double virtual sparsity() = 0;

//Setters
  void setNumRows(unsigned int numRows)//Added
  {
    numRows_ = numRows;
  }

  void setNumCols(unsigned int numCols)//Added
  {
    numCols_ = numCols;
  }

//Getters
  // Returns the number of rows
  unsigned int NumRows()
  {
    return numRows_;
  }

  // Returns the number of columns
  unsigned int NumCols()
  {
    return numCols_;
  }

  // Sets a value to position (i,j) if exists, otherwise inserts a new value
  virtual void setValue(const unsigned int &i, const unsigned int &j, const double &val) = 0;

  // Adds a value to position (i,j) if exists, otherwise inserts a new value
  virtual void addValue(const unsigned int &i, const unsigned int &j, const double &val) = 0;

  // Subtracts a value to position (i,j) if exists, otherwise inserts a new value with oposite sign
  virtual void subValue(const unsigned int &i, const unsigned int &j, const double &val) = 0;

  // Deletes the value in position (i,j) if exists, otherwise does nothing
  virtual void delValue(const unsigned int &i, const unsigned int &j) = 0;

  // Returns the value in position (i,j) if exists, otherwise returns 0
  virtual double getValue(const unsigned int &i, const unsigned int &j) = 0;

  // Returns the sparse matrix in a dense format as a vector of vectors
  virtual std::vector< std::vector<double> > dense() = 0;

  // Returns the product matrix-vector as a vector
  virtual std::vector<double> matMul(const std::vector<double> &vecPhi) = 0;

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
  virtual double vecMul(const unsigned int &i, const std::vector<double> &vecPhi) = 0;

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double excluding the diagonal
  virtual double vecMulNoDiagonal(const unsigned int &i, const std::vector<double> &vecPhi) = 0;

  // Returns a double given by the sum of the products of xValue (a double) for the elements of the iRow matrix row
  virtual double xValueProduct(const unsigned int &i, const double &xValue) = 0;

};

#endif // SPMAT_H
