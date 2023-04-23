#include "FVMatrixSolver.h"
#include <vector>

//Constructor
FVMatrixSolver::FVMatrixSolver(spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, Dictionary fvSolutionDict):
aMatrix_(aMatrix),
bVector_(&bVector),
xVector_(&xVector),
fvSolutionDict_(fvSolutionDict)
{
}
 
FVMatrixSolver::~FVMatrixSolver()
{}
















