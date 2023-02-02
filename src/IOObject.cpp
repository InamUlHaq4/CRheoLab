#include "IOObject.h"
#include "Mesh.h"

IOObject::IOObject 
( 
    const std::string& name,
    const std::string& fileLocation,
    const Mesh& mesh,
    readOperation read,
    writeOperation write,
    const bool& storeObj
)
:
name_(name),
fileLocation_(fileLocation),
mesh_(mesh),
read_(read),
write_(write),
storeObj_(storeObj)
{
    path_ = fileLocation_ + name_;
    // std::cout << "IOObject constructor for " << name_ << std::endl;
}

IOObject::IOObject 
( 
    const std::string& name,
    const std::string& fileLocation,
    const Mesh& mesh
)
:
name_(name),
fileLocation_(fileLocation),
mesh_(mesh)
{
    path_ = fileLocation_ + name_;
}


IOObject::IOObject 
( 
    const IOObject& obj,
    bool store
)
:
name_(obj.name_),
fileLocation_(obj.fileLocation_),
path_(fileLocation_ + name_),
mesh_(obj.mesh_),
read_(obj.read_), //here enters read function
write_(obj.write_),
storeObj_(obj.storeObj_)
{
    if (storeObj_)
    {
        checkIn(this);
    }
    // std::cout << "IOObject copy constructor for " << name_ << std::endl;
}

void IOObject::write() const
{
}

const std::string& IOObject::name() const
{
    return name_;
}

const std::string& IOObject::file() const
{
    return fileLocation_;
}


const std::string& IOObject::path() const
{
    return path_;
}

const Mesh& IOObject::mesh() const
{
    return mesh_;
}

void IOObject::store(bool check)
{
    storeObj_ = check;

    if(storeObj_)
    {
        checkIn(this);
    }
}

bool IOObject::isStore()
{
    return storeObj_;
}

void IOObject::checkIn(IOObject* obj)
{
    auto found = std::find_if(mesh().dataBase().begin(),mesh().dataBase().end(), 
                            [&](IOObject* item)
                            {
                                return item->name() == obj->name();
                            });  

    if (found == mesh().dataBase().end())
    {
        const_cast<Mesh&>(mesh_).dataBaseRef().emplace_back(this); //adicionar ao dataBase
    }
}

void IOObject::checkOut(const std::string& name)
{
    
    Mesh& myMesh = const_cast<Mesh&>(mesh_);

    myMesh.dataBaseRef().erase( 
                                std::remove_if( 
                                                    myMesh.dataBaseRef().begin(), myMesh.dataBaseRef().end(), 
                                                    [name](IOObject* item)
                                                    {
                                                        return item->name() == name;
                                                    }
                                                ), 
                                                myMesh.dataBaseRef().end()
                              );
                              
}  



std::map<std::type_index, std::string> IOObject::dataTypes =
{
    {typeid(double),        "scalar"},   
    {typeid(vector3),       "vector"},
    {typeid(tensor),        "tensor"},
    {typeid(symmTensor),    "symmTensor"},
};

std::map<std::type_index, std::string> IOObject::volTypes =
{
    {typeid(double),        "volScalarField"},   
    {typeid(vector3),       "volVectorField"},
    {typeid(tensor),        "volTensorField"},
    {typeid(symmTensor),    "volSymmTensorField"},
};


const char* IOObject::CRheoHeader = 
R"""(/*--------------------------------*- C++ -*----------------------------------*\
| =========                 |                                                 |
| \\        /  C            | Computational Rheology Group                    |
|  \\      /   R            | Institute for Polymers and Composites            |
|   \\    /    H            | Univeristy of Minho                             |
|    \\  /     E            | Web:         http://www.crheo.org               |
|     \\/      0            |                                                 |
\*---------------------------------------------------------------------------*/)""";