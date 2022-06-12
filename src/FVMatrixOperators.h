#ifndef FVSYSTEMOPERATORS_H
#define FVSYSTEMOPERATORS_H

#include "FVMatrix.h"

// Output vectorField to screen
inline FVMatrix operator+(FVMatrix& FVSa, FVMatrix& FVSb)
{
    FVMatrix result = FVSa;
    //result.bVector_ += FVSb.bVector_;
    //result.aMatrix_ += FVSb.aMatrix_;

    return result;
}   
#endif
