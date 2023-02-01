#include "Face.h"

Face::Face(int nPointsInFace, vector<Point*> facePoints)
:
    ID_(-1),
    nPointsInFace_(nPointsInFace),
    facePoints_(facePoints),
    owner_(nullptr),
    neighbour_(nullptr),
    area_(-1),
    centerOfMass_({-1,-1,-1}),
    areaVector_({-1,-1,-1}),
    weightingFactor_(-1),
    nonOrthogonalityAngle_(-1),
    skewness_(-1)
{}

Face::Face()
{}

// Setters
void Face::setOwner (const Cell& owner)
{
    owner_ = &owner;
}

void Face::setNeighbour(const Cell& neighbour)
{
    neighbour_ = &neighbour;
}

void Face::setID(const int& ID)
{
    ID_ = ID;
}


// Getters

const Cell* Face::owner() const
{
    return owner_;
}

const Cell* Face::neighbour() const
{
    return neighbour_;
}

const vector3& Face::centerOfMass() const
{
    return centerOfMass_;
}

const vector3& Face::areaVector() const
{
    return areaVector_;
}

const double& Face::nonOrthogonality() const
{
    return nonOrthogonalityAngle_;
}

const double& Face::skewness() const
{
    return skewness_;
}


//Removed non-Required Getters:
/*
const double& Face::WeightingFactor() const
{
    return weightingFactor_;
}

const vector3& Face::IntersectionPoint() const //Added
{
    return intersectionPoint_;
}

const int& Face::ID_cell() const //Added
{
    return ID_;
}

const int& Face::nPointsInFace_cell() const //Added
{
    return nPointsInFace_;
}

const double& Face::Area() const //added
{
    return area_;
}
*/

// Computations
void Face::computeArea()
{
    double a(0);
    double b(0);
    double c(0);
    double s(0);

    // face is a triangle
    if(nPointsInFace_ == 3)
    {
        // Edge length
        a = mag(facePoints_[0]->point() - facePoints_[1]->point());
        b = mag(facePoints_[1]->point() - facePoints_[2]->point());
        c = mag(facePoints_[2]->point() - facePoints_[0]->point());

        // Semi-perimeter
        s = (a + b + c) / 2.0;

        // Face area
        area_ = sqrt(s * (s - a) * (s - b) * (s - c));
    }
    else
    {
        // compute face centroid
        vector3 centroid {0,0,0};

        for(int i = 0; i < nPointsInFace_; i++)
        {
            centroid = centroid + facePoints_[i]->point();
        }

        centroid = centroid / nPointsInFace_;

        // face area
        area_ = 0.0;

        // compute area of each subtriangle
        for(int i = 0; i < nPointsInFace_; i++)
        {
                // all points but the last
                if(i < nPointsInFace_ - 1)
                {
                    // edges length
                    a = mag(facePoints_[i]->point() - facePoints_[i+1]->point());
                    b = mag(facePoints_[i]->point() - centroid);
                    c = mag(facePoints_[i+1]->point() - centroid);
                }
                else
                {
                    // edges length
                    a = mag(facePoints_[i]->point() - facePoints_[0]->point());
                    b = mag(facePoints_[i]->point() - centroid);
                    c = mag(facePoints_[0]->point() - centroid);
                }

                // semi-perimeter
                s = (a + b + c) / 2.0;

                // face area
                area_ = area_ + sqrt(s * (s - a) * (s - b) * (s - c));
        }
    }
}

