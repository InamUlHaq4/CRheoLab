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

    FVMatrix (Mesh& mesh, const std::string matrixFormat, const std::string matrixType);

    unsigned int nCells_;
    spmat* aMatrix_;
    /// \f$ b \f$ vector
    std::vector<double> bVector_;
    /// Destructor
    virtual ~FVMatrix();

    private:
           
};

#endif
