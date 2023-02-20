#ifndef VOLFIELD_H
#define VOLFIELD_H

#include "RunTime.h"
#include "BoundaryField.h"
#include "DimensionedSet.h"
#include "Dictionary.h"

typedef std::array<double, 3>   vector3;
typedef std::array<double, 6>   symmTensor;
typedef std::array<double, 9>   tensor;

typedef std::vector<double>     scalarField;
typedef std::vector<vector3>    vectorField;
typedef std::vector<symmTensor> symmTensorField;
typedef std::vector<tensor>     tensorField;

template<typename vectorType> 
class  VolField; 

template <typename vectorType>              
std::ostream& operator<<(std::ostream& os, const  VolField<vectorType>& vf);

typedef std::unordered_map<std::string, std::string> stringMap;

template< typename vectorType>
class VolField
:
    public IOObject
{
    private:
        // Member Functions
        void readInternalField();
        void readDimensions();

    public:

        // Default constructor
        VolField(const IOObject& IO);

        // Constructor with a default value passed by argument
        VolField(const IOObject& IO, const typename vectorType::value_type& defaultValue);

        VolField(const VolField& vf); 

        // Destructor
        virtual ~VolField() = default ;

        // Give access to the boundary entities
        const BoundaryField<vectorType>& boundaryField() const;

        BoundaryField<vectorType>& boundaryFieldRef();

        vectorType& internalFieldRef(); 

        const vectorType& internalField() const;

        virtual void write() const;

        void initHeader() const;
        void updateHeader() const;

        const DimensionedSet& dimensions() {return dimensions_;}

        // Give access to the field/file path in the OS directory tree
        const std::string& fieldFilePath();

        // Give access to the field/file name
        const std::string& fieldFileName();

        VolField& operator=(const VolField &vf); // provisional

        template<class T>
        friend std::ostream& operator<<(std::ostream& os, const VolField<T>& vf);

    private:
        
        vectorType internalField_;
        BoundaryField<vectorType> boundaryField_;
        DimensionedSet dimensions_;
        mutable Dictionary header_;
};

#include "VolFieldOperations.h"
#include "VolFieldI.h"

#endif
