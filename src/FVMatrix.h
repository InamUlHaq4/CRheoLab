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
void createRandomSparseaMatrixbVector(const Mesh &mesh);

// Solve The System of Equations
void solve();

/// Reset the \f$ X\f$ vector to zero
void resetxVector();

//Getters
SolverPerf solverPerf();

private:
spmat* aMatrix_;

std::vector<double> bVector_;

SolverPerf solverPerf_;

VolField<scalarField>& field_;

Dictionary fvSolutionDict_;
    
inline double residualValue();
    
inline double residualNormFactor();
          

};

#endif
