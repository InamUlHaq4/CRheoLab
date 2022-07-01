

#include "FVMatrix.h"

// Temporary Soltion to compile the code - Must be updated in the future
template <typename vectorType>
vectorType& VolField<vectorType>::internalFieldRef() 
{
  return internalField_;
}
// Temporary Soltion to compile the code - Must be updated in the future

//Constructor

FVMatrix::FVMatrix(VolField<scalarField>& field):
field_(field)
{
   unsigned int nCells=field_.mesh().nCells_;
   bVector_.resize(nCells);

    Dictionary fvSystemDict
    (
        Dictionary 
            (
                IOObject
                    (
                        "fvSystem",
                        field_.mesh().time().system(), //"constant",
                        field_.mesh(),
                        fileAction::MUST_READ,
                        fileAction::NO_WRITE,
                        true
                    )
            )
    );

    std::string matrixFormat (fvSystemDict.lookup<std::string> ("matrixFormat"));
    
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
    std::vector<double> result(field_.mesh().nCells_);
    //std::vector<double> result(50);

    double residualNormFactorValue = residualNormFactor();
    double residual = residualValue()/residualNormFactorValue;
    double residualFirst = residual;
    double relResidual = 1.0;
    
    int countIter = 0;
    auto start = std::chrono::high_resolution_clock::now();

    // Read control data from file
    Dictionary fvSystemDict
    (
        IOObject
        (
            "fvSystem",
            field_.mesh().time().system(), //"constant",
            field_.mesh(),
            fileAction::MUST_READ,
            fileAction::NO_WRITE,
            false
        )
    );
    double absNormResidual (fvSystemDict.lookup<double> ("absNormResidual"));
    double relNormResidual (fvSystemDict.lookup<double> ("relNormResidual"));
    std::string solverModel (fvSystemDict.lookup<std::string> ("solverModel"));
    
    std::cout << std::string(90, '#') << std::endl;

    FVMatrixSolver* Solver;

     if(solverModel == "Jacobi")
    {
        Solver = new SJacobi(aMatrix_, bVector_, field_.internalFieldRef(), field_.mesh().nCells_);
    }
    else if(solverModel == "GaussSiedel")
    {
        Solver = new SGaussSiedel(aMatrix_, bVector_, field_.internalFieldRef(), field_.mesh().nCells_);
    }
    else if(solverModel == "SOR")
    {        
        double wSOR (fvSystemDict.lookup<double> ("wSOR"));
        Solver = new SSOR(aMatrix_, bVector_, field_.internalFieldRef(), field_.mesh().nCells_, wSOR);
    } 

    while (residual > absNormResidual && relResidual > relNormResidual)
    {
        
        result = Solver->doSolverStep();
        field_.internalFieldRef() = result;

        residual = residualValue()/residualNormFactor(); 
        relResidual = residual/residualFirst;

        countIter++;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    solverPerf_ = SolverPerf(solverModel, residualFirst, residual, countIter, duration.count());
   
}

///////////////////////////////////////////////
inline double FVMatrix::residualValue()
{
    double residualMagnitude = 0.0;

    for (unsigned int i = 0; i < field_.mesh().nCells_; i++)
    {
        residualMagnitude += fabs(bVector_[i] - aMatrix_->vecMul(i,field_.internalFieldRef()));
    }
    return residualMagnitude;
}

///////////////////////////////////////////////
inline double FVMatrix::residualNormFactor()
{
    
    double xAverage=0.0;
    for (unsigned int i = 0; i < field_.mesh().nCells_; i++)
    {
        xAverage += field_.internalFieldRef()[i];
    }
    xAverage = xAverage / field_.mesh().nCells_;


    double nNormalize=0.0 ;
    for (unsigned int i = 0; i < field_.mesh().nCells_; i++)
    {
        double xValueProduct = aMatrix_->xValueProduct(i,xAverage);
        nNormalize += fabs(aMatrix_->vecMul(i,field_.internalFieldRef()) -  xValueProduct) + fabs(bVector_[i] - xValueProduct);
    }
    return nNormalize;
}
