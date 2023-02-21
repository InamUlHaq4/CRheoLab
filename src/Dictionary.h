#ifndef Dictionary_H
#define Dictionary_H

#include "IOObject.h"
#include "readHelpOperations.h"
#include <unordered_map>
#include <memory>
#include <iomanip>

class Dictionary;
struct indentDict;

typedef std::unordered_map<std::string, std::string> stringMap;
typedef std::unordered_map<std::string, std::unique_ptr<Dictionary>> dictMap;

std::ostream& operator<<(std::ostream& os, const stringMap&  m);
std::ostream& operator<<(std::ostream& os, const indentDict& d);

// struct used for indentation printing of dictionary class
struct indentDict
{
    const Dictionary& dict;
    int indentLevel;    

    indentDict(const Dictionary& dict, int indentLevel=0) 
    : 
    dict(dict), 
    indentLevel(indentLevel) 
    {}
};

struct baseDict
{
    int  nOpenParenthesis_{0};
    bool finishedReadingSubDicts_{false};
    std::string filePath_;
    virtual ~baseDict() = default;
};

class Dictionary
: public baseDict
{
    public:

        //- Constructors
            // empty
            Dictionary() = default;

            // From string
            Dictionary(const std::string& path);

            // From IOObject
            Dictionary(const IOObject& IO);
            
            // Copy constructor
            Dictionary(const Dictionary& otherDict);
            Dictionary& operator=(const Dictionary& otherDict)
            {
                *this = Dictionary(otherDict);
                return *this;
            }

            Dictionary(Dictionary&& otherDict) = default;
            Dictionary& operator=(Dictionary&& otherDict) = default;

            virtual ~Dictionary() = default;

        //- Member functions

            // read
            virtual bool read();
            void readSubDict (Dictionary& tmp, std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter, const std::string& key);
            bool readDict (const std::string& dictName);

            // Manipulate string
            virtual void parseString (std::string& line, std::istringstream& iss, std::ifstream& in_file, Dictionary& tmp2, int& lineCounter);
            void stripAndAppendToMap(std::string&, stringMap&);

        void bracketsTest(std::ifstream& in_file);

        //- Attribute access
        const stringMap& localData() const {return localData_;}
        stringMap& localData(){return localData_;}
        const dictMap& data() const {return data_;}
        dictMap& data(){return data_;}

        //- Lookup
        template <typename T>
        T lookup(const std::string& keyWord) const;

        //- LookupOrDefault
        template <typename T>
        T lookupOrDefault(const std::string& keyWord, T defaultV) const;

        const Dictionary& subDict(const std::string& dictName) const;

        //- Print

        friend std::ostream& operator<<(std::ostream& os, const Dictionary& dict);

    private:
        stringMap   localData_;
        dictMap     data_; 
};

#include "DictionaryI.h"

#endif 

