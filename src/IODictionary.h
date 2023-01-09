#ifndef IODictionary_H
#define IODictionary_H

#include "IOObject.h"
#include "readHelpOperations.h"

class IODictionary
:
    public IOObject
{
    public:
        // Constructor
        IODictionary(const IOObject& IO);

        virtual void write() const;

        // Destructor
        virtual ~IODictionary() = default;
    
};

#endif 
