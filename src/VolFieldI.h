#include "readVolField.h"
#include <fstream>  

template <typename vectorType>
VolField<vectorType>::VolField
(
    const IOObject& IO
)
: 
IOObject(IO),
boundaryField_(IO),
header_(IO.path())
{
    // Check action
    if (readOp() == IOObject::MUST_READ)
    {
        header_.readDict("FoamFile");
        readDimensions();
        readInternalField();
    }
    else if (readOp() == IOObject::NO_READ)
    {
        internalField_.resize(this->mesh().nCells());
    }
    else
    {
        throw std::runtime_error("Unrecognized action for internalField!");
    }
}

template <typename vectorType>
VolField<vectorType>::VolField
(
    const IOObject& IO, 
    const typename vectorType::value_type& defaultValue
)
: 
IOObject(IO),
boundaryField_(IO, defaultValue)
{
    internalField_.resize(this->mesh().nCells(), defaultValue);
    initHeader();
}

template <typename vectorType>
VolField<vectorType>::VolField
(
  const VolField<vectorType>& vf
)
: 
IOObject(vf),
internalField_(vf.internalField_),
boundaryField_(vf.boundaryField_),
header_(vf.header_)
{}

template <typename vectorType>
const BoundaryField<vectorType>& VolField<vectorType>::boundaryField() const
{
    return boundaryField_;
}

// Give access to the boundary entities
template <typename vectorType>
BoundaryField<vectorType>& VolField<vectorType>::boundaryFieldRef()
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

template <typename vectorType>
void VolField<vectorType>::initHeader() const
{
    typename vectorType::value_type primitiveDataType;

    std::unique_ptr<Dictionary> tmpDict = std::make_unique<Dictionary>();

    Dictionary& dict = *tmpDict;

    dict.localData()["version"] = "2.0";
    dict.localData()["format"] = "ascii";
    dict.localData()["class"] = IOObject::volTypes[typeid(primitiveDataType)];
    dict.localData()["object"] = name();

    header_.data().emplace("FoamFile", std::move(tmpDict));
}

template <typename vectorType>
void VolField<vectorType>::updateHeader() const
{
    typename vectorType::value_type primitiveDataType;

    std::string folderName = mesh().time().Folder();

    header_.data()["FoamFile"].get()->localData()["version"] = "2.0";
    header_.data()["FoamFile"].get()->localData()["format"] = "ascii";
    header_.data()["FoamFile"].get()->localData()["class"] = IOObject::volTypes[typeid(primitiveDataType)];
    header_.data()["FoamFile"].get()->localData()["location"] = '"' + folderName.substr(0, folderName.length() - 1) + '"';
    header_.data()["FoamFile"].get()->localData()["object"] = name();
}

template <typename vectorType> //provisional
VolField<vectorType>& VolField<vectorType>::operator=(const VolField<vectorType>& vf) 
{
    if (this == &vf) // prevent self assignment
          return *this;

    internalField_ = vf.internalField_;
    boundaryField_ = vf.boundaryField_;
    
    return *this;
}

template <typename vectorType> 
std::ostream& operator<<(std::ostream& os, const VolField<vectorType>& vf)
{
    os << "dimensions" << "\t" << vf.dimensions_ << ";\n \n";

    os << "internalField " << "\t" ;

    if (vf.internalField_.size() == 1)
    {
      os << "uniform " 
          << vf.internalField_[0] << ";\n \n";
    }
    else
    {
      typename vectorType::value_type primitiveDataType;
      os << "nonuniform List<" << IOObject::dataTypes[typeid(primitiveDataType)] << ">" << "\n" 
          << vf.internalField_;
    }
    os << "\n"
        << vf.boundaryField_ 
        << std::endl;

    return os;
}

template <typename vectorType> 
void VolField<vectorType>::write() const
{
    this->mesh().time().createTimeFolder();

    std::ofstream outfile (this->mesh().time().timeName() + "/" + name());

    if (outfile.fail())
    {
        throw std::runtime_error("Failled to create file. check folder name");
    }

    outfile   << this->CRheoHeader << std::endl;

    updateHeader();

    outfile   << indentDict(header_) << std::endl;;

    outfile   << *this << std::endl;

    outfile.close();
}