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
    friend std::istream& operator>> (std::istream& is, DimensionedSet& ds);

    friend std::ostream& operator<< (std::ostream& os, const DimensionedSet& ds);

    bool compareDimensions (const DimensionedSet& ds1, const DimensionedSet& ds2) const;

    //bool dimensionsRef (const DimensionedSet& ds1, const DimensionedSet& ds2);

    ///@brief Returns the size of the  patch
    int size() const {return dimensions_.size();}

    // DimensionedSet[i]
    const double& operator[](unsigned int index) const;
    double operator[](unsigned int index);

    DimensionedSet operator+( const DimensionedSet& ds2) const;

    DimensionedSet operator-( const DimensionedSet& ds2) const;

    DimensionedSet operator*( const DimensionedSet& ds2) const;

    DimensionedSet operator/( const DimensionedSet& ds2) const;

};

#endif
