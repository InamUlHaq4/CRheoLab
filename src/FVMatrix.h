#ifndef FVMATRIX_H
#define FVMATRIX_H


#include <vector>
#include "Mesh.h"
#include "Dictionary.h"

#include "VolField.h"

#include "lilSpmat.h"
#include "csrSpmat.h"

#include "FVMatrixSolver.h"
#include "SJacobi.h"
#include "SGaussSiedel.h"
#include "SSOR.h"
#include "SolverPerf.h"


// An abstract class for the solver of the system of equations

//template< typename vectorType> - For now just double - thje template will be implemented in the future
class FVMatrix
{
    
public:

FVMatrix(VolField<scalarField>& field);

virtual ~FVMatrix();

/// Function to create random sparse matrix, it also creates a random vector \f$ b\f$
void createRandomSparseaMatrixbVector();

// Solve The System of Equations
void solve();

/// Reset the \f$ X\f$ vector to zero
void resetxVector();

//Getters
SolverPerf solverPerf();
spmat* aMatrix();
std::vector<double> bVector();

//###########################
// Returns the number of rows
unsigned int numRows();

// Adds a value to position (i,j) if exists, otherwise inserts a new value
// virtual void addValue(const unsigned int &i, const unsigned int &j, const double &val) = 0;
//###########################


private:
spmat* aMatrix_;

std::vector<double> bVector_;

SolverPerf solverPerf_;

VolField<scalarField>& field_;

Dictionary fvSolutionDict_;
    
inline double residualValue();
    
inline double residualNormFactor();

//###########################
unsigned int numRows_;
//###########################

};

// Addition operator
//std::vector<double> operator+(const std::vector<double>& A,const std::vector<double>& B);
FVMatrix operator+(FVMatrix fvmA,FVMatrix fvmB);


// Addition operator
//csrSpmat* operator+(const csrSpmat& A,const csrSpmat* B);

// Subtraction operator
//std::vector<double> operator-(const std::vector<double>& A,const std::vector<double>& B);

// Subtraction operator
//csrSpmat* operator-(const csrSpmat& A,const csrSpmat* B);

#endif
