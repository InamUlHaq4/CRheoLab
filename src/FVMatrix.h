#ifndef FVMATRIX_H
#define FVMATRIX_H


#include <vector>
#include "Mesh.h"
#include "Dictionary.h"

#include "VolField.h"

#include "lilSpmat.h"
#include "csrSpmat.h"

#include "FVMatrixSolver.h"
#include "SJacobi.h"
#include "SGaussSiedel.h"
#include "SSOR.h"
#include "SolverPerf.h"


// An abstract class for the solver of the system of equations

//template< typename vectorType> - For now just double - thje template will be implemented in the future
class FVMatrix
{
    
    public:

    FVMatrix(VolField<scalarField>& field);
    
    spmat* aMatrix_;
    
    std::vector<double> bVector_;

    SolverPerf solverPerf_;

    VolField<scalarField>& field_;

     
    inline double residualValue();

      
    inline double residualNormFactor();


    void solve();

    virtual ~FVMatrix();



    private:
           
};

#endif
