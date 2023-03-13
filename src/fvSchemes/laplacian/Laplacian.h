// #ifndef Laplacian_H
// #define Laplacian_H
#pragma once

#include "./fvSchemes/Factory.h"

class Laplacian : public Factory<Laplacian>
{

private:
    // Mathematical Operator name Laplacian only
    const std::string name_;
    // Mathematical Operator discretization method Gauss only
    const std::string discretizationScheme_;

public:
 
    // Constructor
    Laplacian();

    // Destructor
    virtual ~Laplacian(){};
 
    const std::string& name() const
    {
        return name_;
    }

    static std::shared_ptr<Laplacian> New(const std::string& name )
    {
        return Factory::New(name);
    };
    
    // Getters:
    // Laplacian Only
    const std::string& operatorType();
    
    // Gauss  only option
    const std::string& discretizationScheme(); 
    
    // Define the interpolation used for calculating the diffusivity gamma at the face in the derived classes
    virtual const std::string& interpolationScheme() = 0;

    // Define the kind of non-orthogonal correction in the derived classes
    virtual const std::string& nonOrthogonalCorrectionScheme() = 0;

    // Setters:

    // Print:
    virtual void print() = 0;

};

// #include <memory> 
// #include <iostream> 
// #include <map>

// // Nested Class to deal with the Object registry
// template<typename operatorType>
// class Factory
// {
//     public:
//         // This is a function pointer to the constructor of the defined scheme type
//         // which are going to be defined in the derived classes from the Laplacian
//         using createScheme = std::shared_ptr<operatorType>(*)();

//         // Todo This is a static boolean that will register a existence of a scheme 
//         // ? Why this needs to be static?
//         static bool registerScheme( const std::string& name, createScheme scheme )
//         {
//             // If the find is in the end of the registry map then, register the given scheme and 
//             // return true
//             std::map< std::string, Factory::createScheme >& registry = getRegistry();
//             if(registry.find(name) == registry.end())
//             { 
//                 registry[name] = scheme;
//                 return true;
//             }
//             // Else means that the scheme is already registered, so skip over-registering it and
//             // return false
//             return false;
//         };
//         // bool registerScheme( const std::string& name, createScheme scheme );

//         // This is a static std smart shared pointer of the derived schemes from the 
//         // Laplacian Class
//         static std::shared_ptr<operatorType> New(const std::string& name)
//         {
//             std::map< std::string, Factory::createScheme >& registry = getRegistry();
//             auto it = registry.find(name);
//             if (it != registry.end())
//             {
//                 return it->second(); 
//             }
//             else
//             {
//                 std::cout << "\nDefined model \""+name+"\" not found.\nAvailable models are: \n " << std::endl;
//                 printRegistryNames();
//                 std::cout << "Check definitions in the System/fvSchemes file. Code Exiting!" << std::endl;
//                 exit(0);
//             }
                
//             return nullptr;
//         };

//         // This is a static function that is going to print the registered schemes 
//         // available to be used 
//         static void printRegistryNames()
//         {
//             std::map< std::string, Factory::createScheme >& registry = getRegistry();
//             for(const auto& it : registry)
//             {
//                 std::cout << "\t" << it.first <<"\n";
//             }
//             std::cout <<"\n";    
//         };
        
//     private:
//         // This Data member will store a map data type from the std library between 
//         // the created schemes available and the shared pointer to it.
//         // static std::map<std::string, createScheme>* registry;
//         static std::map<std::string, createScheme>& getRegistry()
//         {
//             static std::map<std::string, Factory::createScheme> registry;
//             return registry;
//         };        
// };

// #endif