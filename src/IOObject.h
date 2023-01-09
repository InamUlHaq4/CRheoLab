#ifndef IOObject_H
#define IOObject_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream> 
#include <algorithm>
#include <typeindex>
#include <typeinfo>

class Mesh;

class IOObject
{
    public:

        enum readOperation
        {
            MUST_READ   = 0,
            NO_READ     = 1
        };

        enum writeOperation
        {
            MUST_WRITE  = 0,
            NO_WRITE    = 1
        };

        IOObject
        (
            const std::string& name,
            const std::string& fileLocation,
            const Mesh& mesh,
            readOperation read ,
            writeOperation write ,
            const bool& storeObj = true
        );
        
        IOObject
        (
            const std::string& name,
            const std::string& fileLocation,
            const Mesh& mesh
        );

        // Copy constructor
        IOObject (const IOObject& obj, bool store = false);

        virtual ~IOObject()
        {
            // std::cout << "IOobject " << name() << " is being destroyed" << std::endl;
        }

        virtual const std::string& name() const;
        const std::string& file() const;
        const std::string& path() const;
        const Mesh& mesh() const;
        bool isStore();

        const readOperation& readOp() const {return read_;} 
        const writeOperation& writeOp() const {return write_;} 

        void store(bool check);
        void checkIn(IOObject* obj);
        void checkOut(const std::string& name);

        virtual void write() const;
        
        static std::map<std::type_index, std::string> dataTypes;
        static std::map<std::type_index, std::string> volTypes;
        static const char* CRheoHeader;

        void rename(const std::string& newName){name_ = newName;}

        private:
            std::string name_;
            std::string fileLocation_;
            std::string path_;
            const Mesh& mesh_;
            readOperation read_;
            writeOperation write_;
            bool storeObj_;
};
#endif 
