
#include "FVSystem.h"
#include <vector>
#include <random>
#include <chrono>


FVSystem::FVSystem( Mesh &mesh, vector<double> &xVector) : 
    mesh_(mesh)
    , xVector_(&xVector)
    , nCells_(mesh.nCells_)
    , myDict_(
        Dictionary 
            (
                IOObject
                    (
                        "fvSystem",
                        mesh.time().system(), //"constant",
                        mesh,
                        fileAction::MUST_READ,
                        fileAction::NO_WRITE,
                        true
                    )
            )
    )
    , matrixFormat_ (myDict_.lookup<std::string> ("matrixFormat"))
    , matrixType_ (myDict_.lookup<std::string> ("matrixType"))
    , fvMatrix (new FVMatrix(mesh_, matrixFormat_, matrixType_))
    , solverModel_ (myDict_.lookup<std::string> ("solverModel"))
    , absNormResidual_ (myDict_.lookup<double> ("absNormResidual"))
    , relNormResidual_ (myDict_.lookup<double> ("relNormResidual"))
{
    if (matrixType_== "full"){
       createRandomFullaMatrixbVector();  
    }
    else if (matrixType_== "sparse") {
       createRandomSparseaMatrixbVector(mesh);
    }
    else {
        std::cout << "ERROR: Unindentified Matrix type";
        exit(0);
    }

    setSolver(solverModel_);
    
    std::cout << "ncells:" << nCells_ << std::endl;
}

FVSystem::~FVSystem()
{
    delete Solver_;
    delete fvMatrix;
}


inline double FVSystem::residualValue()
{
    double residualMagnitude = 0.0;

    for (unsigned int i = 0; i < nCells_; i++)
    {
        residualMagnitude += fabs(fvMatrix->bVector_[i] - fvMatrix->aMatrix_->vecMul(i,(*xVector_)));
    }
    return residualMagnitude;
}

///////////////////////////////////////////////25/2/2022
inline double FVSystem::residualNormFactor()
{
    
    xAverage_=0.0;
    for (unsigned int i = 0; i < nCells_; i++)
    {
        xAverage_ += (*xVector_)[i];
    }
    xAverage_ = xAverage_ / nCells_;


    nNormalize_=0.0 ;
    for (unsigned int i = 0; i < nCells_; i++)
    {
        double xValueProduct = fvMatrix->aMatrix_->xValueProduct(i,xAverage_);
        nNormalize_ += fabs(fvMatrix->aMatrix_->vecMul(i,(*xVector_)) -  xValueProduct) + fabs(fvMatrix->bVector_[i] - xValueProduct);
    }
    return nNormalize_;
}

void FVSystem::createRandomFullaMatrixbVector()
{
    std::cout << ">> entered create Full aMatrix and bVector" << std::endl;

    int maxValue = 10;
    srand(time(0));

    for (unsigned int lineI = 0; lineI < nCells_; lineI++)
    {
        double diagValue = 0.0;
        for (unsigned int j = 0; j < lineI; j++)
        {
            fvMatrix->aMatrix_->addValue(lineI,j, static_cast<double>(rand() % maxValue) * (-1));
            diagValue += fabs(fvMatrix->aMatrix_->getValue(lineI,j));
        }

        for (unsigned int j = lineI + 1; j < nCells_; j++)
        {
            fvMatrix->aMatrix_->addValue(lineI,j, static_cast<double>(rand() % maxValue) * (-1));
            diagValue += fabs(fvMatrix->aMatrix_->getValue(lineI,j));
        }
        fvMatrix->aMatrix_->addValue(lineI,lineI, 1.1 * diagValue);
        fvMatrix->bVector_[lineI] = (static_cast<double>(rand() % maxValue));
        //std::cout << "LineI" << lineI << std::endl;
    }
    std::cout << ">> leaving create FullaMatrix and bVector " << std::endl;
}

