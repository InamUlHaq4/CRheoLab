#ifndef fvSolution_H
#define fvSolution_H

#include "Dictionary.h"

class fvSolution
:
public Dictionary

{ 
    public:
    // Constructor
    fvSolution(const IOObject& IO);

    // Destructor
    virtual ~fvSolution(){};

    // Member Functions:

    // Read mandatory subdictionary called "solvers"
    const Dictionary& solverDict(const std::string& field_name, const Dictionary& fvSol);
    
    // Check the existence of relaxation factors, if not, assume predifined value
    void checkRelaxationFactors (const std::string& dictName);

    private:

    // Dictionary of relaxation factors for all the fields
    Dictionary fieldRelaxDict_;

    // Dictionary of relaxation factors for all the equations
    Dictionary eqnRelaxDict_;

    // Dictionary of a specific field in solvers dictionary
    Dictionary solvers_field;
     
};

#endif 
