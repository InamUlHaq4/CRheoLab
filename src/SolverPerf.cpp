
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

bool SolverPerf::proceed()
{
    if ( absResidual_ > maxAbsResidual_ && relResidual_ > maxRelResidual_ && countIter_ < maxNumberOfIter_) return true;

    return false;
}

//void SolverPerf:: init (std::string solverModel , double absNormResidual , double relNormResidual , unsigned int maxNumberOfIter , double residualFirst )
void SolverPerf:: init (std::string solverModel , double maxAbsResidual , double maxRelResidual , unsigned int maxNumberOfIter , double residualFirst )
{
    solverModel_ = solverModel;
    //absNormResidual_ = absNormResidual;
    //relNormResidual_ = relNormResidual;
    maxAbsResidual_ = maxAbsResidual;
    maxRelResidual_ = maxRelResidual;
    maxNumberOfIter_ = maxNumberOfIter;
    residualFirst_ = residualFirst;
}

void SolverPerf::update (double absResidual,double relResidual, unsigned int countIter)
{
    absResidual_ = absResidual;
    relResidual_ = relResidual;
    countIter_ = countIter;
}

void SolverPerf::final (double residualFinal, unsigned int countIter, unsigned int duration)
{
    residualFinal_ = residualFinal;
    countIter_ = countIter;
    duration_ = duration;
}
