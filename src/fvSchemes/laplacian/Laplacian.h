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
