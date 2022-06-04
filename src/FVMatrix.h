#ifndef FVMATRIX_H
#define FVMATRIX_H

#include "Mesh.h"
#include "SJacobi.h"
#include "SGaussSiedel.h"
#include "SSOR.h"
#include "Reader.h"
#include "lilSpmat.h"
#include "csrSpmat.h"
//#include "IODictionary.h"
//#include "IODictionaryw.h"
#include "Dictionary.h"
#include "IOObject.h"

/// Main class for solving the system of equations 
class FVMatrix
{
    public:

        // Default constructor
        // normResidual - should contain the current normalized residual value
        // normResidualIni - should contain the current normalized residual value when the solver method was called
        // absNormResidual - maximum value allowed for the normResidual, if the normResidual < absNormResidual the iteration process should end
        // relNormResidual - minimum reduction required for the normResidual, if normResidual/normResidualIni < relNormResidual the iteration process should end
        /// Default constructor
        FVMatrix(Mesh& mesh, vector<double>& xVector);

        /// Destructor
        virtual ~FVMatrix();

        // Member Functions

        /// Function for a multiplication of a matrix row by a vector, which results in a scalar 
        inline double axMultiplication(const unsigned int& i);
    /*    inline double normalizedResidualValue();*/

        /// Function for calculating the norm of the residual vector \f$\left \| R \right \| \f$ (the first norm)        
      /**  \begin{equation}
        \left \|\left \| R \right \|\right \|= \sum_{i=1}^{N}\begin{vmatrix}
        r_i
        \end{vmatrix}
        \end{equation}*/
        inline double residualValue();

        /// Funtion to calculate the residual scalling factor \f$ n \f$ as
        /**
        \begin{equation}
        n=\sum_{i=1}^{N}
        (\begin{vmatrix}
        AX-A\overline{X}
        \end{vmatrix}) +
        \begin{vmatrix}
        B-A\overline{X}
        \end{vmatrix})
        \end{equation}

        \f$\overline{X}\f$ is the average of the solution vector {\f$ X \f$ }  
        */
        inline double residualNormFactor();

        /// Function for a multiplication of a matrix row by the average of the solution vector \f$\overline{X}\f$, which results in a scalar
        inline double axAverageMultiplication(const unsigned int &i);

        /// Function to create random full matrix such that its diagonal is larger than the sum of the absolue of the elements in the matrix row 
        /// (\f$ a_{ii}\f$ > \f$ \sum_{j=1, j \neq i}^{N} a_{ij} \f$). The function also creates a random vector \f$ b\f$
        void createRandomFullaMatrixbVector();

        /// Function to create random sparse matrix, it also creates a random vector \f$ b\f$
        void createRandomSparseaMatrixbVector(const Mesh &mesh);

        /// Print the matrix elements
        void printaMatrix(std::vector<double>& mat, int n, int m);

        /// Reset the \f$ X\f$ vector to zero
        void resetxVector();

        /// Initialize a solver class of either type Jacobi or GaussSiedel or SOR  
        void setSolver(std::string solvername);

        /// Function for solving the system of equations according to the selected solver. It also calculates and uses the absolute and relative residuals for convergence. 
        /** The scalled residual \f$ \frac{1}{n} \sum_{i=1}^{N}\begin{vmatrix} r_i \end{vmatrix} \f$ is used as the absolute residual. 
        The relative residual is calculated as the scalled residual normalized with respect to the scalled residual at the first iteration.   */     
        std::vector<double> solve();

    private:
        /// \f$ b \f$ vector
        std::vector<double> bVector_;
        /// \f$ X \f$ vector
        std::vector<double>* xVector_;
        /// Number of the elements in the system i.e. the size of the system 
        unsigned int nCells_;
         /// \f$ A \f$ matrix
        spmat* aMatrix_;
        /// Matrix format either lOLists or CSR
        std::string matrixFormat_;
        /// Matrix type either full or sparse
        std::string matrixType_;
        /// Value of the absolute residual that should be satisfied for convergence 
        double absNormResidual_;
        /// Value of the relative residual that should be satisfied for convergence 
        double relNormResidual_;
      //  double normResidual_;
      //  double residualNormFactor_;
        /// Solver for the system of equations with either the type Jacobi or Gauss Siedel or SOR  
        FVMatrixSolver* Solver_;   
        /// Name of the solver for the system of equations with either the name Jacobi or Gauss Siedel or SOR   
        std::string solverModel_;
        /// Reading the solution parameters from a file 
        //Reader readParameter_;
        /// \f$\overline{X}\f$ is the average of the solution vector {\f$ X \f$ } 
        double xAverage_;    
        /// The residual scalling factor \f$ n \f$ 
        double nNormalize_; 
         /// Dictionary for the class
        Dictionary myDict_; 
};

#endif
