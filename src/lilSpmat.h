#ifndef LILSPMAT_H
#define LILSPMAT_H

#include "spmat.h"
#include <vector>
#include <numeric>
#include <ostream>

// Class to implement a list of lists for a sparse matrix
class lilSpmat : public spmat {

public: // change to private later

  // vector of vector for the values
  // values_[i] is the vector for row i
  // values_[i][j] is the index in position j of the std::vector for row i
  // values_ always has numRows_ entries
  // values_[i] has as many entries as non-null values in row i
  std::vector< std::vector<double> > values_;

  // Vector of vector for the columns
  // columns_[i] is the vector for row i
  // columns_[i][j] is the index in position j of the std::vector for row i
  // columns_ always has numRows_ entries
  // columns_[i] has as many entries as non-null values in row i
  std::vector< std::vector<unsigned int> > columns_;

public:

  // Default Constructor
  lilSpmat(){}

  // Constructor with matrix size and name
  lilSpmat(unsigned int numRows, unsigned int numCols, const std::string name = "default");

  // Destructor
  virtual ~lilSpmat(){};

  // Returns the sparsity of the matrix
  double sparsity() const override;

  // Returns the number of non-zero values in row i
  unsigned int getNumNZ(const unsigned int &i) const override;

  // Returns the j-th non-zero value in row i (j is not the column)
  double getNZValue(const unsigned int &i, const unsigned int &j) const override;

  // Returns the column of the j-th non-zero value in row i (j is not the column)
  unsigned int getNZColumn(const unsigned int &i, const unsigned int &j) const override;

  // Sets a value to position (i,j) if exists, otherwise inserts a new value
  void setValue(const unsigned int& i, const unsigned int& j, const double& val) override;

  // Adds a value to position (i,j) if exists, otherwise inserts a new value
  void addValue(const unsigned int& i, const unsigned int& j, const double& val) override;

  // Subtracts a value to position (i,j) if exists, otherwise inserts a new value with oposite sign
  void subValue(const unsigned int& i, const unsigned int& j, const double& val) override;

  // Multiply a value to position (i,j) if exists
  void mulValue(const unsigned int& i, const unsigned int& j, const double& val);

  // Deletes the value in position (i,j) if exists, otherwise does nothing
  void delValue(const unsigned int& i, const unsigned int& j) override;

  // Returns the value in position (i,j) if exists, otherwise returns 0
  double getValue(const unsigned int& i, const unsigned int& j) const override;

  // Returns the sparse matrix in a dense format as a vector of vectors
  std::vector< std::vector<double> > dense() const override;

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
  double vecRowMul(const unsigned int& i, const std::vector<double>& vecPhi) const override;

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double excluding the diagonal
  double vecRowMulNoDiagonal(const unsigned int& i, const std::vector<double>& vecPhi) const override;

  // Returns the sum of the products of a double for the elements of the iRow matrix row
  // double valueProduct(const unsigned int& i, const double& val) const override;
  
};

// Addition operator
lilSpmat operator+(const lilSpmat& A,const lilSpmat& B);
// Addition operator (pointer)
lilSpmat* operator+(const lilSpmat& A,const lilSpmat* B);

// Subtraction operator
lilSpmat operator-(const lilSpmat& A,const lilSpmat& B);
// Subtraction operator (pointer)
lilSpmat* operator-(const lilSpmat& A,const lilSpmat* B);

// Multiplication operator (mat-scalar)
lilSpmat operator*(const lilSpmat& A,const double& val);
// Multiplication operator (mat-scalar) (pointer)
lilSpmat* operator*(const lilSpmat& A,const double* val);

// Multiplication operator (mat-mat)
lilSpmat operator*(const lilSpmat& A,const lilSpmat& B);
// Multiplication operator (mat-mat) (pointer)
lilSpmat* operator*(const lilSpmat& A,const lilSpmat* B);

// Multiplication operator (mat-vec)
std::vector<double> operator*(const lilSpmat& A,const std::vector<double>& vec);
// Multiplication operator (mat-vec) (pointer)
std::vector<double>* operator*(const lilSpmat& A,const std::vector<double>* vec);
// Multiplication operator (mat-vec) (pointer)
std::vector<double>* operator*(const lilSpmat* A,const std::vector<double>& vec);

// Multiplication operator (mat-vec(vec)) 
std::vector<std::vector<double>> operator*(const lilSpmat& A,const std::vector<std::vector<double>>& vec);
// Multiplication operator (mat-vec(vec)) (pointer)
std::vector<std::vector<double>>* operator*(const lilSpmat& A,const std::vector<std::vector<double>>* vec);
// Multiplication operator (mat-vec(vec)) (pointer)
std::vector<std::vector<double>>* operator*(const lilSpmat* A,const std::vector<std::vector<double>>& vec);

#endif // LILSPMAT_H
