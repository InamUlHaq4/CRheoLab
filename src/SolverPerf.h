#ifndef SOLVERPERF_H
#define SOLVERPERF_H

#include <string>
#include <iostream>

/// Main class for solving the system of equations 
class SolverPerf
{
  public:
    SolverPerf();

    SolverPerf(std::string solverModel, double residualFirst,double residualFinal, unsigned int countIter, unsigned int duration);

    void perfShow();

    virtual ~SolverPerf();

    bool proceed();

    void init (std::string solverModel , double maxAbsResidual , double maxRelResidual , unsigned int maxNumberOfIter , double residualFirst); 

    void update (double absResidual,double relResidual, unsigned int countIter);

    void final (double residualFinal, unsigned int countIter, unsigned int duration);

  private:
    bool converged;
    std::string solverModel_;
    double residualFirst_;
    double residualFinal_;
    unsigned int countIter_;
    unsigned int duration_;
    double maxAbsResidual_;
    double maxRelResidual_;
    unsigned int maxNumberOfIter_;
    double absResidual_;
    double relResidual_;

};

#endif
