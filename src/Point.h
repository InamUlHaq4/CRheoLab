#ifndef POINT_H
#define POINT_H

#include <iostream>
#include "mathOperations.h"


class Point
{
    public:
    
        // Constructor
        Point(double, double, double);
        Point();
    

        // Destructor
        virtual ~Point() = default;

        // Member Functions
        void setCoord(double, double, double);

        // Overloaded operatores
        // Setter
        double& operator[](unsigned int entry);

        // Getter
        double operator[](unsigned int entry) const ;

        // Summation
        Point operator+(Point const &obj) const;

        // Subtraction
        Point operator-(Point const &obj) const;

        // Return point vector
        const vector3& point() const;

        // Write to stream
        friend std::ostream& operator<<(std::ostream& , const Point& );
       
    private:
        vector3 point_;

};

#endif // POINT_H
