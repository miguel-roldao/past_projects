#include <iostream>
#include "IntegratorMC.h"
#include "TRandom3.h"
#include "TF1.h"
#include "TFormula.h"

using namespace std;

IntegratorMC::IntegratorMC(TF1* f, int M)
{
  F = new TF1();
  F = f;
  TF = new TFormula();
  Ndim = M;
  a = new double[Ndim];
  b = new double[Ndim];

  if (M != 1)
    cout << "Use uma TFormula, em vez de uma TF1, para calcular integrais multidimensionais!" << endl;
}

IntegratorMC::IntegratorMC(double* xbeg, double* xend, TF1* f, TFormula* tf, int M)
{
  F = new TF1();
  F = f;
  TF = new TFormula();
  TF = tf;
  Ndim = M;
  a = new double[Ndim];
  b = new double[Ndim];

  for (int i = 0; i < Ndim; i++)
  {
    a[i] = xbeg[i];
    b[i] = xend[i];
  }

}

IntegratorMC::IntegratorMC(double* xbeg, double* xend, TFormula* tf, int M)
{
  F = new TF1();
  TF = new TFormula();
  TF = tf;
  Ndim = M;
  a = new double[Ndim];
  b = new double[Ndim];

  for (int i = 0; i < Ndim; i++)
  {
    a[i] = xbeg[i];
    b[i] = xend[i];
  }
}

IntegratorMC::~IntegratorMC()
{
  delete[] a;
  delete[] b;
}

IntegratorMC::IntegratorMC(const IntegratorMC& MC)
{
  Ndim = MC.Ndim;
  a = MC.a;
  b = MC.b;
  *F = *(MC.F);
}

void IntegratorMC::SetBoundaries(double *xbeg, double* xend)
{
  for (int i = 0; i < Ndim; i++)
  {
    a[i] = xbeg[i];
    b[i] = xend[i];
  }
}
void IntegratorMC::SetFormula(TFormula *tf)
{
  TF = tf;
}

void IntegratorMC::UniformRandom(int NSamples, double &Integral, double &Error)
{
  TRandom3 rgen(0); // garante que a semente é única
  Integral = 0;
  Error = 0;

  double *x = new double[Ndim];
  double Integral_Squared = 0;
  double func = 0.;
  bool IsTFormulaDefined = false;

  if (TF != NULL)
    IsTFormulaDefined = true;

  for (int i = 0; i < NSamples; i++)
  {
    for (int j = 0; j < Ndim; j++)
      x[j] = a[j] + rgen.Uniform() * ( b[j] - a[j] );

    if (!IsTFormulaDefined)
      func = F->EvalPar(x);

    else
      func = TF->EvalPar(x);

    Integral += func;
    Integral_Squared += func * func;
  }

  Error = sqrt(-((Integral/NSamples)*(Integral/NSamples)-(Integral_Squared/NSamples) ) / NSamples);

  for (int k = 0; k < Ndim; k++)
  {
    Error    *= (b[k] - a[k]);
    Integral *= (b[k] - a[k]);
  }

  Integral /= NSamples;

  delete[] x;
}

void IntegratorMC::ImportanceSampling(int NSamples, double& Integral, double& Error, TF1* p, TF1* xofy)
{
  TRandom3 rgen(0); // garante que a semente é única
  Integral = 0;
  Error = 0;
  double Integral_Squared = 0;
  double func = 0;
  double *x = new double[Ndim];
  double pdf = 0;
  bool IsTFormulaDefined = false;

  if (TF != NULL)
    IsTFormulaDefined = true;

  for (int i = 0; i < NSamples; i++)
    {
      for (int j = 0; j < Ndim; j++)
        x[j] = a[j] + rgen.Uniform() * ( b[j] - a[j] );

        if (!IsTFormulaDefined)
          func = F->Eval(xofy->EvalPar(x));

        else
          func = TF->Eval(xofy->EvalPar(x));

      pdf  = p->Eval(xofy->EvalPar(x));
      Integral += (func/pdf);
      Integral_Squared += (func/pdf)*(func/pdf);
    }

    Error = sqrt(-((Integral/NSamples)*(Integral/NSamples)-(Integral_Squared/NSamples) ) / NSamples);

    for (int k = 0; k < Ndim; k++)
    {
      Error *= (b[k] - a[k]);
      Integral *= (b[k] - a[k]);
    }

    Integral /= NSamples;
    delete[] x;
}

void IntegratorMC::AcceptanceRejection(int NSamples, double& result, double& error)
{
  result = 0;
  error = 0;
  TRandom* rand = new TRandom(0);
  double rand1 = 0;
  double rand2 = 0;
  double eval;
  double area;

  if(Ndim == 1 && F != NULL)
  {
    double x1 = b[0];
    double x0 = a[0];
    double max = F->GetMaximum(x0,x1);
    double min = F->GetMinimum(x0,x1);

    if(min <= 0)
    {
      double h = max - min;
      int ratio = 0;

      for(int i = 0; i < NSamples; i++)
      {
        rand1 = rand->Uniform();
        rand2 = rand->Uniform();
        eval = x0 + (x1-x0)*rand1;

        if(rand2 * h <= (F->Eval(eval) - min))
          ratio++;
      }

      area = h * (x1-x0);
      error = (area/NSamples)*sqrt(ratio*(1-(ratio/NSamples)));
      result = area*ratio/NSamples + (min * (x1-x0));
    }

    else
    {
      double h = max;
      int ratio = 0;

      for(int i = 0; i < NSamples; i++)
      {
        rand1 = rand->Uniform();
        rand2 = rand->Uniform();
        eval = x0 + (x1-x0)*rand1;

        if(rand2 * h <= (F->Eval(eval)))
          ratio++;
      }

      area = h * (x1-x0);
      error = (area/((double)NSamples))*sqrt(ratio*(1-(ratio/((double)NSamples))));
      result = area*ratio/((double)NSamples);
    }
  }

  else
  {
    if(Ndim > 1)
      cout << "\n**AcceptanceRejection only defined for 1 dimension**\n";

    if(F == NULL)
      cout << "\n**AcceptanceRejection needs a TF1**\n";
  }
}
