// Main file for profiling

#include <iostream>
#include "csrSpmat.h"
#include "Mesh.h"

int main(int argc, char const *argv[]) {

      std::cout << "#############################################################" << std::endl;
      std::cout << "Profile csrSpmat class" << std::endl;
      std::cout << "#############################################################" << std::endl;

      // Initialize the mesh
      Mesh mesh;

      // Number of samples
      unsigned int NS = 1000;

      // Time counters
      double time1;
      double time2;
      double time3;

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix construction" << std::endl;
      std::cout << "#############################################################" << std::endl;

      // Time 1 start

      // Declare and initialize a sparse matrix
      csrSpmat spmat;
      for(unsigned int i=0;i<NS;i++)
      {
            spmat = csrSpmat(mesh);
      }

      // Time 1 end

      // Print time on console
      std::cout << "Time 1: " << time1 << std::endl;

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix fill-in" << std::endl;
      std::cout << "#############################################################" << std::endl;

      // Declaration of variables
      const Cell* neigh_ptr;
      const Cell* owner_ptr;

      // Time 2 start

      // Fill-in the sparse matrix with the positions of the non-null values
      for(unsigned int i=0;i<NS;i++)
      {
            for (unsigned int i=0;i<mesh.nCells_;i++)
            {
                  spmat.addValue(i,i,1.0);
                  for (unsigned int j=0;j<mesh.cellList_[i].cellFaces_.size();j++)
                  {
                        neigh_ptr = mesh.cellList_[i].cellFaces_[j]->getNeighbour();
                        owner_ptr = mesh.cellList_[i].cellFaces_[j]->getOwner();
                        if(neigh_ptr != NULL)
                        {
                              if(neigh_ptr->ID_ == i)
                              {
                                    spmat.addValue(i,owner_ptr->ID_,1.0);
                              }
                              else //if(owner_ptr.ID_ == i)
                              {
                                    spmat.addValue(i,neigh_ptr->ID_,1.0);
                              }
                        }
                  }
            }
      }

      // Time 2 end

      // Print time on console
      std::cout << "Time 2: " << time2 << std::endl;

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix multiplication" << std::endl;
      std::cout << "#############################################################" << std::endl;

      // Declaration of variables
      std::vector<double> vecPhi;
      vecPhi.resize(mesh.nCells_);
      std::vector<double> v;
      v.resize(mesh.nCells_);

      // Time 3 start

      // Call the function that calculates the product matrix-vector
      for(unsigned int i=0;i<NS;i++)
      {
            v = spmat.matMul(vecPhi);
      }

      // Time 3 end

      // Print time on console
      std::cout << "Time 3: " << time3 << std::endl;

      return 0;
}
