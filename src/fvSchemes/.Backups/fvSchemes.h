// #ifndef FVSCHEMES_H
// #define FVSCHEMES_H
#pragma once

// #include "Dictionary.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// First we create an abstract class that defines what is suppose to be a fvScheme
// : public IODictionary
class laplacianBase 
{
    public:
        static std::string operatorType;
        static std::map<std::string,laplacianBase*> laplacianRegistry;

        // Constructor
        laplacianBase(){}
        // Destructor
        virtual ~laplacianBase(){ std::cout << "laplacianBase _·_ destructor called." << std::endl; }

        static std::string getOperator() { return operatorType ; }
        virtual std::string getType() = 0;
        
};
// We must define the static variables somewhere in order to not have a unresolved external link compiling errors
std::string laplacianBase::operatorType="Laplacian Operator";
std::map<std::string,laplacianBase*> laplacianMap;

// The class exists from the others that is inherited from the abstract class
// So the Laplacian Gradient and etc are fvSchemes thus we create a FvFactory in the end
// whose the job is create instances of each of these fvschemes on demand as smart pointers
class lapOrthogonalA : public laplacianBase
{
    public:
        std::string schemeType;
 
        // Constructor
        lapOrthogonalA(){ schemeType="Gauss Linear Orthogonal _A_ Scheme"; }
        // Destructor
        ~lapOrthogonalA(){ std::cout << "lapOrthogonal _A_ destructor called." << std::endl;}
 
        std::string getType() override { return "I am a "+this-> getOperator()+" using a "+schemeType; }
    
};

class lapOrthogonalB : public laplacianBase
{
    public:
        std::string schemeType;
    
        // Constructor
        lapOrthogonalB(){ schemeType="Gauss Linear Orthogonal _B_ Scheme"; }
        // Destructor
        ~lapOrthogonalB(){ std::cout << "lapOrthogonal _B_ destructor called." << std::endl;}

        std::string getType() override { return "I am a "+this-> getOperator()+" using a "+schemeType; }

};

class lapOrthogonalC : public laplacianBase
{
    public:
        std::string schemeType;
    
        // Constructor
        lapOrthogonalC(){ schemeType="Gauss Linear Orthogonal _C_ Scheme"; }
        // Destructor
        ~lapOrthogonalC(){ std::cout << "lapOrthogonal _C_ destructor called." << std::endl;}

        std::string getType() override { return "I am a "+this-> getOperator()+" using a "+schemeType; }

};

enum laplacianType { OrthoA, OrthoB, OrthoC };


// Responsible for creating all the fvSchemes
class laplacianFactoryRaw
{
    public:
    laplacianBase* create(laplacianType scheme)
    {
        // New Method 
        // Take a look into REG Obj
        switch (scheme)
        {
            case OrthoA:
                return new lapOrthogonalA();
            
            case OrthoB:
                return new lapOrthogonalB();
            
            case OrthoC:
                return new lapOrthogonalC();
            
            default:
                std::cout << " Could not find the provided scheme" << scheme << std::endl;
                return nullptr;
        }
    }
};

class laplacianFactorySmart
{
    public:
    std::shared_ptr<laplacianBase> create(laplacianType scheme)
    {
        switch (scheme)
        {
            case OrthoA:
                // return new laplacianSchemes();
                return std::make_shared<lapOrthogonalA>() ;
            
            case OrthoB:
                // return new divSchemes();
                return std::make_shared<lapOrthogonalB>() ;
            
            case OrthoC:
                // return new gradSchemes();
                return std::make_shared<lapOrthogonalC>() ;
            
            default:
                std::cout << " Could not find the provided scheme" << scheme << std::endl;
                return nullptr;
        }
    }
};

// #endif


    // Dictionary fvSchemesDict
    // (
    //     IOObject
    //     (
    //         "fvSchemes",
    //         time.system(),
    //         mesh,
    //         IOObject::MUST_READ,            
    //         IOObject::NO_WRITE
    //     )
    // );

