#ifndef SSOR_H
#define SSOR_H

#include "FVMatrixSolver.h"

/// Class for solving the system of equations using SOR procedure
class SSOR: public FVMatrixSolver
{
    public:

        /// Constructor
        // SSOR( spmat* aMatrix, std::vector<double> &bVector,std::vector<double>& xVector, const int nCells, double wSOR = 0.0);
        SSOR( spmat* aMatrix, std::vector<double> &bVector,std::vector<double>& xVector, double wSOR = 0.0);

        /// Destructor
        virtual ~SSOR();
       
        /// Solver for the system of equations using SOR procedure 
        void doSolverStep() const override ;

    private:
    /// SOR parameter
    double wSOR_;
                       
};

#endif
