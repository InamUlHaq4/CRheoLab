#ifndef VOLFIELDOPERATIONS_H
#define VOLFIELDOPERATIONS_H

typedef std::array<double, 3> vector3;
typedef std::array<double, 6> symmTensor;
typedef std::array<double, 9> tensor;

typedef std::vector<double> scalarField;
typedef std::vector<vector3> vectorField;
typedef std::vector<symmTensor> symmTensorField;
typedef std::vector<tensor> tensorField;

typedef VolField<scalarField> volScalarField;
typedef VolField<vectorField> volVectorField;
typedef VolField<tensorField> volTensorField;
typedef VolField<symmTensorField> volSymmTensorField;

#include "fieldOperations.h"


//volField operations

//sum
template <typename type>
inline std::vector<type> operator+(const type& s, const vector<type>& v)
{   
   std::vector<type> result(v.size());
   for (unsigned int j = 0; j < v.size(); j++)
   {
      result[j]= s + v[j];
   }
   return result;
}

template <typename type>
inline std::vector<type> operator+(const vector<type>& v, const type& s)
{   
   return s+v; 
}


template <typename vectorType>
inline VolField<vectorType> operator+(const VolField<vectorType>& v1, const VolField<vectorType>& v2)
{
   v1.dimensions().compareDimensions (v1.dimensions(), v2.dimensions());

   VolField<vectorType> result 
   (
         IOObject
        (
            v1.name() + "+" + v2.name(),
            v1.mesh().time().timeName(),
            v1.mesh(),
            IOObject::NO_READ,
            IOObject::NO_WRITE,
            false
        ),
        typename vectorType::value_type(0)
   );

   result.dimensionsRef() = v1.dimensions() + v2.dimensions();

   const vectorType& v1_internal = v1.internalField();
   const vectorType& v2_internal = v2.internalField();

   if (v1_internal.size() == 1 && v2_internal.size() == 1) 
   {
      result.internalFieldRef()[0] = v1.internalField()[0] + v2.internalField()[0];
   }

   else
   {
      result.internalFieldRef()= v1.internalField() + v2.internalField();
   }  

   return result;
}

// subtraction

template <typename type>
inline std::vector<type> operator-(const type& s, const vector<type>& v)
{   
   std::vector<type> result(v.size());
   for (unsigned int g = 0; g < v.size(); g++)
   {
      result[g]= s - v[g];
   }
   return result;
}

template <typename type>
inline std::vector<type> operator-(const vector<type>& v, const type& s)
{   
   std::vector<type> result(v.size());
   for (unsigned int g = 0; g < v.size(); g++)
   {
      result[g]= v[g]-s;
   }
   return result; 
}


template <typename vectorType>
inline VolField<vectorType> operator-(const VolField<vectorType>& v1, const VolField<vectorType>& v2)
{
   v1.dimensions().compareDimensions (v1.dimensions(), v2.dimensions());

   VolField<vectorType> result 
   (
         IOObject
        (
            v1.name() + "-" + v2.name(),
            v1.mesh().time().timeName(),
            v1.mesh(),
            IOObject::NO_READ,
            IOObject::NO_WRITE,
            false
        ),
        typename vectorType::value_type(0)
   );

   result.dimensionsRef() = v1.dimensions() - v2.dimensions();

   const vectorType& v1_internal = v1.internalField();
   const vectorType& v2_internal = v2.internalField();

   if (v1_internal.size() == 1 && v2_internal.size() == 1) 
   {
      result.internalFieldRef()[0] = v1.internalField()[0] - v2.internalField()[0];
   }

   else
   {
      result.internalFieldRef()= v1.internalField() - v2.internalField();
   }  

   return result;
}

// multiplication
template <typename type>
inline std::vector<type> operator*(const type& s, const vector<type>& v)
{   
   std::vector<type> result(v.size());
   for (unsigned int j = 0; j < v.size(); j++)
   {
      result[j]= s * v[j];
   }
   return result;
}

template <typename type>
inline std::vector<type> operator*(const vector<type>& v, const type& s)
{   
   return s*v; 
}


template <typename vectorType>
inline VolField<vectorType> operator*(const VolField<vectorType>& v1, const VolField<vectorType>& v2)
{
   VolField<vectorType> result 
   (
         IOObject
        (
            v1.name() + "*" + v2.name(),
            v1.mesh().time().timeName(),
            v1.mesh(),
            IOObject::NO_READ,
            IOObject::NO_WRITE,
            false
        ),
        typename vectorType::value_type(0)
   );

   result.dimensionsRef() = v1.dimensions() * v2.dimensions();

   const vectorType& v1_internal = v1.internalField();
   const vectorType& v2_internal = v2.internalField();

   if (v1_internal.size() == 1 && v2_internal.size() == 1) 
   {
      result.internalFieldRef()[0] = v1.internalField()[0] * v2.internalField()[0];
   }
   
   else
   {
      result.internalFieldRef()= v1.internalField() * v2.internalField();
   }  

   return result;
}

// division
template <typename type>
inline std::vector<type> operator/(const type& s, const vector<type>& v)
{   
   std::vector<type> result(v.size());
   for (unsigned int j = 0; j < v.size(); j++)
   {
      result[j]= s / v[j];
   }
   return result;
}

template <typename type>
inline std::vector<type> operator/(const vector<type>& v, const type& s)
{   
   std::vector<type> result(v.size());
   for (unsigned int j = 0; j < v.size(); j++)
   {
      result[j]= v[j] / s;
   }
   return result;
}


template <typename vectorType>
inline VolField<vectorType> operator/(const VolField<vectorType>& v1, const VolField<vectorType>& v2)
{
   VolField<vectorType> result 
   (
         IOObject
        (
            v1.name() + "/" + v2.name(),
            v1.mesh().time().timeName(),
            v1.mesh(),
            IOObject::NO_READ,
            IOObject::NO_WRITE,
            false
        ),
        typename vectorType::value_type(0)
   );

   result.dimensionsRef() = v1.dimensions() / v2.dimensions();

   const vectorType& v1_internal = v1.internalField();
   const vectorType& v2_internal = v2.internalField();

   if (v1_internal.size() == 1 && v2_internal.size() == 1) 
   {
      result.internalFieldRef()[0] = v1.internalField()[0] / v2.internalField()[0];
   }
    
   else
   {
      result.internalFieldRef()= v1.internalField() / v2.internalField();
   }  

   return result;
}

#endif
