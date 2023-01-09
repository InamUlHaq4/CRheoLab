#include "readVolField.h"

template <typename vectorType>
VolField<vectorType>::VolField(const IOObject& IO)
    : IODictionary(IO),
      boundaryField_(IO)
{
  // Check action
  if (read() == MUST_READ)
  {
      internalField_=readInternalField();
  }
  else if (read() == NO_READ)
  {
      internalField_.resize(this->mesh().nCells_);
  }
  else
  {
      std::cerr << "Unrecognized action for internalField!" << std::endl;
  }
}

template <typename vectorType>
VolField<vectorType>::VolField(const IOObject& IO, const typename vectorType::value_type& defaultValue)
  : IODictionary(IO),
    boundaryField_(IO, defaultValue)
{
      internalField_.resize(this->mesh().nCells_, defaultValue);
}

template <typename vectorType>
VolField<vectorType>::VolField(const VolField<vectorType>& vf)
  : IODictionary(vf),
  internalField_(vf.internalField_),
  boundaryField_(vf.boundaryField_)
{}



// Give access to the boundary entities
template <typename vectorType>
BoundaryField<vectorType>& VolField<vectorType>::boundaryField()
{
  return boundaryField_;
}

template <typename vectorType>
vectorType& VolField<vectorType>::internalFieldRef() 
{
  return internalField_;
}

template <typename vectorType>
const vectorType& VolField<vectorType>::internalField() const 
{
  return internalField_;
}

template <typename vectorType> //provisional
VolField<vectorType>& VolField<vectorType>::operator=(const VolField<vectorType>& vf) 
{
  if (this == &vf)
        return *this;

  internalField_ = vf.internalField_;
  boundaryField_ = vf.boundaryField_;
  
  return *this;
}

