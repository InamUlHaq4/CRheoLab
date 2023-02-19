
#include "Mesh.h"
#include "RunTime.h"

//#include "IODictionary.h"
//#include "IOObject.h"

#include "Dictionary.h"
#include "VolField.h"
//#include "VolFieldI.h"
#include "VolFieldOperations.h"

//#include "Boundary.h"
//#include "BoundaryI.h"

//#include "fvBoundaryConditionsField.h"

#include "FVMatrix.h"

//#include "fvm.h"

//#include "fvc.h"


/*
void foo(VolField<std::vector<double>>& field)
{
    Dictionary& banana2 = field.mesh().lookup<Dictionary>( "transportProperties");
    double d1 = banana2.lookup<double>("abc");

    VolField<std::vector<double>> banana
    (
        IOObject
        (
            "p",
            field.mesh().time().constant(),
            field.mesh(),
            IOObject::NO_READ,
            IOObject::NO_WRITE,
            false
        ),
         d1
    );

    field = field+banana;

    
}
*/
int main()
{

    std::cout << "Current path is : " << getExecutablePath() << std::endl;

    checkCaseStructure();
    
    RunTime time;    

    Mesh polyMesh(time);
   
    //Testing System of equations    std::vector<double> T1(polyMesh.nCells_,0.);
    
    VolField<scalarField> T1
    (
        IOObject
        (
            "T1",
            time.timeName(),
            polyMesh,
            IOObject::MUST_READ,
            IOObject::NO_WRITE,
            true
        )
    );

    FVMatrix TEqn1(T1);
    
    TEqn1.createRandomSparseaMatrixbVector();
    TEqn1.solve();
    TEqn1.solverPerf().perfShow();
    TEqn1.resetxVector();
    TEqn1.solve();
    TEqn1.solverPerf().perfShow();
    
    VolField<scalarField> T2
    (
        IOObject
        (
            "T2",
            time.timeName(),
            polyMesh,
            IOObject::MUST_READ,
            IOObject::NO_WRITE,
            true
        )
    );

    FVMatrix TEqn2(T2);
        
    TEqn2.createRandomSparseaMatrixbVector();
    TEqn2.solve();
    TEqn2.solverPerf().perfShow();
    TEqn2.resetxVector();
    TEqn2.solve();
    TEqn2.solverPerf().perfShow();

    //std::vector<double> TEquation2 = fvc::laplacian(1.0,T1);

    //TEquation1.solve();

    /*
    TEquation1.solve();
    TEquation1.solve();
    TEquation1.resetxVector();
    TEquation1.setSolver("Jacobi");
    TEquation1.solve();
    TEquation1.resetxVector();
    TEquation1.setSolver("GaussSiedel");
    TEquation1.solve();
    std::cout << "end solve " << std::endl; 
    */


    return 0;
}
