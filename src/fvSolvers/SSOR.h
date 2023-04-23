#ifndef SSOR_H
#define SSOR_H

#include "FVMatrixSolver.h"

/// Class for solving the system of equations using SOR procedure
class SSOR: public FVMatrixSolver
{
    public:

        /// Constructor
        // SSOR( spmat* aMatrix, std::vector<double> &bVector,std::vector<double>& xVector, const int nCells, double wSOR = 0.0);
        SSOR( spmat* aMatrix, std::vector<double> &bVector,std::vector<double>& xVector, Dictionary fvSolutionDict);

        /// Destructor
        virtual ~SSOR();

        static std::string className();

        static std::shared_ptr<FVMatrixSolver> New(spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, Dictionary fvSolutionDict);
       
        /// Solver for the system of equations using SOR procedure 
        void doSolverStep() const override ;

    private:
    /// SOR parameter
    double wSOR_;

    static bool signToRegistry;
    
    // attribute to store the solver method NAme
    static std::string solverMethod_;      
                    
};

#endif
