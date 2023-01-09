#include "IODictionary.h"


IODictionary::IODictionary(const IOObject& IO)
:
    IOObject(IO)
{}


void IODictionary::write() const
{
    throw std::runtime_error("write() not implemented for IOObject");
}

