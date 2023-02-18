#ifndef JACOBI_H
#define JACOBI_H

#include "FVMatrixSolver.h"

/// Class for solving the system of equations using Jacobi procedure
class SJacobi: public FVMatrixSolver
{
    public:

        /// Constructor
        // SJacobi( spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, const int nCells);
        SJacobi( spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector);
        /// Destructor
        virtual ~SJacobi();
        /// Solver for the system of equations using Jacobi procedure
        std::vector<double> doSolverStep() const override;

    private:
                       
};

#endif
