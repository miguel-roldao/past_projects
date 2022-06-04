#include "Integrator.h"
#include "Derivator.h"
#include <cmath>

using namespace std;

Integrator::Integrator(double xbeg, double xend, TF1* func)
{
  x0 = xbeg;
  x1 = xend;
  F = func;
}

void Integrator::SetBoundaries(double x_0,double x_1)
{
  x0 = x_0;
  x1 = x_1;
}

void Integrator::TrapezoidalRule(int n, double& result, double& error)
{
  Derivator Aux(F);
  double h = (x1 - x0) / ((double)n);
  result = 0;
  error = 0;
  double deriv2_max = 0;
  for(int i = 0; i < n; i++)
  {
    result += (Evaluate(x0 + i*h) + Evaluate(x0 + (i+1) * h)) * h * 0.5;
  //  cout << result << endl;
  }
//  cout<< "h = " << Aux.Deriv_1(x0,5e-3) << endl;
  error = fabs(h*h/12 * (Aux.Deriv_1(x1,5e-3) - Aux.Deriv_1(x0,5e-3)));
  //cout<< error << "O erro não está certo (TrapezoidalRule)..." << endl;
}

void Integrator::SimpsonRule(int n, double& result, double& error)
{
//  cout << __PRETTY_FUNCTION__ << endl;
  Derivator Aux(F);
  double h = (x1 - x0) / ((double)n);
  result = 0;
  error = 0;
  double deriv4_max = 0;

  //if(n % 2  == 1)
  /*
0.0   0.5   1.0   1.5   2.0
  */

    for (int i = 0; i < n ; i ++)
    {
      result += h/6 * (Evaluate(x0 + i*h) + 4 * Evaluate(x0 + i*h + 0.5*h) + Evaluate(x0 + (i+1)*h));
    //  cout << x0+i*h << " - " << x0 + i*h + 0.5*h << " - " << x0 + (i+1)*h << endl;
    //  cout << "it- " << i << "result: " << result << endl;
    }
    //cout << h << " ---- " << Aux.Deriv_3(x1,5e-3) << " ---- " <<Aux.Deriv_3(x0,5e-3) << endl;
    error = fabs(h*h*h*h/180 * (Aux.Deriv_3(x1,5e-3) - Aux.Deriv_3(x0,5e-3))/16);

}
