#include "SGaussSiedel.h"

    std::string SGaussSiedel::solverMethod_("GaussSiedel");

    //Constructor
    SGaussSiedel::SGaussSiedel(spmat* aMatrix, std::vector<double> &bVector,std::vector<double>& xVector, const Dictionary& fvSolutionDict)
    :
    FVMatrixSolver(aMatrix,bVector,xVector, fvSolutionDict)
    {}

    // Destructor
    SGaussSiedel::~SGaussSiedel()
    {}

    void SGaussSiedel::doSolverStep() const
    {
        //std::vector<double> result(bVector_->size());    

        for(unsigned int lineI = 0; lineI < bVector_->size(); lineI++)
        {
            //result[lineI] = ((*bVector_)[lineI] -  axMultiplicationNoDiagonal(lineI))/(*aMatrix_)[lineI*nCells_+lineI]; 
            (*xVector_)[lineI] = ((*bVector_)[lineI] - aMatrix_->vecMulNoDiagonal(lineI,(*xVector_)))/aMatrix_->getValue(lineI,lineI);
            
            //(*xVector_)[lineI] = result[lineI];                   

        }      
    }

    std::string SGaussSiedel::solverMethod()
    {
        return solverMethod_;
    }

    std::shared_ptr<FVMatrixSolver> SGaussSiedel::New(spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, const Dictionary& fvSolutionDict)
    {
        return std::make_shared<SGaussSiedel>(aMatrix, bVector, xVector, fvSolutionDict);
    }


    bool SGaussSiedel::signToRegistry =
    FVSolverFactory::registerScheme
    (
        SGaussSiedel::solverMethod_,
        SGaussSiedel::New
    );        


                  



