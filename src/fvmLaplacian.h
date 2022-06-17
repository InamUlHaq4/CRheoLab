#ifndef FVMLAPLACIAN_H
#define FVMLAPLACIAN_H

#include "FVMatrix.h"
#include "VolField.h"


namespace fvm
{
   //Assuming a constant (e.g K_diffusivity)
   template<typename vectorType> // .cpp file concretizes the vectorType
   FVMatrix laplacian(FVMatrix& FVM,const double& K, VolField<vectorType>& vf);
   
}


#endif 
