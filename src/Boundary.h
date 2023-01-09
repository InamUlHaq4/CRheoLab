#ifndef Boundary_H
#define Boundary_H

#include "Mesh.h"
#include "RunTime.h"
#include <iostream>

///@brief Boundary Class stores the field data for a patch (faces on domain boundary).
/// provides attributes to store patch information.

template<typename vectorType> class Boundary; 

template <typename vectorType>              
std::ostream& operator<<( std::ostream&, const Boundary<vectorType>&);

template<typename vectorType>
class Boundary
:
    public IOObject
{
    public:
    
        // Constructor by Reading Input file to initialize data members 
        ///@brief Boundary constructor by reading Input file  
        ///@param fileName name of the file to read field data from
        ///@param patch reference to the Patch
        ///@param time reference to the RunTime object
        ///@param action Enum fileAction ( MUST_READ or NO_READ)
        Boundary(const IOObject& IO, const Patch& patch);
        
        // Constructing with a default value passed by argument
        ///@brief Boundary constructor by setting a default value for the field 
        ///@param fileName name of the file to read field data from
        ///@param patch reference to the Patch
        ///@param time reference to the RunTime object
        ///@param action Enum fileAction ( MUST_READ or NO_READ)
        ///@param defaultValue is a scalar, vector or a tensor with which the field must be initialized. \note Vectors and tensors must be initialized in braces like: {value1,value2, ...,etc. }.
        Boundary(const IOObject& IO, const Patch& patch, const typename vectorType::value_type& defaultValue);

        Boundary(const Boundary& bf); //provisional

        // Destructor
        virtual ~Boundary() = default ;

        // Read Boundary field
        ///@brief this function reads from a specified patch and returns the information to construct the object.
        ///@param patchName the name of patch for reading information. 
        void readBoundaryPatch(const std::string& patchName);

        ///@brief Member function to access the boundary patch defined values
        vectorType& definedValues();

        ///@brief Member function to access the boundary patch defined name
        const std::string& name() const;

        ///@brief Member function to access the boundary patch defined type ( fixedValue, fixedGradient, symmetry, and etc. )
        const std::string& type() const;
    
        ///@brief Member function to access the boundary patch field type ( uniform and non-uniform )
        bool& uniformField();

        ///@brief Member function to access the boundary patch supplementary data content.
        const std::map<std::string, std::string>& otherInfo();

        // Operator Overloading templated
        // Setter
        ///@brief Operator [] to modify the content set for a given position 
        ///@param posI position of a face given by a positive integer. 
        typename vectorType::value_type& operator[](unsigned int posI);

        // Getter
        ///@brief Operator [] to retrieve the content set for a given position 
        ///@param posI position of a face given by a positive integer. 
        typename vectorType::value_type operator[](unsigned int posI) const;

        virtual void write() const;

        Boundary& operator=(const Boundary &bf); //provisional

        template<class T>
        friend std::ostream& operator<<(std::ostream& os, const Boundary<T>& b);
                
    private:

      // Private Data Members
      
        const Patch& boundaryPatch_;

        // The type name of the Boundary condition.
        std::string type_; 

        // The field if it is uniform or not.
        bool uniformField_;

        // The values for the faces in the patch.
        vectorType definedValues_;

        // The supplementary data content.
        std::map<std::string, std::string> otherInfo_;
};

#include "BoundaryI.h"

#endif 
