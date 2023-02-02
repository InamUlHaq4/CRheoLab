#ifndef FACE_H
#define FACE_H

#include "Point.h"
#include <vector>
using std::vector;

#include "Cell.h"

class Face
{
    public:

        // Constructor
        Face(int, vector<Point*>);
        Face();

        // Destructor
        virtual  ~Face()=default;

        // Member Functions
        // Setters
        void setOwner(const Cell& owner);
        void setNeighbour(const Cell& neighbour);
        void setID(const int& ID);


        // Getters
        const Cell* owner() const;
        const Cell* neighbour() const;
        const vector3& centerOfMass() const;
        const vector3& areaVector() const;
        const double& nonOrthogonality() const;
        const double& skewness() const;

        // Computations
        void computeArea();

        /// @brief Computes the face area vector \f$\vec{S}_f\f$
        void computeareaVector();

        void computecenterOfMass();
        /// @brief Computation of cells face weighting factor, \f$g_{c}\f$.
        /// @brief \f[ g_{c} =  \frac{ \left | \vec{d}_{fF} \cdot \vec{S}_f \right | }{ \left | \vec{d}_{Cf} \cdot \vec{S}_f \right | + \left | \vec{d}_{fF} \cdot \vec{S}_f \right |} \f]

        void computeWeightingFactor();

        void computeNonOrthogonality();

        void computeIntersectionPoint();

        void computeSkewness();

        void correctSf();

        // Write to stream
        friend std::ostream& operator<<(std::ostream& , const Face& );

    private:
        int ID_;
        int nPointsInFace_;
        vector<Point*> facePoints_;        
        //Attributes obtained from other classes, require setters
        const Cell* owner_;
        const Cell* neighbour_;

        //Attributes calculated on face.cpp, don't require setters
        // Area
        double area_;
        // Center of mass
        vector3 centerOfMass_;
        /// Area vector, \f$\vec{S}_f\f$
        vector3 areaVector_;
        // Weighting factor
        double weightingFactor_;
        // Non-orthogonality angle
        double nonOrthogonalityAngle_;
        // Face Skewness
        double skewness_;

        // Intersection point (IP)
        vector3 intersectionPoint_;
};

#endif // FACE_H
