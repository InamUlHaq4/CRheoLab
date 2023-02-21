

#include "FVMatrix.h"

// Temporary Soltion to compile the code - Must be updated in the future
// template <typename vectorType>
// vectorType& VolField<vectorType>::internalFieldRef() 
// {
//   return internalField_;
// }
// Temporary Solution to compile the code - Must be updated in the future

//Constructor

FVMatrix::FVMatrix(VolField<scalarField>& field):
field_(field), fvSolutionDict_(field.mesh().time().system()+"fvSolution")
{
    unsigned int nCells=field_.mesh().nCells();
    bVector_.resize(nCells);
    fvSolutionDict_.readDict("solvers");
      
    std::string matrixFormat (fvSolutionDict_.subDict("solvers").subDict(field_.name()).lookup<std::string> ("matrixFormat"));

    if (matrixFormat== "lOLists")
        aMatrix_ = new lilSpmat(nCells,nCells);
    else if (matrixFormat== "CSR")
        aMatrix_ = new csrSpmat(field_.mesh());
    else {
        std::cout << "ERROR: Unindentified Matrix format";
        exit(0);
    }
}
 
FVMatrix::~FVMatrix()
{
    //std::cout << "delete aMAtrix_" << std::endl;
    delete aMatrix_;
}


void FVMatrix::solve()
{
    double residualNormFactorVal = residualNormFactor();
    double residual = residualValue()/residualNormFactorVal;
    double residualFirst = residual;
        
    auto start = std::chrono::high_resolution_clock::now();

    // Initialize solver performance Object
    solverPerf_ = SolverPerf(fvSolutionDict_.subDict("solvers").subDict(field_.name()), residualFirst);
  
    FVMatrixSolver* Solver;

     if(solverPerf_.solverModel() == "Jacobi")
    {
        //Solver = new SJacobi(aMatrix_, bVector_, field_.internalFieldRef(), field_.mesh().nCells());
        Solver = new SJacobi(aMatrix_, bVector_, field_.internalFieldRef());
    }
    else if(solverPerf_.solverModel() == "GaussSiedel")
    {
        //Solver = new SGaussSiedel(aMatrix_, bVector_, field_.internalFieldRef(), field_.mesh().nCells());
        Solver = new SGaussSiedel(aMatrix_, bVector_, field_.internalFieldRef());
    }
    else if(solverPerf_.solverModel() == "SOR")
    {        
        double wSOR (fvSolutionDict_.subDict("solvers").subDict(field_.name()).lookup<double> ("wSOR"));
        //Solver = new SSOR(aMatrix_, bVector_, field_.internalFieldRef(), field_.mesh().nCells(), wSOR);
        Solver = new SSOR(aMatrix_, bVector_, field_.internalFieldRef(), wSOR);
    } 

    while (solverPerf_.proceed())
    {
        
        Solver->doSolverStep();

        residual = residualValue()/residualNormFactor(); 
        
        solverPerf_.update (residual);

    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    //solverPerf_ = SolverPerf(solverModel, residualFirst, residual, countIter, duration.count());
    solverPerf_.final (duration.count());
}

///////////////////////////////////////////////
inline double FVMatrix::residualValue()
{
    double residualMagnitude = 0.0;

    for (unsigned int i = 0; i < field_.mesh().nCells(); i++)
    {
        residualMagnitude += fabs(bVector_[i] - aMatrix_->vecMul(i,field_.internalFieldRef()));
    }
    return residualMagnitude;
}

///////////////////////////////////////////////
inline double FVMatrix::residualNormFactor()
{
    
    double xAverage=0.0;
    for (unsigned int i = 0; i < field_.mesh().nCells(); i++)
    {
        xAverage += field_.internalFieldRef()[i];
    }
    xAverage = xAverage / field_.mesh().nCells();


    double nNormalize=0.0 ;
    for (unsigned int i = 0; i < field_.mesh().nCells(); i++)
    {
        double xValueProduct = aMatrix_->xValueProduct(i,xAverage);
        nNormalize += fabs(aMatrix_->vecMul(i,field_.internalFieldRef()) -  xValueProduct) + fabs(bVector_[i] - xValueProduct);
    }
    return nNormalize;
}

void FVMatrix::createRandomSparseaMatrixbVector()
{
    std::cout << ">> entered create Sparse aMatrix and bVector" << std::endl;

    int maxValue = 10;
    srand(time(0));
  
    for (unsigned int iFace=0;iFace < field_.mesh().nInteriorFaces();iFace++)
    {
        unsigned int iNeighbour = field_.mesh().faceList()[iFace].neighbour()->ID();
        unsigned int iOwner = field_.mesh().faceList()[iFace].owner()->ID();
        
        double mCoef = (static_cast<double>(rand() % maxValue))+1.0;

        aMatrix_->addValue(iNeighbour,iOwner, -mCoef); // Add mCoef to line iNeighbour column iOwner
        aMatrix_->addValue(iOwner,iNeighbour, -mCoef); // Add mCoef to line iOwner column iNeighbour
        aMatrix_->addValue(iNeighbour,iNeighbour, mCoef); // Add mCoef to Diagonal iNeighbour ,iNeighbour
        aMatrix_->addValue(iOwner,iOwner, mCoef); // Add mCoef to Diagonal iOwner ,iOwner
        // std::cout << fvMatrix.aMatrix_->getValue(iNeighbour,iOwner) << std::endl;
        // std::cout << fvMatrix.aMatrix_->getValue(iOwner,iNeighbour) << std::endl;
        // std::cout << fvMatrix.aMatrix_->getValue(iNeighbour,iNeighbour) << std::endl;
        // std::cout << fvMatrix.aMatrix_->getValue(iOwner,iOwner) << std::endl;

    }

    //Loop for cells
    for (unsigned int iCell = 0; iCell < field_.mesh().nCells(); iCell++)
    {
        // add a factor to diagonal
        aMatrix_->addValue(iCell,iCell, 1.1 *  aMatrix_->getValue(iCell,iCell));
        bVector_[iCell] = (static_cast<double>(rand() % maxValue));
    }

    std::cout << ">> leaving create Sparse aMatrix and bVector " << std::endl;
}

// reset class xVector to zeros
void FVMatrix::resetxVector()
{
    std::fill(field_.internalFieldRef().begin(), field_.internalFieldRef().end(), 0.);
}

//Getters
SolverPerf FVMatrix::solverPerf()
{
    return solverPerf_;
}

spmat* FVMatrix::aMatrix()
{
    return aMatrix_;
}

std::vector<double> FVMatrix::bVector()
{
    return bVector_;
}