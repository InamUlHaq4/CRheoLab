#include "SGaussSiedel.h"

    //Constructor
    SGaussSiedel::SGaussSiedel(spmat* aMatrix, std::vector<double> &bVector,std::vector<double>& xVector)
    :
    FVMatrixSolver(aMatrix,bVector,xVector)
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

        


                  



