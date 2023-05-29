#include "printUtils.H"
#include "Dictionary.h"
#include "VolField.h"
#include "Mesh.h"
#include "IOObject.h"

int main()
{
    RunTime time;

    Mesh mesh(time);

    volScalarField p 
    (
        IOObject
        (
            "p",
            time.timeName(),
            mesh,
            IOObject::MUST_READ,
            IOObject::NO_WRITE
        )
    );

    volScalarField banana 
    (
        IOObject
        (
            "banana",
            time.timeName(),
            mesh,
            IOObject::MUST_READ,
            IOObject::NO_WRITE
        )
    );
    
    volScalarField test1 = p + p;
    volScalarField test2 = p * banana;
    volScalarField test3 = p / banana;
    test1.write();
    test2.write();
    test3.write();

    volScalarField test4 = p + banana;
    test4.write();


    std::cout << "nsns" << std::endl;

    return 0;
}
