#include "fvmLaplacian.h"
#include "mathOperations.h"
#include "fvBoundaryConditionsField.h"

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


        // *** Boundary faces contributions ---------------------------------------------------- ***//

        // Initializing boundary conditions coefficient contributions
        fvBoundaryConditionsField<scalarField> boundaryConditions(vf);
        long unsigned int patchesSize = vf.mesh().nPatches_;
        double diffusionK(K);
        for ( long unsigned int patchI = 0; patchI < patchesSize; patchI++)
        { 
          // std::cout << "This is the patch: " << patchI << std::endl;
          // Loading the faces controls for this patch
          int sizeOfPatch( boundaryConditions.coefficientsData().at(patchI).gradientInternalCoeffs.size() );
          int startPatchFaceID = vf.mesh().patchList_[patchI].startFace();

          // Looping in all the faces for this patch
          for (int faceI = 0; faceI < sizeOfPatch; faceI++)
          {
            vector3 areaVec = vf.mesh().faceList_[startPatchFaceID+faceI].getAreaVector();
            double  areaMag = mag(areaVec);

            //std::cout << "This is the face: " << startPatchFaceID+faceI << std::endl;
            // Retrieving the boundary face owner cell ID
            int ownInd = vf.mesh().faceList_[startPatchFaceID+faceI].getOwner()->ID_;
            
            // std::cout << "It's Owner Cell is the cell: " << ownInd << std::endl;
            // Loading the values to added for the laplacian term
            double valueToAddDiagonal( boundaryConditions.coefficientsData().at(patchI).gradientInternalCoeffs.at(faceI));
            double valueToAddSource( boundaryConditions.coefficientsData().at(patchI).gradientBoundaryCoeffs.at(faceI));
            
            // Adding the loaded values to the proper places
            fvMatrix.aMatrix_->addValue(ownInd,ownInd,(-diffusionK*valueToAddDiagonal*areaMag));
            fvMatrix.bVector_.at(ownInd) += (diffusionK*valueToAddSource*areaMag) ;
          }
        }
  
        // ***-End-of-Boundary-faces-contributions---------------------------------------------- ***// 

     
      return fvMatrix;
    }
    
}






