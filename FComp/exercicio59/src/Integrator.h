#ifndef H_INTEGRATOR_H
#define H_INTEGRATOR_H

#include "Func1D.h"
#include "Derivator.h"

class Integrator: public Func1D
{
  public:
    Integrator(double xbeg=0, double xend=0, TF1* func=NULL);
    ~Integrator() {;}
    void SetBoundaries(double x_0,double x_1);
    void TrapezoidalRule(int n, double& result, double& error);
    void SimpsonRule(int n, double& result, double& error);
  protected:
    double x0;
    double x1;
};

#endif
