#ifndef DimensionedSet_H
#define DimensionedSet_H

#include <array>
#include <iostream>
#include <string>

class DimensionedSet
{
    private:
    std::array<double, 7> dimensions_{0};

    public:
    friend std::istream& operator>> (std::istream& is, DimensionedSet& ds)
    {   
        char braket1, braket2;

        is >> braket1;
        
        if(is.fail())
            is.setstate(std::ios::failbit);

        for (int i=0; i < 7; i++)
        {
            is >> ds.dimensions_[i];
        }

        is >> braket2;

        if(is.fail())
            is.setstate(std::ios::failbit);

        return is;
    }

    friend std::ostream& operator<< (std::ostream& os, const DimensionedSet& ds)
    {
        os << '[' ;
        os << ds.dimensions_[0];
        for (int i=1; i<7; i++)
        {
            os << " " <<  ds.dimensions_[i];
        }
        os << ']';

        return os;
    }

};

#endif