void Face::computecenterOfMass()
{
    // face is a triangle
    if(nPointsInFace_ == 3)
    {
        // face center of mass
        centerOfMass_ = facePoints_[0]->point() + facePoints_[1]->point() +facePoints_[2]->point();
        centerOfMass_ = centerOfMass_ / 3.0;
    }
    else
    {
        // compute face centroid
        vector3 centroid {0,0,0};

        for(int i = 0; i < nPointsInFace_; i++)
        {
            centroid = centroid + facePoints_[i]->point();
        }
        centroid = centroid / nPointsInFace_;

        // numerator
        vector3 numerator({0,0,0});

        // denominator
        double denominator(0.0);

        double a(0);
        double b(0);
        double c(0);
        vector3 subcentroid ({0,0,0});

        // compute area and centroid of each subtriangle
        for(int i = 0; i < nPointsInFace_; i++)
        {
                // all points but the last
                if(i < nPointsInFace_ - 1)
                {
                    // edges length
                    a = mag(facePoints_[i]->point() - facePoints_[i+1]->point());
                    b = mag(facePoints_[i]->point() - centroid);
                    c = mag(facePoints_[i+1]->point() - centroid);

                    // subtriangle centroid
                    subcentroid = facePoints_[i]->point() + facePoints_[i+1]->point() + centroid;
                    subcentroid = subcentroid / 3.0;
                }
                else
                {
                    // edges length
                    a = mag(facePoints_[i]->point() - facePoints_[0]->point());
                    b = mag(facePoints_[i]->point() - centroid);
                    c = mag(facePoints_[0]->point() - centroid);

                    // subtriangle centroid
                    subcentroid = facePoints_[i]->point() + facePoints_[0]->point() + centroid;
                    subcentroid = subcentroid / 3.0;
                }

                // semi-perimeter
                double s = (a + b + c) / 2.0;

                // subtriangle area
                double subarea = sqrt(s * (s - a) * (s - b) * (s - c));

                // compute numerator
                numerator = numerator + subcentroid*subarea;

                // compute denominator
                denominator = denominator + subarea;
        }
        // face center of mass
        centerOfMass_ = numerator / denominator;
    }
}

void Face::computeareaVector()
{
    //Creates two vectors from the center of mass and one of the points in the face
    vector3 tmp_vec1 = facePoints_[0]->point() - centerOfMass_;
    vector3 tmp_vec2 = facePoints_[1]->point() - centerOfMass_;

    // Computes the face normal by doing the cross product of the products (this is not the faceAreaVector)
    vector3 areaVector_tmp = (tmp_vec1^tmp_vec2);

    // Computes the norm of the cross product between two vectors
    double mag_vector_tmp = mag(areaVector_tmp);

    // Calculates the faceAreaVector
    areaVector_ = (areaVector_tmp/mag_vector_tmp)*area_;
}

void Face::computeWeightingFactor()
{
    bool isInteriorFace (neighbour());

    if (isInteriorFace)
    {
        // linear interpoaltion factor defined as:
        // g_c \phi_P + (1-g_c) \phi_N
        const vector3& faceCenter = centerOfMass();
        const vector3& C_o = owner_->centerOfMass();
        const vector3& C_n = neighbour_->centerOfMass();

        const vector3 d_Cf = faceCenter - C_o ;
        const vector3 d_fF = C_n - faceCenter;
        //const vector3 e_f = getareaVector()/mag( getareaVector() );

        const vector3& Sf = areaVector();

        double SfdOwn = std::abs(Sf & d_Cf);
        double SfdNei = std::abs(Sf & d_fF);

        //setweightingFactor( std::abs(d_fF & e_f) / ( std::abs(d_Cf & e_f) + std::abs(d_fF & e_f) ));

        //setWeightingFactor( SfdNei / ( SfdOwn + SfdNei ) );
        weightingFactor_ = SfdNei / ( SfdOwn + SfdNei );
    }
    else
    {
        //setWeightingFactor(1.0);
        weightingFactor_ = 1.0;
    }
}



void Face::computeNonOrthogonality()
{
    bool isInteriorFace (neighbour());

    const vector3& C_o = owner_->centerOfMass(); //Cell owner

    const vector3& Sf = areaVector(); // Face Area vector

    const vector3 nf = Sf/mag(Sf); // Face normal vector

    double theta = -1;

    if (isInteriorFace)
    {
        const vector3& C_n = neighbour_->centerOfMass(); // from neighbor

        const vector3 d = C_n - C_o;

        // theta = acos(d.nf/[|d|.|n|])
        double thetaRad = std::acos(
                                        (d & nf)/(mag(d)*mag(nf))
                                    );
        theta = radToDegree(thetaRad);
    }
    else
    {
        const vector3& faceCenter= centerOfMass();
        const vector3 dn = faceCenter- C_o;
        double thetaRad = std::acos(
                                        (dn & nf)/(mag(dn)*mag(nf))
                                    );
        theta = radToDegree(thetaRad);

    }

    //setNonOrthogonalityFace(theta);
    nonOrthogonalityAngle_ = theta;
}


