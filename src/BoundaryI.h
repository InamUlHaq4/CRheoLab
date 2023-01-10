#include "readBoundary.h"

// Constructor by Reading Input file to initialize data members 
template <typename vectorType>
Boundary<vectorType>::Boundary
(
  const IOObject& IO, 
  const Patch& patch
)
  : IOObject(IO),
    boundaryPatch_(patch)
{
    if (readOp() == IOObject::MUST_READ)
    {
      readBoundaryPatch(boundaryPatch_.name());
    }
    else if (readOp() == IOObject::NO_READ)
    {
        type_ = "calculated";
        uniformField_ = false;
        definedValues_.resize(patch.nFaces());

        typename vectorType::value_type dataToVector{0};
        std::fill(this->definedValues_.begin(),this->definedValues_.end(), dataToVector);
    }
    else
    {
        throw std::runtime_error("Unrecognized action for boundaryField! Please choose MUST_READ or NO_READ!");
    }

    // Verifying if the patch size is in agreement with the mesh Patch size
    if 
    (
           (!this->uniformField_) 
        && (this->type_!="empty") 
        && (this->definedValues_.size() != (long unsigned int)patch.nFaces())
    )
    {
        std::cerr << "The input data for the patch named as \" "
        << patch.name() << " \" for the field " << this->name() 
        << " in the file " << this->mesh().time().Path() << this->name() 
        << " has " << this->definedValues_.size() 
        << " entries, while this patch allows only " << patch.nFaces()  << " face!" << std::endl;
        throw std::runtime_error(" ");
    }
}

// Constructing with a default value passed by argument
template <typename vectorType>
Boundary<vectorType>::Boundary
(
  const IOObject& IO, 
  const Patch& patch, 
  const typename vectorType::value_type& defaultValue
)
  : IOObject(IO),
    boundaryPatch_(patch)
{
    type_ = "calculated";
    uniformField_ = false;
    definedValues_.resize(patch.nFaces(), defaultValue);
}


template <typename vectorType>
Boundary<vectorType>::Boundary
(
  const Boundary<vectorType>& bf
)
  : IOObject(bf),
    boundaryPatch_(bf.boundaryPatch_),
    type_(bf.type_),
    uniformField_ (bf.uniformField_),
    definedValues_ (bf.definedValues_),
    otherInfo_(bf.otherInfo_)
{}


// Member function to access the boundary patch defined values
template <typename vectorType>
vectorType& Boundary<vectorType>::definedValues()
{
  return definedValues_;
}

// Member function to access the boundary patch defined name
template <typename vectorType>
const std::string& Boundary<vectorType>::name() const
{
  return boundaryPatch_.name();
}

// Member function to access the boundary patch defined type ( fixedValue, fixedGradient, symmetry, and etc. )
template <typename vectorType>
const std::string& Boundary<vectorType>::type() const
{
  return type_;
}

// Member function to access the boundary patch field type ( uniform and non-uniform )
template <typename vectorType>
bool& Boundary<vectorType>::uniformField()
{
  return uniformField_;
}


// Member function to access the boundary patch supplementary data content.
template <typename vectorType>
const Dictionary& Boundary<vectorType>::otherInfo()
{
  return otherInfo_;
}

// Operator Overloading templated
// Setter 
template <typename vectorType>
typename vectorType::value_type& Boundary<vectorType>::operator[](unsigned int posI)
{
  if (posI >= this->definedValues_.size())
  {
      throw std::runtime_error("The given index is out of bounds");
  }

  return definedValues().at(posI);
}

// Operator Overloading templated
// Getter 
template <typename vectorType>
typename vectorType::value_type Boundary<vectorType>::operator[](unsigned int posI) const
{
  if (posI >= definedValues().size())
  {
      throw std::runtime_error("The given index is out of bounds");
  }

  return this->definedValues_.at(posI);
}


template <typename vectorType>
Boundary<vectorType>& Boundary<vectorType>::operator=(const Boundary<vectorType>& bf)
{
  if (this == &bf)
        return *this;

  // Needs to be fixed
  
  return *this;
}

template <typename vectorType>
std::ostream& operator<<(std::ostream& os, const Boundary<vectorType>& b)
{
  os << "\t" 
     << b.name() << "\n"
     << "\t" 
     << '{'     << "\n"
     << "\t\t"    << "type" << "\t" <<"\t" << b.type_ << ';' << "\n";

  os << indentDict(b.otherInfo_, 2);

  if (b.uniformField_ && b.definedValues_.size() != 0)
  {
    os << "\t\t" << "value" << "\t" <<"\t" 
       << "uniform "
       << b.definedValues_[0] 
       << ';' << "\n";
  }
  else if (!b.uniformField_ && b.definedValues_.size() != 0)
  {
    typename vectorType::value_type primitiveDataType;
    if (IOObject::dataTypes.find(typeid(primitiveDataType)) != IOObject::dataTypes.end()) 
    {
        os << "\t\t"
           <<"value" << "\t"<<"\t" 
           << "nonuniform List<" << IOObject::dataTypes[typeid(primitiveDataType)] << ">" << "\n" 
           << b.definedValues_;
    } 
    else 
    {
        throw std::runtime_error("Error in dataType for printing...");
    }
  }

  os  << "\t"
      << '}'   
      << std::endl;

  return os;
}

template <typename vectorType> 
void Boundary<vectorType>::write() const
{
    throw std::runtime_error("write() not implemented for IOObject");
}




