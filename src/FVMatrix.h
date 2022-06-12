#ifndef FVMATRIX_H
#define FVMATRIX_H

#include "Mesh.h"
#include "lilSpmat.h"
#include "csrSpmat.h"

//**
/// An abstract class for the solver of the system of equations
class FVMatrix
{
    public:

    FVMatrix (const int ncells, const std::string matrixFormat, const std::string matrixType);
    /// \f$ A \f$ matrix
    spmat* aMatrix_;
    /// \f$ b \f$ vector
    std::vector<double> bVector_;
    /// Number of the elements in the system i.e. the size of the system
    unsigned int nCells_;


    private:
           
};

#endif
