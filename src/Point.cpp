#include "Point.h"

Point::Point(double x, double y, double z)
:  
    point_{x,y,z}
{}

Point::Point()
:   
    point_{-1, -1 ,-1}
{}

void Point::setCoord(double x, double y, double z)
{
    point_[0] = x;
    point_[1] = y;
    point_[2] = z;
}

// Setter
double& Point::operator[](int entry)
{
    if (entry==0)
        return point_[0];
    else if(entry==1)
        return point_[1];
    else if(entry==2)
        return point_[2];
    else
        throw std::out_of_range("Point does not have index " + std::to_string(entry));
}

// Getter
double Point::operator[](int entry) const 
{
    if (entry==0)
        return point_[0];
    else if(entry==1)
        return point_[1];
    else if(entry==2)
        return point_[2];
    else
        throw std::out_of_range("Point does not have index " + std::to_string(entry));
}

Point Point::operator+(Point const &obj) const
{
    Point result;
    result.point_[0] = point_[0] + obj.point_[0];
    result.point_[1] = point_[1] + obj.point_[1];
    result.point_[2] = point_[2] + obj.point_[2];

    return result;
}

Point Point::operator-(Point const &obj) const
{
    Point result;
    result.point_[0] = point_[0] - obj.point_[0];
    result.point_[1] = point_[1] - obj.point_[1];
    result.point_[2] = point_[2] - obj.point_[2];

    return result;
}

const vector3& Point::point() const
{
    return point_;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "[ " << p[0] << ", " << p[1] << ", " << p[2] << " ]" << std::endl;
    return os;
}
