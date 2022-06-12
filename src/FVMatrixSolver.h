#ifndef FVMATRIXSOLVER_H
#define FVMATRIXSOLVER_H

#include "Mesh.h"
#include "FVMatrix.h"

//**
/// An abstract class for the solver of the system of equations
class FVMatrixSolver
{
    public:

        /// Default constructor
        FVMatrixSolver(FVMatrix* fvMat, std::vector<double>* xVector,const int nCells);

        /// Destructor
        virtual ~FVMatrixSolver();

        // Member Functions
        // double axMultiplicationNoDiagonal(const unsigned int& i) const;
        
        /// Function to solve the system of equations, defined in the specific solver classes i.e. in the Jacobi, Gauss Siedel, and SOR classes.
        virtual  std::vector<double> doSolverStep() const = 0;
       
        
    protected:
        /// \f$ A \f$ matrix
        FVMatrix* fvMatrix_;
        /// \f$ X \f$ vector
        std::vector<double>* xVector_;
        /// Number of the elements in the system i.e. the size of the system
        unsigned int nCells_;


    private:
           
};

#endif
