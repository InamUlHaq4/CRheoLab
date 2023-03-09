// Main file for testing

#include <iostream>
#include "lilSpmat.h"

int main(int argc, char const *argv[]) {

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test lilSpmat class" << std::endl;
      std::cout << "#############################################################" << std::endl;

      std::vector<std::vector<double>> matrix
      {
        {1.0, 0.0, 2.0, 0.0},
        {0.0, 3.0, 0.0, 0.0},
        {0.0, 4.0, 0.0, 5.0},
        {0.0, 0.0, 0.0, 6.0}
      };

      std::cout << "Testing matrix:" << std::endl;
      for (unsigned int i = 0; i < matrix.size(); i++)
      {
            for (unsigned int j = 0; j < matrix[i].size(); j++)
            {
                  std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
      }

      //#############################################################

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix construction" << std::endl;
      std::cout << "#############################################################" << std::endl;

      // Declare and initialize a sparse matrix
      lilSpmat spmatA = lilSpmat(4,4);

      // add values
      spmatA.addValue(0,0,1.0);
      spmatA.addValue(0,2,2.0);
      spmatA.addValue(1,1,3.0);
      spmatA.addValue(2,1,4.0);
      spmatA.addValue(2,3,5.0);
      spmatA.addValue(3,3,6.0);
      
      // add some garbage values
      spmatA.addValue(2,2,100.0);
      spmatA.addValue(3,2,100.0);
     
      // delete garbage values
      spmatA.delValue(2,2);
      spmatA.delValue(3,2);

      std::cout << "Columns indexes:" << std::endl;
      for (unsigned int i = 0; i < spmatA.columns_.size(); i++)
      {
            for (unsigned int j = 0; j < spmatA.columns_[i].size(); j++)
            {
                  std::cout << spmatA.columns_[i][j] << " ";
            }
            std::cout << std::endl;
      }

      std::cout << "Columns values:" << std::endl;
      for (unsigned int i = 0; i < spmatA.values_.size(); i++)
      {
            for (unsigned int j = 0; j < spmatA.values_[i].size(); j++)
            {
                  std::cout << spmatA.values_[i][j] << " ";
            }
            std::cout << std::endl;
      }

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix to dense format" << std::endl;
      std::cout << "#############################################################" << std::endl;

      // Vector of vectors to store the sparse matrix in a dense format
      std::vector< std::vector<double> > denseMatrix;

      // Returns the sparse matrix in a dense format as a vector of vectors
      denseMatrix = spmatA.dense();

      std::cout << "Dense matrix:" << std::endl;
      for (unsigned int i = 0; i < denseMatrix.size(); i++)
      {
            for (unsigned int j = 0; j < denseMatrix[i].size(); j++)
            {
                  std::cout << denseMatrix[i][j] << " ";
            }
            std::cout << std::endl;
      }

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix multiplication" << std::endl;
      std::cout << "#############################################################" << std::endl;

      std::vector<double> vecPhi{ 1.0, 2.0, 3.0, 4.0};

      std::cout << "Phi vector for multiplication:" << std::endl;
      for (double valuePhi : vecPhi)
            std::cout << valuePhi << std::endl;

      std::vector<double> v(4);

      // Call the function that calculates the product matrix-vector
      v = spmatA * vecPhi;

      std::cout << "Vector resulting from the matrix-vector product:" << std::endl;
      for (double valueV : v)
            std::cout << valueV << std::endl;

      unsigned int rowMatVecProd = 2;

      // Call the function that calculates the product (row-of-matrix)-vector
      double ProdRowMatVec = spmatA.vecRowMul(rowMatVecProd, vecPhi);

      std::cout << "Double resulting from the (row-of-matrix)-vector product:" << std::endl;
      std::cout << "For row: " << rowMatVecProd << ", Product: " << ProdRowMatVec << std::endl;

      std::cout << "#############################################################" << std::endl;
      std::cout << "JCastro tests" << std::endl;
      std::cout << "#############################################################" << std::endl << std::endl;

      // Create new matrix B with addValue functions
      lilSpmat spmatB = lilSpmat(4,4,"B");

      spmatB.addValue(0,0,2.0);
      spmatB.addValue(0,2,3.0);
      spmatB.addValue(1,1,4.0);
      spmatB.addValue(2,1,5.0);
      spmatB.addValue(2,3,6.0);
      spmatB.addValue(3,3,7.0);
      // spmatB.addValue(4,3,8.0);

      std::cout << spmatB << std::endl;
      
      // Add matrices
      lilSpmat spmatC;  	//default C matrix
      lilSpmat spmatD;  	//default D matrix    

      spmatC = spmatA + spmatA;
      spmatD = spmatA + spmatB;

      // giving the matrices a name
      spmatC.setName("C");
      spmatD.setName("D");

      // std::cout << spmatC << std::endl;
      // std::cout << spmatD << std::endl;

      // Create a matrix with name
      lilSpmat spmatAA = lilSpmat(4,4,"AA mat");

      std::cout << spmatAA << std::endl;

      // Test addition/subtraction compatibility
      lilSpmat spmatBB = lilSpmat(4,3,"BB mat");
      // lilSpmat spmatCC = spmatAA + spmatBB;
      // std::cout << spmatCC << std::endl;

      // Test multiplication compatibility
      std::vector<double> vec1{1.0, 2.0, 3.0, 4.0};
      std::vector<double> vecTest = spmatB * vec1;
      std::cout << vecTest << std::endl;

      std::vector<std::vector<double>> vec2{{0.0, 1.0, 2.0, 3.0},{3.0, 2.0, 1.0, 0.0},{0.0, 1.0, 2.0, 3.0},{3.0, 2.0, 1.0, 0.0}};
      std::vector<std::vector<double>> vecTest2 = spmatB * vec2;
      std::cout << vecTest2 << std::endl;

      // Test matrix multiplication
      lilSpmat spmatEE = spmatB * spmatB;
      std::cout << spmatEE << std::endl;


// Jayesh Feb 2023 (Testing for Matrix Substration and Multiplication)
////////////////////////////////////////////////////////////////////////////
      // std::cout << "#############################################################" << std::endl;
      // std::cout << "Jayesh tests" << std::endl;
      // std::cout << "#############################################################" << std::endl << std::endl;


      // std::cout << "A " << spmatA << std::endl;
      
      // lilSpmat spmatE = lilSpmat(4,4);

      // spmatE.addValue(0,0,9.0);
      // spmatE.addValue(0,3,1.0);
      // spmatE.addValue(1,2,7.0);
      // spmatE.addValue(2,0,8.0);
      // spmatE.addValue(2,3,3.0);
      // spmatE.addValue(3,0,5.0);

      // std::cout << "E " << spmatE << std::endl;
      
      // lilSpmat spmatF;  	
      // lilSpmat spmatG;  

      // std::cout << "#############################################################" << std::endl;
      // std::cout << "Test sparse matrix subtraction" << std::endl;
      // std::cout << "#############################################################" << std::endl;

      // spmatF = spmatA - spmatE;

      // std::cout << "F " << spmatF << std::endl;

      // std::cout << "#############################################################" << std::endl;
      // std::cout << "Test sparse matrix Multiplication" << std::endl;
      // std::cout << "#############################################################" << std::endl;

      // spmatG = spmatA * 7;

      // std::cout << "G " << spmatG << std::endl;
      // ///////////////////////////////////////////////////////////////////


      std::cout << "A " << spmatA << std::endl;
      std::vector <double> vecR;
      std::vector <double> vecV ={1, 2, 3, 4};

      vecR = spmatA * vecV;

      for (unsigned int i = 0; i < vecR.size(); i++)
      {
            std::cout << vecR[i] << std::endl;
      }
      
      
      return 0;
}
