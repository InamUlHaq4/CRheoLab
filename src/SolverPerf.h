#ifndef SOLVERPERF_H
#define SOLVERPERF_H

#include <string>
#include <iostream>

#include "Dictionary.h"

/// Main class for solving the system of equations 
class SolverPerf
{
  public:
    SolverPerf();

    //Constructor
    SolverPerf(const Dictionary& fvSolutionSubDict, double residualFirst);

    //Destructor
    virtual ~SolverPerf()  = default;

    void perfShow();

    bool proceed();

    void update (double absResidual);

    void final (unsigned int duration);

    //Getters
    std::string solverModel();

  private:
    Dictionary fvSolutionSubDict_;
    bool converged_;
    std::string solverModel_;
    double maxAbsResidual_;
    double maxRelResidual_;
    unsigned int maxNumberOfIter_;
    double residualFirst_;
    double residualFinal_;
    unsigned int duration_;
    double absResidual_;
    double relResidual_;
    unsigned int numberOfIter_;

};

#endif
