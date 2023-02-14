#include "Laplacian.h"

Laplacian::Laplacian(): name_("Laplacian"), discretizationScheme_("Gauss")
{   // Todo WdCG
    std::cout << "Base class is being created" << std::endl;
}

// bool Laplacian::Factory::registerScheme( const std::string& name, createScheme scheme )
// {
//     // If the find is in the end of the registry map then, register the given scheme and 
//     // return true
//     std::map< std::string, Laplacian::Factory::createScheme >& registry = getRegistry();
//     if(registry.find(name) == registry.end())
//     { 
//         registry[name] = scheme;
//         return true;
//     }
//     // Else means that the scheme is already registered, so skip over-registering it and
//     // return false
//     return false;
// }

// std::shared_ptr<Laplacian> Laplacian::Factory::New( const std::string& name )
// {
//     std::map< std::string, Laplacian::Factory::createScheme >& registry = getRegistry();
//     auto it = registry.find(name);
//     if (it != registry.end())
//     {
//         return it->second(); 
//     }
//     else
//     {
//         std::cout << "\nDefined model \""+name+"\" not found.\nAvailable models are: \n " << std::endl;
//         printRegistryNames();
//         std::cout << "Check definitions in the System/fvSchemes file. Code Exiting!" << std::endl;
//         exit(0);
//     }
        
//     return nullptr;
// }

// void Laplacian::Factory::printRegistryNames()
// {
//     std::map< std::string, Laplacian::Factory::createScheme >& registry = getRegistry();
//     for(const auto& it : registry)
//     {
//         std::cout << "\t" << it.first <<"\n";
//     }
//     std::cout <<"\n";    
// }

// std::map<std::string, Laplacian::Factory::createScheme> Laplacian::Factory::registry;
// std::map< std::string, Laplacian::Factory::createScheme >& Laplacian::Factory::getRegistry()
// {
//     static std::map<std::string, Laplacian::Factory::createScheme> registry;
//     return registry;
// }

const std::string& Laplacian::operatorType()
{
  return name_;
}
const std::string& Laplacian::discretizationScheme()
{
  return discretizationScheme_ ;
}
