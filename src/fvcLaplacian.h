#ifndef FVCLAPLACIAN_H
#define FVCLAPLACIAN_H

#include "FVMatrix.h"
#include "VolField.h"


namespace fvc
{
   //Assuming a constant (e.g K_diffusivity)
   template<typename vectorType> // .cpp file concretizes the vectorType
   std::vector<double> laplacian(const double& K, VolField<vectorType>& vf);
   
}

#include "fvcLaplacianI.h"
#endif 
