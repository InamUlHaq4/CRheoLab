
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

#include "fvc.h"

#include "./fvSchemes/laplacian/Laplacian.h"

int main()
{

    std::cout << "Current path is : " << getExecutablePath() << std::endl;

    checkCaseStructure();
    
    RunTime time;

    Mesh polyMesh(time);

    // std::shared_ptr<Laplacian> laplacianCreator;
    // Laplacian::banana();
    std::shared_ptr<Laplacian> laplacianCreator = Laplacian::New("Orthogonal");
    std::cout << "\n\n----------------------\n\n" << std::endl;
    std::cout << "I am a "; laplacianCreator->print();
    std::cout << "\n\n----------------------\n\n" << std::endl;
    laplacianCreator = Laplacian::New("Corrected");
    std::cout << "\n\n----------------------\n\n" << std::endl;
    std::cout << "I am a "; laplacianCreator->print();
    std::cout << "\n\n----------------------\n\n" << std::endl;
    laplacianCreator = Laplacian::New("NonExisting");
    
            
            // #include "../../src/fvSchemes/fvSchemes.h"
            // laplacianFactoryRaw laplacianCreator;
            // laplacianBase* lapRawOrthoA = laplacianCreator.create(OrthoA);
            // laplacianBase* lapRawOrthoB = laplacianCreator.create(OrthoB);
            // laplacianBase* lapRawOrthoC = laplacianCreator.create(OrthoC);
            
            // std::cout << "\n\n----------------------\n\n" << std::endl;
            // std::cout << "I am a "+lapRawOrthoA->getOperator() << std::endl;
            // std::cout << "I am a "+lapRawOrthoB->getOperator() << std::endl;
            // std::cout << "I am a "+lapRawOrthoC->getOperator() << std::endl;
            // std::cout << "\n\n----------------------\n\n" << std::endl;
            // std::cout << lapRawOrthoA->getType() << std::endl;
            // std::cout << lapRawOrthoB->getType() << std::endl;
            // std::cout << lapRawOrthoC->getType() << std::endl;
            // std::cout << "\n\n----------------------\n\n" << std::endl;
            
            // delete lapRawOrthoA;
            // delete lapRawOrthoB;
            // delete lapRawOrthoC;

            // laplacianFactorySmart laplacianSmartSharedCreator;
            // std::shared_ptr<laplacianBase> lapSmartSharedOrthoA = laplacianSmartSharedCreator.create(OrthoA);
            // std::shared_ptr<laplacianBase> lapSmartSharedOrthoB = laplacianSmartSharedCreator.create(OrthoB);
            // std::shared_ptr<laplacianBase> lapSmartSharedOrthoC = laplacianSmartSharedCreator.create(OrthoC);
            
            // std::cout << "\n\n----------------------\n\n" << std::endl;
            // std::cout << "I am a "+lapSmartSharedOrthoA->getOperator() << std::endl;
            // std::cout << "I am a "+lapSmartSharedOrthoB->getOperator() << std::endl;
            // std::cout << "I am a "+lapSmartSharedOrthoC->getOperator() << std::endl;
            // std::cout << "\n\n----------------------\n\n" << std::endl;
            
            // std::cout << lapSmartSharedOrthoA->getType() << std::endl;
            // std::cout << lapSmartSharedOrthoB->getType() << std::endl;
            // std::cout << lapSmartSharedOrthoC->getType() << std::endl;
            // std::cout << "\n\n----------------------\n\n" << std::endl;
            
            // lapSmartSharedOrthoB->operatorType="MODIFIED Laplacian Operator";
            // std::cout << "\n\n----------------------\n\n" << std::endl;
            // std::cout << lapSmartSharedOrthoA->getType() << std::endl;
            // std::cout << lapSmartSharedOrthoB->getType() << std::endl;
            // std::cout << lapSmartSharedOrthoC->getType() << std::endl;
            // std::cout << "\n\n----------------------\n\n" << std::endl;

            // laplacianBase::operatorType="2nd TIME MODIFIED Laplacian Operator";
            // std::cout << "\n\n----------------------\n\n" << std::endl;
            // std::cout << lapSmartSharedOrthoA->getType() << std::endl;
            // std::cout << lapSmartSharedOrthoB->getType() << std::endl;
            // std::cout << lapSmartSharedOrthoC->getType() << std::endl;
            // std::cout << "\n\n----------------------\n\n" << std::endl;

    // //Testing System of equations    std::vector<double> T1(polyMesh.nCells_,0.);
    
    // VolField<scalarField> T1
    // (
    //     IOObject
    //     (
    //         "T",
    //         time.timeName(),
    //         polyMesh,
    //         fileAction::MUST_READ,
    //         fileAction::NO_WRITE,
    //         true
    //     )
    // );

    // FVMatrix TEquation1 = fvm::laplacian(1.0,T1);
 
    // TEquation1.solve();
    // TEquation1.solverPerf_.perfShow();


    // // FvFactory FVNULL;
    // // FVNULL.create(NULL);
    

    // std::vector<double> TEquation2 = fvc::laplacian(1.0,T1);
    



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
    // VolField<scalarField> T
    // (
    //     IOObject
    //     (
    //         "T",
    //         time.timeName(),
    //         polyMesh,
    //         fileAction::MUST_READ,
    //         fileAction::NO_WRITE,
    //         false
    //     )
    // );
    // fvBoundaryConditionsField<scalarField> TBoundaryCondition(T);

    return 0;
}
