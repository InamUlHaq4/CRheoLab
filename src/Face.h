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
        virtual  ~Face(){};

        // Member Functions
        // Setters
        void setOwner(const Cell& owner);
        void setNeighbour(const Cell& neighbour);
        void setID(const int& ID);
        void setWeightingFactor(const double& g_c);
        void setNonOrthogonalityFace(const double& nonOrthoAngle);
        void setSkewness(const double& skewness);
        
        void setIntersectionPoint(const vector3& intersectionPoint);//Added
        void setnPointsInFace(const int& nPointsInFace);//Added
        void setArea(const double& area); //added
        void setCenterOfMass(const vector3& centerOfMass); //added
        void setAreaVector(const vector3& areaVector); //added

        // Getters
        const Cell* Owner() const;
        const Cell* Neighbour() const;
        const vector3& CenterOfMass() const;
        const vector3& AreaVector() const;
        const double& WeightingFactor() const;
        const double& NonOrthogonality() const;
        const double& Skewness() const;
        const vector3& IntersectionPoint() const;

        const int& ID_cell() const;//Added
        const int& nPointsInFace_cell() const;//Added
        const double& Area() const; //added

        // Computations
        void computeArea();

        /// @brief Computes the face area vector \f$\vec{S}_f\f$
        void computeAreaVector();

        void computeCenterOfMass();
        /// @brief Computation of cells face weighting factor, \f$g_{c}\f$.
        /// @brief \f[ g_{c} =  \frac{ \left | \vec{d}_{fF} \cdot \vec{S}_f \right | }{ \left | \vec{d}_{Cf} \cdot \vec{S}_f \right | + \left | \vec{d}_{fF} \cdot \vec{S}_f \right |} \f]

        void computeWeightingFactor();

        void computeNonOrthogonality();

        void computeIntersectionPoint();

        void computeSkewness();

        // Write to stream
        friend std::ostream& operator<<(std::ostream& , const Face& );

    private:
        int ID_;

        int nPointsInFace_;
        vector<Point*> facePoints_;

        const Cell* owner_;
        const Cell* neighbour_;

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
