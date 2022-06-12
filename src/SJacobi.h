#ifndef JACOBI_H
#define JACOBI_H

#include "FVMatrixSolver.h"
#include "FVMatrix.h"

/// Class for solving the system of equations using Jacobi procedure
class SJacobi: public FVMatrixSolver
{
    public:

        /// Constructor
        SJacobi( FVMatrix* fvMatrix,std::vector<double>* xVector, const int nCells);

        /// Destructor
        virtual ~SJacobi();
        /// Solver for the system of equations using Jacobi procedure
        std::vector<double> doSolverStep() const override;

    private:
                       
};

#endif
