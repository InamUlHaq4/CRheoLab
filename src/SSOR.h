#ifndef SOR_H
#define SOR_H

#include "FVMatrixSolver.h"
#include "lilSpmat.h"

/// Class for solving the system of equations using SOR procedure
class SSOR: public FVMatrixSolver
{
    public:

        /// Constructor
        SSOR( spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, const int nCells, double wSOR = 0.0);

        /// Destructor
        virtual ~SSOR();
       
        /// Solver for the system of equations using SOR procedure 
        std::vector<double> doSolverStep() const override ;

    private:
    /// SOR parameter
    double wSOR_;
                       
};

#endif
