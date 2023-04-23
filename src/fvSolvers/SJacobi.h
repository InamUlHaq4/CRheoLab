#ifndef JACOBI_H
#define JACOBI_H

#include "FVMatrixSolver.h"

/// Class for solving the system of equations using Jacobi procedure
class SJacobi: public FVMatrixSolver
{
    public:

        /// Constructor
        // SJacobi( spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, const int nCells);
        SJacobi( spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, Dictionary fvSolutionDict);
        /// Destructor
        virtual ~SJacobi();

        static std::string className();

        static std::shared_ptr<FVMatrixSolver> New(spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, Dictionary fvSolutionDict);

        /// Solver for the system of equations using Jacobi procedure
        void doSolverStep() const override;

    private:
        static bool signToRegistry;
        
        // attribute to store the solver method NAme
        static std::string solverMethod_;  


                       
};

#endif
