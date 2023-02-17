#include "FVMatrixSolver.h"
#include <vector>

//Constructor
FVMatrixSolver::FVMatrixSolver(spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector):
aMatrix_(aMatrix),
bVector_(&bVector),
xVector_(&xVector)
//nCells_(nCells)
{}
 
FVMatrixSolver::~FVMatrixSolver()
{}
