void FVSystem::createRandomSparseaMatrixbVector(const Mesh &mesh)
{
    std::cout << ">> entered create Sparse aMatrix and bVector" << std::endl;

    int maxValue = 10;
    srand(time(0));
  
    for (unsigned int iFace=0;iFace<mesh.nInteriorFaces_;iFace++)
    {
        unsigned int iNeighbour = mesh.faceList_[iFace].getNeighbour()->ID_;
        unsigned int iOwner = mesh.faceList_[iFace].getOwner()->ID_;
        
        double mCoef = (static_cast<double>(rand() % maxValue))+1.0;

        fvMatrix->aMatrix_->addValue(iNeighbour,iOwner, -mCoef); // Add mCoef to line iNeighbour column iOwner
        fvMatrix->aMatrix_->addValue(iOwner,iNeighbour, -mCoef); // Add mCoef to line iOwner column iNeighbour
        fvMatrix->aMatrix_->addValue(iNeighbour,iNeighbour, mCoef); // Add mCoef to Diagonal iNeighbour ,iNeighbour
        fvMatrix->aMatrix_->addValue(iOwner,iOwner, mCoef); // Add mCoef to Diagonal iOwner ,iOwner
        // std::cout << fvMatrix.aMatrix_->getValue(iNeighbour,iOwner) << std::endl;
        // std::cout << fvMatrix.aMatrix_->getValue(iOwner,iNeighbour) << std::endl;
        // std::cout << fvMatrix.aMatrix_->getValue(iNeighbour,iNeighbour) << std::endl;
        // std::cout << fvMatrix.aMatrix_->getValue(iOwner,iOwner) << std::endl;

    }

    //Loop for cells
    for (unsigned int iCell = 0; iCell < nCells_; iCell++)
    {
        // add a factor to diagonal
        fvMatrix->aMatrix_->addValue(iCell,iCell, 1.1 *  fvMatrix->aMatrix_->getValue(iCell,iCell));
        fvMatrix->bVector_[iCell] = (static_cast<double>(rand() % maxValue));
    }

    std::cout << ">> leaving create Sparse aMatrix and bVector " << std::endl;
}

// reset class xVector to zeros
void FVSystem::resetxVector()
{
    std::fill((*xVector_).begin(), (*xVector_).end(), 0.);
}

// select a solver
void FVSystem::setSolver(std::string solvername)
{
     
    solverModel_ = solvername;
    
    std::cout << std::string(90, '#') << std::endl;

     if(solverModel_ == "Jacobi")
    {
        std::cout << ">>> Solving by Jacobi <<<<<" << std::endl;
        Solver_ = new SJacobi(fvMatrix, xVector_, nCells_);
    }
    else if(solverModel_ == "GaussSiedel")
    {
        std::cout << ">>> Solving by Gauss Siedel <<<<<" << std::endl;
        Solver_ = new SGaussSiedel(fvMatrix, xVector_, nCells_);
    }
    else if(solverModel_ == "SOR")
    {        
        std::cout << ">>> Solving by SOR <<<<<" << std::endl;

        double wSOR = myDict_.lookup<double> ("wSOR");

        std::cout << ">>>>> wSOR=" << wSOR << std::endl;
        Solver_ = new SSOR(fvMatrix, xVector_, nCells_, wSOR);
    } 
}
///////////////////////////////////////////////25/2/2022
std::vector<double> FVSystem::solve()
{
    std::vector<double> result(nCells_);

    double residualNormFactorValue =residualNormFactor();
    double residual = residualValue()/residualNormFactorValue;
    double residualFirst = residual;
    double relResidual = 1.0;
    
    int count = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while (residual > absNormResidual_ && relResidual > relNormResidual_)
    {
        
        result = Solver_->doSolverStep();
        *(xVector_) = result;

        residual = residualValue()/residualNormFactor(); //  I have used residualNormFactor() instead of residualNormFactorValue??? 
        relResidual = residual/residualFirst;

        count++;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << std::string(120, '#') << std::endl;
    std::cout << "Number of Iterations: " << count << std::endl;
    std::cout << "Initial Residual: " << std::scientific << residualFirst << " -> Final Residual: " << std::scientific << residual << std::endl;
    std::cout << "Elapsed time:" << duration.count() << " ms" << std::endl;
    return result;
}

void FVSystem::defineFVMatrix(FVMatrix& fvMatrixNew)
{
    this->fvMatrix =  &fvMatrixNew;
}