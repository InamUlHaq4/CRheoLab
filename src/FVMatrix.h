#ifndef FVMATRIX_H
#define FVMATRIX_H


#include <vector>
#include "Mesh.h"
#include "Dictionary.h"

#include "VolField.h"

#include "lilSpmat.h"
#include "csrSpmat.h"

#include "./fvSolvers/FVMatrixSolver.h"
#include "./fvSolvers/SJacobi.h"
#include "./fvSolvers/SGaussSiedel.h"
#include "./fvSolvers/SSOR.h"
#include "SolverPerf.h"


// An abstract class for the solver of the system of equations

//template< typename vectorType> - For now just double - thje template will be implemented in the future
class FVMatrix
{
    
public:

FVMatrix(VolField<scalarField>& field);

FVMatrix(const FVMatrix& fvMatrixA);

virtual ~FVMatrix();

/// Function to create random sparse matrix, it also creates a random vector \f$ b\f$
void createRandomSparseaMatrixbVector();

// Solve The System of Equations
void solve();

/// Reset the \f$ X\f$ vector to zero
void resetxVector();

//Getters
SolverPerf solverPerf();
spmat* aMatrix() const;
spmat* aMatrixRef();
const std::vector<double> bVector() const;
std::vector<double>& bVectorRef();
VolField<scalarField>& field() const;
Dictionary& fvSolutionDict();

//FVMatrix operator+(const FVMatrix& fvmB);

private:
spmat* aMatrix_;

std::vector<double> bVector_;

SolverPerf solverPerf_;

VolField<scalarField>& field_;

Dictionary fvSolutionDict_;
    
inline double residualValue();
    
inline double residualNormFactor();          

};

FVMatrix operator+(const FVMatrix& fvmA, const FVMatrix& fvmB);

#endif
