#include "SSOR.h"

    //Constructor
    SSOR::SSOR(spmat* aMatrix, std::vector<double> &bVector,std::vector<double>& xVector, double wSOR)
    :
    FVMatrixSolver(aMatrix, bVector, xVector),
    wSOR_(wSOR)
    {}

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

        


                  



