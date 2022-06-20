#include "fvmLaplacian.h"
#include "mathOperations.h"
//#include "Mesh.h"
//#include "Face.h"
//#include "Cell.h"


namespace fvm
{   
    //Scalar Field situation
    FVMatrix laplacian(const double& K, VolField<scalarField>& vf)
    {
        FVMatrix fvMatrix(vf);
        //We will acess the  const Mesh& mesh attending the VolField <scalarField>& vf

        //***************Internal Faces contributions**************************************************//
                 //vf.mesh() gives the mesh of vf
        for(unsigned int i = 0; i < vf.mesh().nInteriorFaces_ ;i++)
        {
             int ownInd = vf.mesh().faceList_[i].getOwner()->ID_;//->ID_ will be soon replaced with a getter // <----------------------(Owner index) 
             int neiInd = vf.mesh().faceList_[i].getNeighbour()->ID_;  // <------- (Neighbour index)

             vector3 Sf = vf.mesh().faceList_[i].getAreaVector(); //<--------------Face area vector
             vector3 d =  vf.mesh().cellList_[ownInd].getCenterOfMass() - vf.mesh().cellList_[neiInd].getCenterOfMass(); // distance vector between onwer center and neighnour center (Q_P - Q_N)

             double d_modulus = sqrt( d & d); // |d| 
             double Sf_modulus =  sqrt( Sf & Sf);  //|Sf|
             double a = (Sf_modulus/d_modulus); // |S_f|/|d|

            fvMatrix.aMatrix_->addValue(ownInd,neiInd,K*a); // updating  non-diagonal components the aMatrix of FVM
            fvMatrix.aMatrix_->addValue(neiInd,ownInd,K*a);
  
            fvMatrix.aMatrix_->addValue(ownInd,ownInd,(-1)*fvMatrix.aMatrix_->getValue(ownInd,neiInd)); // updating  the diagonal components of aMatrix
            fvMatrix.aMatrix_->addValue(neiInd,neiInd,(-1)*fvMatrix.aMatrix_->getValue(neiInd,ownInd));
        }


        //******Here should the boundary Faces  Part **********//





        //****************************************************//



     
      return fvMatrix;
    }
    
}






