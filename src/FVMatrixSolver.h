#ifndef FVMATRIXSOLVER_H
#define FVMATRIXSOLVER_H

#include "Mesh.h"
#include "lilSpmat.h"

//**

class FVMatrixSolver
{
    public:

        // Default constructor
        FVMatrixSolver(lilSpmat& mataMatrix,  std::vector<double>& bVector, std::vector<double>& xVector,const int nCells);

        // Destructor
        virtual ~FVMatrixSolver();

        // Member Functions
        // double axMultiplicationNoDiagonal(const unsigned int& i) const;
        
        virtual  std::vector<double> doSolverStep() const = 0;
       
        
    protected:
        lilSpmat* const aMatrix_;
        std::vector<double>* bVector_;
        std::vector<double>* xVector_;
        unsigned int nCells_;


    private:
           
};

#endif
