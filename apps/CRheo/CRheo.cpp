
#include "printUtils.H"
#include "Dictionary.h"
#include "VolField.h"
#include "Mesh.h"
#include "fvSolution.h"

int main()
{
    RunTime time;

    Mesh mesh(time);

    #include "createFields.H"

    while(time.loop())
    {
        std::cout << "time [s]: " << time.time() << std::endl;

        p = p + p; 

        volScalarField p2 = p + p;

        std::cout << U << std::endl;  

        p2.write();
    }

    return 0;
}
