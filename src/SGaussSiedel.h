#ifndef GAUSSSIEDEL_H
#define GAUSSSIEDEL_H

#include "FVMatrixSolver.h"


/// Class for solving the system of equations using Gauss Siedel procedure
class SGaussSiedel: public FVMatrixSolver
{
    public:

        /// Constructor
        //SGaussSiedel( spmat* aMatrix, std::vector<double> &bVector,std::vector<double>& xVector, const int nCells);
        SGaussSiedel( spmat* aMatrix, std::vector<double> &bVector,std::vector<double>& xVector);

        /// Destructor
        virtual ~SGaussSiedel();
        /// Solver for the system of equations using Gauss Siedel procedure
        void doSolverStep()  const override ;

    private:
                       
};

#endif
