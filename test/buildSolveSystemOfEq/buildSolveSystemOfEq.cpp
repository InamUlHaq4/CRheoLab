
#include "Mesh.h"
#include "RunTime.h"
#include "IODictionary.h"
#include "VolField.h"
#include "IOObject.h"
#include "Dictionary.h"
#include "FVSystem.h"

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

int main()
{

    std::cout << "Current path is : " << getExecutablePath() << std::endl;

    checkCaseStructure();
    
    RunTime time;

    Mesh polyMesh(time);
    
 

    //Testing System of equations    std::vector<double> T1(polyMesh.nCells_,0.);
    std::vector<double> T1(polyMesh.nCells_,0.);
    //std::vector<double> T2(polyMesh.nCells_,0.);
    //std::vector<double> T3(polyMesh.nCells_,0.);    
    //std::cout << "T: " << T << std::endl;
    FVSystem TEquation1(polyMesh, T1);
   // FVSystem TEquation1(polyMesh, T1, jacobi, 1E-15, 1E-15);
  //  FVSystem TEquation2(polyMesh, T2, gaussSidel, 1E-15, 1E-15);
   // FVSystem TEquation3(polyMesh, T3, SOR, 1E-15, 1E-15, 1.2);
    //std::cout << ">> solve " << std::endl;
  //  std::cout << ">> Jacobi " << std::endl;
    //TEquation1.setSolver("Jacobi");
    TEquation1.solve();
    TEquation1.solve();
    TEquation1.resetxVector();
    TEquation1.setSolver("Jacobi");
    TEquation1.solve();
    TEquation1.resetxVector();
    TEquation1.setSolver("GaussSiedel");
    TEquation1.solve();
    std::cout << "end solve " << std::endl;


    return 0;
}
