#include "FVMatrixSolver.h"
#include <vector>
#include <random>


//Constructor
FVMatrixSolver::FVMatrixSolver(FVMatrix* fvMatrix,std::vector<double>* xVector,const int nCells ):
fvMatrix_(fvMatrix),
xVector_(xVector),
nCells_(nCells)
{}
 
FVMatrixSolver::~FVMatrixSolver()
{}
















