
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
#include "fvm.h"

#include "math.h"   //added


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

    //MCN at the point the boundaryField_.nPatches_ from T1 is not correct, but the number of elements boundaryField_.boundaryData_ is not correct
    //MCN the nPatches is deleted in the volume field in the constructor after the following line >> header_.readDict("FoamFile");

    std::cout << std::endl << "Solving for T1" << std::endl;

    FVMatrix TEqn1 (fvm::laplacian(23, T1) + fvm::laplacian(36, T1));
    //FVMatrix TEqn1 (T1);

    TEqn1.createRandomSparseaMatrixbVector();
    TEqn1.resetxVector();
    TEqn1.solve();
    TEqn1.solverPerf().perfShow();
    //TEqn1.resetxVector();
    TEqn1.solve();
    TEqn1.solverPerf().perfShow();
    

    // VolField<scalarField> T2
    // (
    //     IOObject
    //     (
    //         "T2",
    //         time.timeName(),
    //         polyMesh,
    //         IOObject::MUST_READ,
    //         IOObject::NO_WRITE,
    //         true
    //     )
    // );


    // std::cout << std::endl << "Solving for T2" << std::endl;

    // FVMatrix TEqn2(T2);
        
    // TEqn2.createRandomSparseaMatrixbVector();
    // TEqn2.solve();
    // TEqn2.solverPerf().perfShow();
    // //TEqn2.resetxVector();
    // TEqn2.solve();
    // TEqn2.solverPerf().perfShow();

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

    //FVMatrix TEqnTotal = TEqn1 + TEqn2;



    return 0;
}
