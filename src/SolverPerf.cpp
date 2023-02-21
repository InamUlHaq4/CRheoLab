
#include "SolverPerf.h"

SolverPerf::SolverPerf()
{ }

SolverPerf::SolverPerf(const Dictionary& fvSolutionSubDict, double residualFirst): 
    fvSolutionSubDict_(fvSolutionSubDict)
    , residualFirst_(residualFirst)
{

    maxAbsResidual_ = fvSolutionSubDict_.lookup<double> ("maxAbsResidual");
    maxRelResidual_ = fvSolutionSubDict_.lookup<double> ("maxRelResidual");
    solverModel_ = fvSolutionSubDict_.lookup<std::string> ("solverModel");
    maxNumberOfIter_ = fvSolutionSubDict_.lookupOrDefault<unsigned int> ("maxNumberOfIter", 1000);
    numberOfIter_ = 0;
    absResidual_ = residualFirst;
    residualFirst_= residualFirst;
    relResidual_ = 1.0;   
    converged_ = false;
}

void SolverPerf::perfShow()
{
    std::cout << std::endl;
    std::cout << std::string(90, '#') << std::endl;
    std::cout << ">>> Solved by "<< solverModel_ << "<<<<<" << std::endl;
    std::cout << std::string(90, '#') << std::endl;
    if (converged_)
    {
        std::cout << "The solution converged after " << numberOfIter_ << " iterations" << std::endl;
    }
    else
    {
        std::cout << "Not converged after reaching the maximum number of iterations(" << maxNumberOfIter_ << ")" << std::endl;
    }
    std::cout << "Initial Absolute Residual: " << std::scientific << residualFirst_ << " -> Final Absolute Residual: " << std::scientific << absResidual_ << std::endl;
    std::cout << "Final Relative Residual: " << std::scientific << relResidual_ << std::endl;
    std::cout << "Elapsed time:" << duration_ << " ms" << std::endl;
    std::cout << std::string(90, '#') << std::endl;

}

bool SolverPerf::proceed()
{
    if ( absResidual_ > maxAbsResidual_ && relResidual_ > maxRelResidual_ && numberOfIter_ < maxNumberOfIter_) 
    {   
        numberOfIter_ +=1;
        return true;
    }
    if ( absResidual_ <= maxAbsResidual_ || relResidual_ <= maxRelResidual_ ) converged_ = true;
    return false;
}

void SolverPerf::update (double absResidual)
{
    absResidual_ = absResidual;
    relResidual_ = absResidual_ / residualFirst_;
}

void SolverPerf::final (unsigned int duration)
{
    duration_ = duration;
}

//Getters
std::string SolverPerf::solverModel()
{
    return solverModel_;
}