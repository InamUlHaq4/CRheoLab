#include "SJacobi.h"

    //Constructor
    SJacobi::SJacobi(FVMatrix* fvMatrix,std::vector<double>* xVector, const int nCells)
    :
    FVMatrixSolver(fvMatrix,xVector, nCells)
    {}
   
    // Destructor
    SJacobi::~SJacobi()
    {}

    std::vector<double> SJacobi::doSolverStep() const  
    {

        std::vector<double> result(nCells_);    

        for(unsigned int lineI = 0; lineI < nCells_; lineI++)
        {
            //result[lineI] = ((*bVector_)[lineI] -  axMultiplicationNoDiagonal(lineI))/(*aMatrix_)[lineI*nCells_+lineI];            
            result[lineI] = ((fvMatrix_->bVector_)[lineI] - fvMatrix_->aMatrix_->vecMulNoDiagonal(lineI,(*xVector_)))/fvMatrix_->aMatrix_->getValue(lineI,lineI);
        }      
        return result;
    }

        


                  



