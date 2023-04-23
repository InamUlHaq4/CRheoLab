#include "SSOR.h"

    std::string SSOR::solverMethod_("SOR");

    //Constructor
    SSOR::SSOR(spmat* aMatrix, std::vector<double> &bVector,std::vector<double>& xVector, Dictionary fvSolutionDict)
    :
    FVMatrixSolver(aMatrix, bVector, xVector, fvSolutionDict)    
    {
        wSOR_ = fvSolutionDict_.lookup<double> ("wSOR");

        std::cout << "wSOR=" << wSOR_ << std::endl ;
    }

    // Destructor
    SSOR::~SSOR()
    {}
     
    void SSOR::doSolverStep() const 
    {       
        std::vector<double> result(bVector_->size());    

        for(unsigned int lineI = 0; lineI < bVector_->size(); lineI++)
        {
            //result[lineI] = ((*bVector_)[lineI] -  axMultiplicationNoDiagonal(lineI))/(*aMatrix_)[lineI*nCells_+lineI];
            result[lineI] = ((*bVector_)[lineI] - aMatrix_->vecMulNoDiagonal(lineI,(*xVector_)))/aMatrix_->getValue(lineI,lineI);
            (*xVector_)[lineI] =  (*xVector_)[lineI] * (1-wSOR_) + wSOR_*result[lineI];       
        }      
    }

    std::string SSOR::className()
    {
        return solverMethod_;
    }

    std::shared_ptr<FVMatrixSolver> SSOR::New(spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, Dictionary fvSolutionDict)
    {
        return std::make_shared<SSOR>(aMatrix, bVector, xVector, fvSolutionDict);
    }


    bool SSOR::signToRegistry =
    FVSolverFactory::registerScheme
    (
        SSOR::solverMethod_,
        SSOR::New
    );
       
        


                  



