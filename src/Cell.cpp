#include "Face.h"

Cell::Cell()
:
    ID_(-1),
    volume_(-1),
    centerOfMass_({-1,-1,-1}),
    skewness_(-1),
    cellFaces_()
{}

// Setters

void Cell::setID(const int& ID)
{
    ID_ = ID;
}
void Cell::setCellFaces(const vector<Face*>& cellFaces)
{
    cellFaces_= cellFaces;
}

// Getters
const vector3& Cell::centerOfMass() const
{
    return centerOfMass_;
}

const double& Cell::volume() const
{
    return volume_;
}

const double& Cell::maxNonOrthogonality() const
{
    return maxNonOrthogonality_;
}

const double& Cell::skewness() const
{
    return skewness_;
}

const int& Cell:: ID() const
{
    return ID_;
}

const vector<Face*>& Cell::cellFaces() const
{
    return cellFaces_;
}


// Computations
void Cell::computeVolume()
{
    const vector3 geometricCenter = computeGeometricCenter();

    double cellVolume = 0;
    
    for(unsigned int faceI = 0; faceI < cellFaces_.size(); faceI++)
    {    
			const vector3& Sf = cellFaces_[faceI]->AreaVector();   

      const vector3& Cf = cellFaces_[faceI]->CenterOfMass();

      //Accumulate volume-weighted face-pyramid center
      double pyrvol = computepyrVol(Sf, Cf, geometricCenter);

			//Accumulate volume-weighted face-pyramid center
      cellVolume += pyrvol;      
    }

    volume_ = cellVolume;                                                                    
}


void Cell::computeCenter()
{
    const vector3 geometricCenter = computeGeometricCenter();
 
    vector3 cellCenter {0,0,0};

    for(unsigned int faceI = 0; faceI < cellFaces_.size(); faceI++)
    {     
      const vector3& Sf = cellFaces_[faceI]->AreaVector();
      
      const vector3& Cf = cellFaces_[faceI]->CenterOfMass();

      double pyrVol  = computepyrVol(Sf, Cf, geometricCenter);
     
      const vector3 pyrc = (0.75)*Cf + (0.25)*geometricCenter;

      cellCenter = cellCenter + pyrc*pyrVol;
    }

   centerOfMass_ = cellCenter/volume_;
}


double Cell::computepyrVol(const vector3& Sf, const vector3& Cf, const vector3& geometricCenter)const
{
    double VSMALL = 1.0e-37;

    const vector3  d_gf = Cf -geometricCenter;

    // Check if the normal is in the right direction
    double flipNormal = 1;

    if((Sf & d_gf) < 0)
    {
        flipNormal = -1;
    }

    // Computes the volume of the sub-pyramid
    double pyrVol = std::max(  
                                ( (flipNormal*Sf) & d_gf) 
                              , VSMALL
                            )/3;
    
    return pyrVol;

}

vector3 Cell::computeGeometricCenter() const
{
   vector3 geometricCenter {0,0,0};

    for(unsigned int faceI = 0; faceI <cellFaces_.size(); faceI++)
    {
      const vector3& Cf = cellFaces_[faceI]->CenterOfMass();  

      geometricCenter = geometricCenter + Cf;
  
    }
    geometricCenter=geometricCenter/cellFaces_.size(); 

    return geometricCenter;
}

void Cell::computeMaxNonOrthogonality()
{
    double maxNonOrthogonalityAngle = 0.0;
    for (unsigned int i=0; i< this->cellFaces_.size(); i++)
    {
        maxNonOrthogonalityAngle= std::max(
                                                maxNonOrthogonalityAngle,
                                                cellFaces_[i]->NonOrthogonality()
                                            );
    }

    maxNonOrthogonality_= maxNonOrthogonalityAngle;
}

void Cell::computeSkewness()
{
    double maxSkewness = 0.0;
    for (unsigned int i=0; i< this->cellFaces_.size(); i++)
    {

        maxSkewness = std::max(
                                                maxSkewness,
                                                cellFaces_[i]->Skewness()
                                            );
    }

    skewness_ = maxSkewness;
}
