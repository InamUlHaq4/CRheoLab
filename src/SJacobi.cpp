#include "SJacobi.h"

    //Constructor
    SJacobi::SJacobi(spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector)
    :
    FVMatrixSolver(aMatrix,bVector,xVector)
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

        


                  



