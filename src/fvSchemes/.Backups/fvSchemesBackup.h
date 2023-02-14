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
class FvSchemes 
{
    public:
        virtual std::string getOperator() = 0;
        virtual std::string getType() = 0;
};

// The class exists from the others that is inherited from the abstract class
// So the Laplacian Gradient and etc are fvSchemes thus we create a FvFactory in the end
// whose the job is create instances of each of these fvschemes on demand as smart pointers
class laplacianSchemes : public FvSchemes
{
    public:
        std::string getOperator() override { return "I am a Laplacian Operator"; }
        std::string getType() override { return "I am a laplacian Operator using a Gauss Linear Orthogonal Scheme"; }

};
// class laplacianOrthogonal : public laplacianSchemes
// {
// };

class divSchemes : public FvSchemes
{
    public:
        std::string getOperator() override { return "I am a Divergent Operator"; }
        std::string getType() override { return "I am a divergent Operator using a Gauss Linear Scheme"; }
};

class gradSchemes : public FvSchemes
{
    public:
        std::string getOperator() override { return "I am a Gradient Operator"; }
        std::string getType() override { return "I am a Gradient Operator using a leastSquares Scheme"; }
};

enum FVType { LAPLACIAN, DIVERGENT, GRADIENT };


// Responsible for creating all the fvSchemes
class FvFactory
{
    public:
    FvSchemes* create(FVType scheme)
    {
        switch (scheme)
        {
            case LAPLACIAN:
                return new laplacianSchemes();
            
            case DIVERGENT:
                return new divSchemes();
            
            case GRADIENT:
                return new gradSchemes();
            
            default:
                std::cout << " Could not find the provided scheme" << scheme << std::endl;
                return nullptr;
        }
    }
};

class FvFactoryShared
{
    public:
    std::shared_ptr<FvSchemes> create(FVType scheme)
    {
        switch (scheme)
        {
            case LAPLACIAN:
                // return new laplacianSchemes();
                return std::make_shared<laplacianSchemes>() ;
            
            case DIVERGENT:
                // return new divSchemes();
                return std::make_shared<divSchemes>() ;
            
            case GRADIENT:
                // return new gradSchemes();
                return std::make_shared<gradSchemes>() ;
            
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

