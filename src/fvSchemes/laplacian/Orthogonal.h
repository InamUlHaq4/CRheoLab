// #ifndef NEWTONIAN_H
// #define NEWTONIAN_H
#pragma once

#include "Laplacian.h" 
#include <vector>

class Orthogonal : public Laplacian
{
    private:
        // The interpolation used for calculating the diffusivity gamma at the face.  ( Linear | harmonic )
        const std::string interpolationScheme_;
        
        // The kind of non-orthogonal correction
        static std::string nonOrthogonalCorrectionScheme_;

    protected:
        
    public:

        // Constructor
        Orthogonal();

        // Destructor
        virtual ~Orthogonal(){};

        static std::string className();

        static std::shared_ptr<Laplacian> New();

        const std::string& interpolationScheme() override;
    
        const std::string& nonOrthogonalCorrectionScheme() override;

        void print() override;

        private:

            static bool signToRegistry;    

};

// #endif
