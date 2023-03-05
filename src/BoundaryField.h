#ifndef boundaryField_H
#define boundaryField_H

#include "IODictionary.h"
#include "Mesh.h"
#include "RunTime.h"
#include "Boundary.h"

///@brief boundaryField Class stores the field data and other information for all the patches.

template< typename vectorType>
class BoundaryField
{
    public:

        ///@brief BoundaryField constructor by reading Input file  
        ///@param fileName name of the file to read field data from
        ///@param mesh reference to the Mesh
        ///@param time reference to a RunTime object 
        ///@param action Enum fileAction ( MUST_READ or NO_READ)
        BoundaryField(const IOObject&);

        ///@brief BoundaryField constructor by setting a default value for the field for all the boundary patches  
        ///@param fileName name of the file to read field data from
        ///@param mesh reference to the Mesh
        ///@param time reference to a RunTime object 
        ///@param action Enum fileAction ( MUST_READ or NO_READ)
        ///@param defaultValue is a scalar, vector or a tensor with which the field must be initialized. \note Vectors and tensors must be initialized in braces like: {value1,value2, ...,etc. }.
        BoundaryField(const IOObject&, const typename vectorType::value_type& defaultValue);
            
        // Destructor
        virtual ~BoundaryField() = default ;

        ///@brief Returns the size of the boundary patch
        int size() const;
        
        ///@brief Member function to access the boundary data
        vector<Boundary<vectorType>>& boundaryData();

        ///@brief Returns the index in the boundaryField patch list for the give patch name 
        const int& patchID(const std::string& patchName) const;

        ///@brief Returns the name in the boundaryField patch list for the give patch index 
        const std::string& patchName(const int& ID) const;

         ///@brief Returns for a patch I, the face J defined value
        typename vectorType::value_type patchIFaceJValue(int patchI, int faceJ) const;

        BoundaryField& operator=(const BoundaryField &bf); //provisional
        const Boundary<vectorType>& operator[](int index) const;

        template<class T>
        friend std::ostream& operator<<(std::ostream& os, const BoundaryField<T>& bf);

        //Getters
        const int& nPatches() const;

        ///@brief Returns the Type of Boundary Condition
        const std::string& patchTypeOfBCondition(int i) const;
  
    private:

        // Private Data Members
        vector<Boundary<vectorType>> boundaryData_;
        const int nPatches_;
        
};

#include "BoundaryFieldI.h"

#endif