void Face::computeIntersectionPoint()
{
    bool isInteriorFace (neighbour());

    if (isInteriorFace)
    {
        const vector3& Cf = centerOfMass();

        const vector3& Sf = areaVector();

        // Owner Cell Center of Mass (CM)
        const vector3& Co = owner_->centerOfMass();
        // Neighbour Cell Center of Mass
        const vector3& Cn = neighbour_->centerOfMass();

        // Vector Owner CM to Face CM
        vector3 vecOF = Cf - Co;
        // Vector Face CM to Neighbour CM
        vector3 vecFN = Cn - Cf;
        // Vector Owner CM to Neighbour CM
        vector3 vecON = Cn-Co;

        // distance Owner CM to Face CM parallel to Face Area vector
        double dOF = abs((vecOF & Sf)/mag(Sf));
        // distance Face CM to Neighbour CM parallel to Face Area vector
        double dFN = abs((vecFN & Sf)/mag(Sf));

        // Face Intersection Point
        intersectionPoint_ = Co + (dOF / (dOF + dFN) ) * vecON;
    }
    else
    //boundary faces
    {
        // Owner CM
        vector3 Co = owner_->centerOfMass();

        // Vector Owner CM to Face CM
        vector3 vecOF = centerOfMass_ - Co;

        // Unit vector normal to the face
        vector3 unitNormalVectorFace = 1.0/mag(areaVector_) * areaVector_;

        // distance Owner CM to Face CM parallel to Face Area vector
        double dOF=abs(vecOF & unitNormalVectorFace );

        // Face Intersection Point
        intersectionPoint_ = Co+dOF*unitNormalVectorFace;
    }
}


void Face::computeSkewness()
{
    bool isInteriorFace ( neighbour() );

    const vector3& Cf = centerOfMass();

    const vector3& Sf = areaVector();

    const vector3& Co = owner_->centerOfMass();

    const vector3& Cn = neighbour_->centerOfMass();

    //const vector3& intersectionPoint = getIntersectionPoint();

    vector3 dOF = Cf - Co;

    double SMALL = 1e-15;

    double normSkewness = 0.0;

    if (isInteriorFace)
    {
        vector3 d = Cn - Co;

        // Compute skewness vector
        vector3 skewness = dOF - (Sf & dOF)  /  ( (Sf & d) + SMALL ) * d;

        vector3 normSkewnessVector = skewness/( mag(skewness) + SMALL );

        // Normalisation distance calculated as the approximate distance
        // from the face centre to the edge of the face in the direction
        // of the skewness
        double fd = 0.2*mag(d) + SMALL;

        for (unsigned int i = 0; i < facePoints_.size(); i++)
        {
            const vector3& tmp_point = facePoints_[i]->point();

            double tmp = std::abs(normSkewnessVector & (tmp_point - Cf) );

            fd = std::max(fd, tmp );
        }

        // normalized skewnnes
        normSkewness = mag(skewness)/fd;
    }
    else
    {

        vector3 nf = Sf/mag(Sf);

        vector3 dn =  nf*(nf & dOF);

        // Compute skewness vector
        vector3 skewness = dOF - (Sf & dOF)  /  ( (Sf & dn) + SMALL ) * dn;

        vector3 normSkewnessVector = skewness/( mag(skewness) + SMALL );

        // Normalisation distance calculated as the approximate distance
        // from the face centre to the edge of the face in the direction
        // of the skewness
        double fd = 0.4*mag(dn) + SMALL;

        for (unsigned int i = 0; i < facePoints_.size(); i++)
        {
            const vector3& tmp_point = facePoints_[i]->point();

            double tmp = std::abs(normSkewnessVector & (tmp_point - Cf) );

            fd = std::max(fd, tmp );
        }

        // normalized skewnnes
        normSkewness = mag(skewness)/fd;
    }

    skewness_ = normSkewness;
}

void Face::correctSf(){
    
    vector3 d{0};

    if (neighbour())
    {
        // distance vector between owner and neighbour cell
        d = neighbour_->centerOfMass() - owner_->centerOfMass();
    }
    else
    {
        d = centerOfMass_ - owner_->centerOfMass();
    }

    if( (areaVector_ & d) < 0)
    {
        // rotates area vector by 180º
        areaVector_=-1.0*areaVector_;
    }
}

std::ostream& operator<<(std::ostream& os, const Face& p)
{
    os << "[ " << std::endl;

    for (unsigned int i= 0; i < p.facePoints_.size() ; i++)
    {
        os << *p.facePoints_[i];
    }

    os << "]" << std::endl;

    return os;
}
