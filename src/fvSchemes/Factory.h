#pragma once

#include <iostream> 
#include <memory> 
#include <map>

// Templated Class to deal with the Object registry fot the mathematical Operators
template<typename operatorType>
class Factory
{
    public:
        // This is a function pointer to the constructor of the defined scheme type
        // which are going to be defined in the derived classes from the Laplacian
        using createScheme = std::shared_ptr<operatorType>(*)();

        // The "registerScheme" function is a static member of the "Factory" class, it takes in a 
        // string "name" and a "createScheme" object called "scheme". The purpose of this function
        // is to register a new scheme in the "registry" static map instance.
        // This function is used in the end of each derived class .cpp file to register its existence.
        static bool registerScheme( const std::string& name, createScheme scheme )
        {
            // The "registry" map is accessed through a reference variable "registry" which
            // is assigned the value returned by the "getRegistry()" function. This function
            // returns a reference to the static map "registry".
            std::map< std::string, Factory::createScheme >& registry = getRegistry();
            // The if statement checks if the given "name" exists in the "registry" map by 
            // using the "std::map::find()" function. If the function returns "registry.end()",
            // it means that the given scheme does not exist in the map, and the function proceeds
            // to register the scheme with the given name by assigning it to the "registry" map.
            // The function then returns true.
            if(registry.find(name) == registry.end())
            { 
                registry[name] = scheme;
                return true;
            }
            // Else, means that the "name" already exists in the map, then the function returns false,
            // indicating that the registration was not successful, so skip over-registering it.
            return false;
        };

        // This is a static std shared smart pointer of the derived schemes from the 
        // Laplacian Class
        static std::shared_ptr<operatorType> New(const std::string& name)
        {
            std::map< std::string, Factory::createScheme >& registry = getRegistry();
            auto it = registry.find(name);
            if (it != registry.end())
            {
                return it->second(); 
            }
            else
            {
                std::cout << "\nDefined model \""+name+"\" not found.\nAvailable models are: \n " << std::endl;
                printRegistryNames();
                std::cout << "Check definitions in the System/fvSchemes file.\n\n\n\t\tProgram Exiting ...\n\n\n" << std::endl;
                exit(0);
            }
            return nullptr;
        };

        // This is a static function that is going to print the registered schemes 
        // available to be used 
        static void printRegistryNames()
        {
            std::map< std::string, Factory::createScheme >& registry = getRegistry();
            for(const auto& it : registry)
            {
                std::cout << "\t" << it.first <<"\n";
            }
            std::cout <<"\n";    
        };
        
    private:
        // This Data member will store a map data type from the std library between 
        // the created schemes available and the shared pointer to it.
        // static std::map<std::string, createScheme>* registry;
        static std::map<std::string, createScheme>& getRegistry()
        {
            static std::map<std::string, Factory::createScheme> registry;
            return registry;
        };        
};
// #endif
