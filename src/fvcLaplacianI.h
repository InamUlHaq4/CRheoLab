#include "fvcLaplacian.h"
#include "mathOperations.h"
#include "fvBoundaryConditionsField.h"

//#include "Mesh.h"
//#include "Face.h"
//#include "Cell.h"


namespace fvc
{   
    //Scalar Field situation
    std::vector<double> laplacian(const double& K, VolField<scalarField>& vf)
    {
      std::vector<double> vecB(vf.mesh().nCells_,0.0);
        //FVMatrix fvMatrix(vf);
        //We will access the  const Mesh& mesh attending the VolField <scalarField>& vf

        //***************Internal Faces contributions**************************************************//

        for(long unsigned int i = 0; i < vf.mesh().nInteriorFaces_ ;i++)
        {
             int ownInd = vf.mesh().faceList_[i].getOwner()->ID_;
             int neiInd = vf.mesh().faceList_[i].getNeighbour()->ID_;

             vector3 Sf = vf.mesh().faceList_[i].getAreaVector(); 
             vector3 d =  vf.mesh().cellList_[ownInd].getCenterOfMass() - vf.mesh().cellList_[neiInd].getCenterOfMass();

             double d_modulus = sqrt( d & d); // |d| 
             double Sf_modulus =  sqrt( Sf & Sf);  //|Sf|
             double a = (Sf_modulus/d_modulus); // |S_f|/|d|

            vecB.at(ownInd) += ((K)*(-a)*vf.internalFieldRef().at(ownInd));
            vecB.at(neiInd) += (-(K)*(-a)*vf.internalFieldRef().at(neiInd));
            
        };
      
      // *** Boundary faces contributions ---------------------------------------------------- ***//

        // // Initializing boundary conditions coefficient contributions
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
            // fvMatrix.aMatrix_->addValue(ownInd,ownInd,(+diffusionK*valueToAddDiagonal*areaMag));
            // fvMatrix.bVector_.at(ownInd) += (-diffusionK*valueToAddSource*areaMag) ;
            vecB.at(ownInd) += ( +diffusionK*valueToAddDiagonal*areaMag*vf.internalFieldRef().at(ownInd) );
            vecB.at(ownInd) += ( +diffusionK*valueToAddSource  *areaMag                                    );
         }
        }
        // ***-End-of-Boundary-faces-contributions---------------------------------------------- ***// 

      return vecB;
    }
    
}
