#ifndef FVMATRIXSOLVER_H
#define FVMATRIXSOLVER_H

//#include "Mesh.h"
#include "spmat.h"


// An abstract class for the solver of the system of equations
class FVMatrixSolver
{
    public:

        /// Default constructor
        // FVMatrixSolver(spmat* aMatrix,  std::vector<double>& bVector, std::vector<double>& xVector,const int nCells);

        FVMatrixSolver(spmat* aMatrix,  std::vector<double>& bVector, std::vector<double>& xVector);

        /// Destructor
        virtual ~FVMatrixSolver();

        // Member Functions
        // double axMultiplicationNoDiagonal(const unsigned int& i) const;
        
        /// Function to solve the system of equations, defined in the specific solver classes i.e. in the Jacobi, Gauss Siedel, and SOR classes.
        virtual  void doSolverStep() const = 0;
       
        
    protected:
        /// \f$ A \f$ matrix
        spmat* const aMatrix_;
        /// \f$ b \f$ vector
        std::vector<double>* bVector_;
        /// \f$ X \f$ vector
        std::vector<double>* xVector_;

    private:
           
};

#endif
