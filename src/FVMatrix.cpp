#include "FVMatrix.h"
#include <vector>
#include "FVMatrixOperators.h"

//Constructor
FVMatrix::FVMatrix(Mesh& mesh, const std::string matrixFormat, const std::string matrixType )
{
   unsigned int nCells=mesh.nCells_;
   bVector_.resize(nCells);

   if (matrixFormat== "lOLists")
        aMatrix_ = new lilSpmat(nCells,nCells);
    else if (matrixFormat== "CSR")
    {
        
        if (matrixType== "full"){
            aMatrix_ = new csrSpmat(nCells);             
        }
        else if (matrixType== "sparse") {
            aMatrix_ = new csrSpmat(mesh);
        }
        else {
            std::cout << "ERROR: Unindentified Matrix type";
            exit(0);
        }
    }
    else {
        std::cout << "ERROR: Unindentified Matrix format";
        exit(0);
    }


}
 
FVMatrix::~FVMatrix()
{
    //std::cout << "delete aMAtrix_" << std::endl;
    delete aMatrix_;
}
