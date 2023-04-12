#ifndef CSRSPMAT_H
#define CSRSPMAT_H

#include "spmat.h"
#include "Mesh.h"
#include <vector>

// Class to implement a list of lists for a sparse matrix
class csrSpmat : public spmat {

public: // change to private later

  // Number of total non-null values
  unsigned int numNZ_;

  // Vector of vector for the values
  std::vector<double> values_;

  // Vector of vector for the columns
  std::vector<unsigned int> columns_;

  // Vector of vector for the row pointers
  std::vector<unsigned int> rowPtr_;

public:

  // Default constructor
  csrSpmat(){}

  // Mesh constructor
  csrSpmat(Mesh& mesh);

  // Constructor with matrix size and name
  csrSpmat(unsigned int numRows, unsigned int numCols, const std::string name = "default");

  // Destructor
  virtual ~csrSpmat(){};

  // Returns the sparsity of the matrix
  double sparsity() const override;

  // Returns the number of non-zero values for the row 
  unsigned int getNumNZ(const unsigned int &row) const override;

  // Returns the j-th non-zero value for the row 
  double getNZValue(const unsigned int &row, const unsigned int &i) const override;

  // Returns the colum of the i-th non-zero value for the row 
  unsigned int getNZColumn(const unsigned int &row, const unsigned int &i) const override;

  // Sets a value to position (row,col) if exists, otherwise inserts a new value
  void setValue(const unsigned int& row, const unsigned int& col, const double& val) override;

  // Adds a value to position (row,col) if exists, otherwise throws an error
  void addValue(const unsigned int& row, const unsigned int& col, const double& val) override;

  // Subtracts a value to position (row,col) if exists, otherwise throws an error
  void subValue(const unsigned int& row, const unsigned int& col, const double& val) override;

  // Deletes the value in position (row,col) if exists, otherwise throws an error
  void delValue(const unsigned int& row, const unsigned int& col) override;

  // Returns the value in position (row,col) if exists, otherwise returns 0
  double getValue(const unsigned int& row, const unsigned int& col) const override;

  // Returns the sparse matrix in a dense format as a vector of vectors
  std::vector< std::vector<double> > dense() const override;

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
  double vecRowMul(const unsigned int& row, const std::vector<double>& vecPhi) const override;

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double excluding the diagonal
  double vecRowMulNoDiagonal(const unsigned int& row, const std::vector<double>& vecPhi) const override;

  // Returns the sum of the products of a double for the elements of the iRow matrix row
  // double valueProduct(const unsigned int& i, const double& val) const override;

};

// Addition operator
csrSpmat operator+(const csrSpmat& A,const csrSpmat& B);
// Addition operator (pointer)
csrSpmat* operator+(const csrSpmat& A,const csrSpmat* B);

// Subtraction operator 
csrSpmat operator-(const csrSpmat& A,const csrSpmat& B);
// Subtraction operator (pointer)
csrSpmat* operator-(const csrSpmat& A,const csrSpmat* B);

// Multiplication operator (mat-scalar)
csrSpmat operator*(const csrSpmat& A,const double& val);
// Multiplication operator (mat-scalar) (pointer)
csrSpmat* operator*(const csrSpmat& A,const double* val);

// Multiplication operator (mat-mat)
csrSpmat operator*(const csrSpmat& A,const csrSpmat& B);
// Multiplication operator (mat-mat) (pointer)
csrSpmat* operator*(const csrSpmat& A,const csrSpmat* B);

// Multiplication operator (mat-vec)
std::vector<double> operator*(const csrSpmat& A, const std::vector<double>& vec);
// Multiplication operator (mat-vec) (pointer)
std::vector<double>* operator*(const csrSpmat* A, const std::vector<double>& vec);
// Multiplication operator (mat-vec) (pointer)
std::vector<double>* operator*(const csrSpmat& A, const std::vector<double>* vec);


#endif // CSRSPMAT_H
