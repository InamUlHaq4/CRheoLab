#ifndef MATHOPERATIONS_H
#define MATHOPERATIONS_H

#include<vector>
#include <array>
#include <cmath> 
#include <map>

typedef double                  scalar;
typedef std::array<double, 3>   vector3;
typedef std::array<double, 6>   symmTensor;
typedef std::array<double, 9>   tensor;

typedef std::vector<double>     scalarField;
typedef std::vector<vector3>    vectorField;
typedef std::vector<symmTensor> symmTensorField;
typedef std::vector<tensor>     tensorField;

#include "fieldOperations.h"
#include "scalarOperations.h"
#include "vectorOperations.h"
#include "tensorOperations.h"

template <std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<double, N>& p)
{
    os << "(" ;
    
    os << p[0];

    for (unsigned int i = 1; i < p.size(); ++i) 
    {
        os << " " << p[i] ;
    }

    os << ")";
    
    return os;
}

// template <class T, T ch, bool SkipWhitespace = false>
// struct basicStream 
// {
//     friend std::istream& operator>>(std::istream& is, checkStream) 
//     {
//         if (skipWhiteSpace) 
//         { 
//             while (std::isspace(static_cast<unsigned char>(is.peek()))) 
//             {
//                 is.ignore();
//             }
//         }
//         if (is.peek() == ch)
//             is.ignore();
//         else
//             is.setstate(std::ios::failbit);
//         return is;
//     }
// };

// template<char Ch, bool SkipWhiteSpace = false>
// using checkStream = basicStream<char, ch, SkipWhiteSpace>;

template <char ch, bool skipWhiteSpace = false>
struct checkStream 
{
    friend std::istream& operator>>(std::istream& is, checkStream) 
    {
        if (skipWhiteSpace) 
        { 
            while (std::isspace(static_cast<unsigned char>(is.peek()))) 
            {
                is.ignore();
            }
        }
        if (is.peek() == ch)
            is.ignore();
        else
            is.setstate(std::ios::failbit);
        return is;
    }
};

template <std::size_t N>
std::istream& operator>>(std::istream& is, std::array<double, N>& p)
{
    constexpr checkStream<'(', true> p1;
    constexpr checkStream<')', true> p2;

    is >> p1;

    for (unsigned int i = 0; i < p.size(); ++i) 
    {
        is >> p[i] ;
    }

    is >> p2;
    
    return is;
}


template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << v.size() << "\n"
       << "("      << "\n";
    
    for (unsigned int i = 0; i < v.size(); ++i) 
    {
        os << v[i] << "\n";
    }

    os << ")" << "\n"
       << ';' << std::endl;
    
    return os;
}

#endif


