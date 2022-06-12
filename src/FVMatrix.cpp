#include "FVMatrix.h"
#include <vector>



//Constructor
FVMatrix::FVMatrix(const int nCells, const std::string matrixFormat, const std::string matrixType ):
nCells_(nCells)
{
    nCells_ = nCells;
    bVector_.resize(nCells_);

   if (matrixFormat== "lOLists")
        aMatrix_ = new lilSpmat(nCells_,nCells_);
    else if (matrixFormat== "CSR")
        if (matrixType== "full"){
            aMatrix_ = new csrSpmat(nCells_);             
        }
        else if (matrixType== "sparse") {
            aMatrix_ = new csrSpmat(mesh);
        }
        else {
            std::cout << "ERROR: Unindentified Matrix type";
            exit(0);
        }

    else {
        std::cout << "ERROR: Unindentified Matrix format";
        exit(0);
    }


}
 
FVMatrix::~FVMatrix()
{}
