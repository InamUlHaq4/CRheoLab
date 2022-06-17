
#include "SolverPerf.h"


SolverPerf::SolverPerf()
{ }

SolverPerf::SolverPerf(std::string solverModel, double residualFirst,double residualFinal, unsigned int countIter, unsigned int duration) : 
    solverModel_(solverModel)
    , residualFirst_(residualFirst)
    , residualFinal_(residualFinal)
    , countIter_(countIter)
    , duration_(duration)
{
    
}

SolverPerf::~SolverPerf()
{ }

void SolverPerf::perfShow()
{
    std::cout << std::string(90, '#') << std::endl;
    std::cout << ">>> Solved by "<< solverModel_ << "<<<<<" << std::endl;
    std::cout << std::string(90, '#') << std::endl;
    std::cout << std::string(120, '#') << std::endl;
    std::cout << "Number of Iterations: " << countIter_ << std::endl;
    std::cout << "Initial Residual: " << std::scientific << residualFirst_ << " -> Final Residual: " << std::scientific << residualFinal_ << std::endl;
    std::cout << "Elapsed time:" << duration_ << " ms" << std::endl;
    std::cout << std::string(90, '#') << std::endl;
}


