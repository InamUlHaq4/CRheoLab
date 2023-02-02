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
      

  private:
    std::string solverModel_;
    double residualFirst_;
    double residualFinal_;
    unsigned int countIter_;
    unsigned int duration_;
};

#endif
