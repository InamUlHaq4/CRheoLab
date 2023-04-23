#include "SJacobi.h"

    std::string SJacobi::solverMethod_("Jacobi");

    //Constructor
    SJacobi::SJacobi(spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, Dictionary fvSolutionDict)
    :
    FVMatrixSolver(aMatrix,bVector,xVector, fvSolutionDict)
    {}
   
    // Destructor
    SJacobi::~SJacobi()
    {}

    void SJacobi::doSolverStep() const  
    {

        std::vector<double> result(bVector_->size());    

        for(unsigned int lineI = 0; lineI < bVector_->size(); lineI++)
        {       
            result[lineI] = ((*bVector_)[lineI] - aMatrix_->vecMulNoDiagonal(lineI,(*xVector_)))/aMatrix_->getValue(lineI,lineI);
        }      
        (*xVector_)=result;
    }

    std::string SJacobi::className()
    {
        return solverMethod_;
    }

    std::shared_ptr<FVMatrixSolver> SJacobi::New(spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, Dictionary fvSolutionDict)
    {
        return std::make_shared<SJacobi>(aMatrix, bVector, xVector, fvSolutionDict);
    }


    bool SJacobi::signToRegistry =
    FVSolverFactory::registerScheme
    (
        SJacobi::solverMethod_,
        SJacobi::New
    );
       


                  



