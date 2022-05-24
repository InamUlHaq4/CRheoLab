// Main file for profiling

#include <iostream>
#include "lilSpmat.h"
#include "Mesh.h"
#include <chrono>
#include <iomanip>      // std::setprecision
#include <math.h>

int main(int argc, char const *argv[]) {

      std::cout << "#############################################################" << std::endl;
      std::cout << "Profile lilSpmat class" << std::endl;
      std::cout << "#############################################################" << std::endl;

      // Initialize the mesh
      Mesh mesh;

      // Number of samples
      unsigned int NS = 1000;
      double time1 = 0.0;
      double time2 = 0.0;
      double time3 = 0.0;

      for (unsigned int i = 0; i < NS; i++)
      {

            // Test sparse matrix construction - Test 1

            // Duration 1 start
            auto start1 = std::chrono::high_resolution_clock::now();

            // Declare and initialize a sparse matrix
            lilSpmat *spmat = new lilSpmat(mesh.nCells_,mesh.nCells_);

            auto stop1 = std::chrono::high_resolution_clock::now();
            auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
            time1 += (pow (10.0, -6.0) * duration1.count());
            // Duration 1 end

            // Test sparse matrix fill-in - Test 2

            // Declaration of variables
            const Cell* neigh_ptr;
            const Cell* owner_ptr;

            // Duration 2 start
            auto start2 = std::chrono::high_resolution_clock::now();

            // Fill-in the sparse matrix with the positions of the non-null values
            for (unsigned int i=0;i<mesh.nCells_;i++)
            {
                  spmat->addValue(i,i,1.0);
                  for (unsigned int j=0;j<mesh.cellList_[i].cellFaces_.size();j++)
                  {
                        neigh_ptr = mesh.cellList_[i].cellFaces_[j]->getNeighbour();
                        owner_ptr = mesh.cellList_[i].cellFaces_[j]->getOwner();
                        if(neigh_ptr != NULL)
                        {
                              if(neigh_ptr->ID_ == i)
                              {
                                    spmat->addValue(i,owner_ptr->ID_,1.0);
                              }
                              else //if(owner_ptr.ID_ == i)
                              {
                                    spmat->addValue(i,neigh_ptr->ID_,1.0);
                              }
                        }
                  }
            }

             auto stop2 = std::chrono::high_resolution_clock::now();
            auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
            time2 += (pow (10.0, -6.0) * duration2.count());
            // Duration 2 end

            // Test sparse matrix multiplication - Test 3

            // Declaration of variables
            std::vector<double> vecPhi;
            vecPhi.resize(mesh.nCells_);

            std::vector<double> v;
            v.resize(mesh.nCells_);

            // Duration 3 start
            auto start3 = std::chrono::high_resolution_clock::now();

            // Call the function that calculates the product matrix-vector
            v = spmat->matMul(vecPhi);

            auto stop3 = std::chrono::high_resolution_clock::now();
            auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start3);
            time3 += (pow (10.0, -6.0) * duration3.count());
            // Duration 3 end

            // Destructor
            delete spmat;

      }

      std::cout << "Elapsed time for Sparse Matrix construction: " << std::fixed << std::setprecision(3) << time1 << " s" << std::endl;

      std::cout << "Elapsed time for Sparse Matrix Fill-in: " << std::fixed << std::setprecision(3)  << time2 << " s" << std::endl;

      std::cout << "Elapsed time for Sparse Matrix Multiplication: " << std::fixed << std::setprecision(3) << time3 << " s" << std::endl;

      return 0;
}
