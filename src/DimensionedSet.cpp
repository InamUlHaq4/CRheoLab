#include "DimensionedSet.h"

std::istream& operator>> (std::istream& is, DimensionedSet& ds)
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

std::ostream& operator<< (std::ostream& os, const DimensionedSet& ds)
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

bool DimensionedSet::compareDimensions (const DimensionedSet& ds1, const DimensionedSet& ds2) const
{   
        // Iterate over both vectors in parallel
        for (int i = 0; i < ds1.size(); i++)
        {
            // Compare values at each position
            if (ds1[i] != ds2[i])
            {
                std::string message = "Dimensions are different\n"; 
                std::cout << ds1 << "  is not the same as  " << ds2 << std::endl;
                throw std::runtime_error(message);
            }
        }
        return true;
}

DimensionedSet DimensionedSet::operator+(const DimensionedSet& ds2) const
{
    compareDimensions (*this, ds2);
    return *this;
}

DimensionedSet DimensionedSet::operator-(const DimensionedSet& ds2) const
{
    compareDimensions (*this, ds2);
    return *this;
}

DimensionedSet DimensionedSet::operator*(const DimensionedSet& ds2) const
{
    DimensionedSet  dim;

    for (int i = 0; i < ds2.size(); i++)
    {
        dim.dimensions_[i] = this->dimensions_[i] + ds2.dimensions_[i];
    }
    return dim;
}

DimensionedSet DimensionedSet::operator/(const DimensionedSet& ds2) const
{
    DimensionedSet  dim;

    for (int i = 0; i < ds2.size(); i++)
    {
        dim.dimensions_[i] = this->dimensions_[i] - ds2.dimensions_[i];
    }
    return dim;
}

double DimensionedSet::operator[](unsigned int posI)
{
  if (posI >= dimensions_.size())
  {
      throw std::runtime_error("The given index is out of bounds");
  }

  return dimensions_[posI];
}

const double& DimensionedSet::operator[](unsigned int posI) const
{
  if (posI >= dimensions_.size())
  {
      throw std::runtime_error("The given index is out of bounds");
  }

  return dimensions_[posI];
}
