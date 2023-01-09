
#ifndef PRINTUTILS_H
#define PRINTUTILS_H

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <iomanip>


typedef std::unordered_map<std::string, std::string> stringMap;

std::ostream& operator<<(std::ostream& os, const stringMap& m)
{

    size_t size = 0;

    // Get largest key
    for (const auto& elem : m)
    {
        if (size < elem.first.size())
        {
            size = elem.first.size();
        }
    }

    for(const auto& elem : m)
    {
        os  << elem.first 
            << std::setw(size)
            << "\t"
            << elem.second
            << ';'
            << "\n";
    }
    

    return os;
}


// Print maps of strings
std::ostream& operator<<(std::ostream& os, const std::map<std::string,std::string> & m)
{
    size_t size = 0;

    // Get largest key
    for (const auto& elem : m)
    {
        if (size < elem.first.size())
        {
            size = elem.first.size();
        }
    }

    for(const auto& elem : m)
    {
        os  << elem.first 
            << std::setw(size)
            << "\t"
            << elem.second
            << ';'
            << "\n";
    }
    
    return os;
}


#endif