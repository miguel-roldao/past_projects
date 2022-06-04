#ifndef H_INTEGRATORMC_H
#define H_INTEGRATORMC_H
#include "Integrator.h"
using namespace std;

class IntegratorMC: public Integrator
{
  public:
    IntegratorMC(TF1* f=NULL, int M=1);
    IntegratorMC(double* xbeg, double* xend, TF1* f = NULL, TFormula* tf = NULL, int M = 1);
    IntegratorMC(double* xbeg, double* xend, TFormula* tf = NULL, int M = 1);
    IntegratorMC(const IntegratorMC&);
    ~IntegratorMC();
    void SetBoundaries(double *xbeg, double* xend);
    void SetFormula(TFormula *tf);
    void UniformRandom (int NSamples, double& Integral, double& Error);
    void ImportanceSampling(int NSamples, double& Integral, double& Error, TF1* p, TF1* xofy);
    void AcceptanceRejection(int n, double& result, double& error);

  private:
    int Ndim;
    TF1* F;
    TFormula* TF;
    double * a;
    double * b;
};

#endif
