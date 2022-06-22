
#include "Mesh.h"
#include "RunTime.h"

//#include "IODictionary.h"
//#include "IOObject.h"

#include "Dictionary.h"
#include "VolField.h"
#include "VolFieldI.h"
#include "VolFieldOperations.h"

#include "Boundary.h"
#include "BoundaryI.h"

#include "fvBoundaryConditionsField.h"

#include "FVMatrix.h"

#include "fvm.h"



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
            fileAction::NO_READ,
            fileAction::NO_WRITE,
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
            "T",
            polyMesh.time().constant(),
            polyMesh,
            fileAction::NO_READ,
            fileAction::NO_WRITE,
            false
        )
    );

    FVMatrix TEquation1(T1);
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

    // Testing constructor from the constructor initialization in the VolField class
    VolField<scalarField> T
    (
        IOObject
        (
            "T",
            time.timeName(),
            polyMesh,
            fileAction::MUST_READ,
            fileAction::NO_WRITE,
            false
        )
    );
    fvBoundaryConditionsField<scalarField> TBoundaryCondition(T);

    // //** --- Tests WdCG ---------------------- **//
    // FVMatrix TMatrix(T);
    // std::vector<double> diagonalTerms(9,0.0);
    // double diffusionK=1e-3;

    // long unsigned int patchesSize = T.mesh().nPatches_;
    // for ( long unsigned int patchI = 0; patchI < patchesSize; patchI++)
    // { 
    //     std::cout << "This is the patch: " << patchI << std::endl;
    //     // Loading the faces controls for this patch
    //     int sizeOfPatch( TBoundaryCondition.coefficientsData().at(patchI).gradientInternalCoeffs.size() );
    //     int startPatchFaceID = T.mesh().patchList_[patchI].startFace();

    //     // Looping in all the faces for this patch
    //     for (int faceI = 0; faceI < sizeOfPatch; faceI++)
    //     { 
    //         std::cout << "\t\tThis is the Patch face: " << startPatchFaceID+faceI << std::endl;
    //         // Retrieving the boundary face owner cell ID
    //         int ownInd = T.mesh().faceList_[startPatchFaceID+faceI].getOwner()->ID_;
            
    //         vector3 areaVec = T.mesh().faceList_[startPatchFaceID+faceI].getAreaVector();
    //         double  areaMag = mag(areaVec);

    //         ((ownInd == 0) || (ownInd == 3) || (ownInd == 6) ) ? (diffusionK = 1e-3) : (diffusionK = 100);

    //         std::cout << "\t\t\t\tIt's Owner Cell is the cell: " << ownInd << std::endl;
    //         // Loading the values to added for the laplacian term
    //         double valueToAddDiagonal( TBoundaryCondition.coefficientsData().at(patchI).gradientInternalCoeffs.at(faceI));
    //         double valueToAddSource( TBoundaryCondition.coefficientsData().at(patchI).gradientBoundaryCoeffs.at(faceI));
            
    //         // Adding the loaded values to the proper places
    //         TMatrix.aMatrix_->addValue(ownInd,ownInd,valueToAddDiagonal*areaMag);
    //         diagonalTerms.at(ownInd)+=-diffusionK*valueToAddDiagonal*areaMag;
    //         TMatrix.bVector_.at(ownInd)+=diffusionK*valueToAddSource*areaMag;
    //     }
    // }
    // //** ---End-of-Tests----- WdCG ----------- **//

    return 0;
}
