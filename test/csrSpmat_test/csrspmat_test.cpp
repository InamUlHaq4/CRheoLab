// Main file for testing

#include <iostream>
#include "csrSpmat.h"

int main(int argc, char const *argv[]) {

      /*
      std::cout << "#############################################################" << std::endl;
      std::cout << "Test csrSpmat class" << std::endl;
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

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix construction" << std::endl;
      std::cout << "#############################################################" << std::endl;

      csrSpmat spmatA;

      spmatA.numRows_ = 4;
      spmatA.numCols_ = 4;
      spmatA.numNZ_ = 6;
      spmatA.columns_ = {0,2,1,1,3,3};
      spmatA.values_ = {1.0,2.0,3.0,4.0,5.0,6.0};
      spmatA.rowPtr_ = {0,2,3,5,6}; ///!!!!

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

      std::vector<double> vecPhi;
      vecPhi.resize(spmatA.getNumCols());

      std::cout << "Phi vector for multiplication:" << std::endl;
      for (double valuePhi : vecPhi)
            std::cout << valuePhi << std::endl;

      std::vector<double> v;
      v.resize(spmatA.getNumCols());

      // Call the function that calculates the product matrix-vector as a vector
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
      std::cout << "Test sparse matrix addition" << std::endl;
      std::cout << "#############################################################" << std::endl;

      // Create new matrices B and C
      csrSpmat spmatB = spmatA;
      csrSpmat spmatC = spmatA;

      csrSpmat *spmatA_ptr = &spmatA;
      csrSpmat *spmatB_ptr = &spmatA;
      csrSpmat *spmatC_ptr = &spmatA;

      // Add matrices
      spmatC = spmatA + spmatB;

      spmatC_ptr = spmatA + spmatA_ptr;

      spmatC_ptr = *spmatA_ptr + spmatA_ptr;

      // Returns the sparse matrix in a dense format as a vector of vectors
      denseMatrix = spmatC.dense();

      std::cout << "Dense matrix:" << std::endl;

      for (unsigned int i = 0; i < denseMatrix.size(); i++)
      {
            for (unsigned int j = 0; j < denseMatrix[i].size(); j++)
            {
                  std::cout << denseMatrix[i][j] << " ";
            }
            std::cout << std::endl;
      }

      // Returns the sparse matrix in a dense format as a vector of vectors
      denseMatrix = spmatC_ptr->dense();

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
      std::cout << "Test sparse matrix subtraction" << std::endl;
      std::cout << "#############################################################" << std::endl;

                  //Jayesh Feb 2023

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix Multiplication" << std::endl;
      std::cout << "#############################################################" << std::endl;

      csrSpmat spmatE;
      csrSpmat spmatF;
      csrSpmat* spmatG;


      spmatE.numRows_ = 4;
      spmatE.numCols_ = 4;
      spmatE.numNZ_ = 9;
      spmatE.columns_ = {0,2,1,1,3,0,1,2,3};
      spmatE.values_ = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0};
      spmatE.rowPtr_ = {0,2,3,5,9};

      std::cout << "E " << spmatE << std::endl;
      spmatF = spmatE * 2;
      std::cout << "F " << spmatF << std::endl;
      double* testVal = new double(3);

      spmatG = spmatE * testVal;
      
      std::cout << "G " << *spmatG << std::endl;

      */
      std::cout << "#############################################################" << std::endl;
      std::cout << "JCastro tests" << std::endl;
      std::cout << "#############################################################" << std::endl << std::endl;

      csrSpmat spmatAB = csrSpmat(4,4,"AB csrmat");

      spmatAB.columns_ = {0,2,1,1,3,3};
      spmatAB.values_ = {1.0,2.0,3.0,4.0,5.0,6.0};
      spmatAB.rowPtr_ = {0,2,3,5,6};
      
      spmatAB.addValue(0,1,9);
      spmatAB.addValue(1,3,9);
      spmatAB.addValue(2,0,9);
      spmatAB.addValue(3,3,9);
      spmatAB.setValue(0,0,7);
      spmatAB.setValue(0,3,8);

      // why have addValue and subValue?

      std::cout << spmatAB << std::endl;

      csrSpmat spmatAA = csrSpmat(4,4,"AA csrmat");

      spmatAA.numNZ_ = 6; // why is this needed?
      spmatAA.columns_ = {0,2,1,1,3,3};
      spmatAA.values_ = {1.0,2.0,3.0,4.0,5.0,6.0};
      spmatAA.rowPtr_ = {0,2,3,5,6};

      std::cout << spmatAA << std::endl;

      // Test multiplication compatibility
      std::vector<double> vec1{1.0, 2.0, 3.0, 4.0};
      std::vector<double> vecTest = spmatAA * vec1;
      std::cout << vecTest << std::endl;

      csrSpmat spmatBB = spmatAA * spmatAA;
      std::cout << spmatBB << std::endl;
      
      // printf("x= %10.2e\n", x) function for matrices

      // Example matrices in CSR format
      // vector<double> valuesA = { 1, 2, 3, 4, 5, 6 };
      // vector<int> rowIndicesA = { 0, 2, 3, 1, 2, 3 };
      // vector<int> colPointersA = { 0, 2, 3, 6 };

      // vector<double> valuesB = { 1, 2, 3, 4, 5, 6 };
      // vector<int> rowIndicesB = { 0, 1, 2, 0, 1, 2 };
      // vector<int> colPointersB = { 0, 3, 6 };

      // // Perform matrix multiplication
      // vector<vector<double>> result = matrixMultiply(valuesA, rowIndicesA, colPointersA, valuesB, rowIndicesB, colPointersB, 3);

      // // Output result
      // for (int i = 0; i < result.size(); i++) {
      //       for (int j = 0; j < result[0].size(); j++) {
      //             cout << result[i][j] << " ";
      //       }
      //       cout << endl;

      return 0;
}