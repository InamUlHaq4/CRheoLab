#ifndef geometricField_H
#define geometricField_H

#include "RunTime.h"
#include "BoundaryField.h"
#include "DimensionedSet.h"
#include "Dictionary.h"
#include "geometricFieldFwd.h"

template<typename vectorType, typename geometricType>              
std::ostream& operator<<(std::ostream& os, const  geometricField<vectorType, geometricType>& vf);

typedef std::unordered_map<std::string, std::string> stringMap;


template<typename vectorType, typename geometricType>
class geometricField
:
    public IOObject,
    public geometricType
{
    private:
        // Member Functions
        void readInternalField();
        void readDimensions();

    public:

        // Default constructor
        explicit geometricField(const IOObject& IO);

        // Constructor with a default value passed by argument
        geometricField(const IOObject& IO, 
                       const DimensionedSet& dims,
                       const typename vectorType::value_type& defaultValue);

        geometricField(const geometricField& vf); 

        // Destructor
        virtual ~geometricField() = default ;

        // Give access to the boundary entities
        const BoundaryField<vectorType>& boundaryField() const;

        BoundaryField<vectorType>& boundaryFieldRef();

        vectorType& internalFieldRef(); 

        const vectorType& internalField() const;

        virtual void write() const;

        void initHeader() const;
        void updateHeader() const;

        const DimensionedSet& dimensions() const {return dimensions_;}
        DimensionedSet& dimensions() {return dimensions_;}

        geometricField& operator=(const geometricField &vf); // provisional

        template<class T, class U>
        friend std::ostream& operator<<(std::ostream& os, const geometricField<T, U>& vf);

        typename vectorType::value_type& operator[](int pos);
        const typename vectorType::value_type& operator[](int pos) const; 

    private:
        
        vectorType internalField_;
        BoundaryField<vectorType> boundaryField_;
        DimensionedSet dimensions_;
        mutable Dictionary header_;
};

#include "geometricFieldI.h"
#include "geometricFieldOperations.h"
#endif
