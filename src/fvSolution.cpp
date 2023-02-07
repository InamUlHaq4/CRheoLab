#include "fvSolution.h"

fvSolution::fvSolution(const IOObject& IO)
:
Dictionary(IO)
{
   Dictionary::read(),
   Dictionary::subDict("solvers"); //check if mandatory subDictionary called "solvers" exists, if not throw an error.
}

const Dictionary& fvSolution::solverDict(const std::string& field_name, const Dictionary& fvSol) 
{
   solvers_field = fvSol.subDict("solvers").subDict(field_name);
   return fvSol.subDict("solvers").subDict(field_name);
}

void fvSolution::checkRelaxationFactors (const std::string& dictName)
{
   dictMap& relaxation_map (Dictionary::data());

    if (relaxation_map.count(dictName))

    {  
       const Dictionary& relaxDict = *relaxation_map.at(dictName);

       if (relaxDict.data().count("fields") || relaxDict.data().count("equations"))
        {
            
            if (relaxDict.data().count("fields"))
            {
                fieldRelaxDict_ = relaxDict.subDict("fields");
            }
 
            if (relaxDict.data().count("equations"))
            {
                eqnRelaxDict_ = relaxDict.subDict("equations");
            }
            
        }     
    }

    else
    {
        std::cout << "Relaxation factors not found. Proceeding with no-relaxation. " << std::endl;
    }
}
