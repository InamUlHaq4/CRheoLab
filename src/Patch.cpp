#include "Patch.h"


Patch::Patch(std::string name, std::string type, int nFaces, int startFace)
:   name_(name),
    type_(type),
    nFaces_(nFaces),
    startFace_(startFace)
{
}


const std::string& Patch::name() const
{
    return name_;
}

//Getters
int Patch::nFaces() const
{
    return nFaces_;
}


int Patch::startFace() const
{
    return startFace_;
}
