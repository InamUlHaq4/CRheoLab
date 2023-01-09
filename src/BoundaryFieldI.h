// BoundaryField constructor by reading Input file  
template <typename vectorType>
BoundaryField<vectorType>::BoundaryField(const IOObject& IO)
:     nPatches_(IO.mesh().nPatches_)
{
    for (int i = 0; i < nPatches_; i++)
    {
        boundaryData_.push_back(Boundary<vectorType>(IO, IO.mesh().patchList_[i]));
    } 
}

// BoundaryField constructor by setting a default value for the field  
template <typename vectorType>
BoundaryField<vectorType>::BoundaryField(const IOObject& IO, const typename vectorType::value_type& defaultValue)
:     nPatches_(IO.mesh().nPatches_)
{
    for (int i = 0; i < nPatches_; i++)
    {
        boundaryData_.push_back(Boundary<vectorType>(IO, IO.mesh().patchList_[i], defaultValue));
    }
}

// Member function to access the boundary data
template <typename vectorType>
vector<Boundary<vectorType>>& BoundaryField<vectorType>::boundaryData()
{
    return boundaryData_;
}

// Returns the size of the boundary patch
template <typename vectorType>
const int& BoundaryField<vectorType>::size() const
{
    return boundaryData_.size();
}

// Returns the name in the boundaryField patch list for the give patch index 
template <typename vectorType>
const int& BoundaryField<vectorType>::patchID(const std::string& patchName) const
{
    int pId=-1;
    for (unsigned int i = 0; i < nPatches_; i++)
    {
        if (boundaryData_[i].name()==patchName)
        {
            pId=boundaryData_[i].index();
        } 
    }
    return pId;
}

// Returns the index in the boundaryField patch list for the give patch name 
template <typename vectorType>
const std::string& BoundaryField<vectorType>::patchName(const int& ID) const
{
    return boundaryData_[ID].name();
}

template <typename vectorType> //provisional
BoundaryField<vectorType>& BoundaryField<vectorType>::operator=(const BoundaryField<vectorType>& bf)
{
  if (this == &bf)
        return *this;

  boundaryData_ = bf.boundaryData_;
  
  return *this;
}
