#include <iostream>
#include <cmath>
#include <iomanip>
#include "TF1.h"
#include "TF2.h"
#include "Integrator.h"
#include "IntegratorMC.h"

using namespace std;

int main ()
{
  int n = 1000;
  double xmin = 0;
  double xmax = 1;
  double result_holder = 0;
  double error_holder = 0;
  double *xxmin = new double[2];
  double *xxmax = new double[2];

  for (int i = 0; i < 2; i++)
  {
    xxmin[i] = xmin;
    xxmax[i] = xmax;
  }


  TF1 *f1 = new TF1("f1","1/(1 + x*x)", xmin, xmax);

  TFormula *f2 = new TFormula("f2", "(x+y)/(x * x + y * y)");

  cout << "\nf(x) = 1/(1+x^2): \n";

  Integrator I(xmin, xmax, f1);
  I.TrapezoidalRule(n, result_holder, error_holder);
  cout << "(Método Trapezoidal) I = " << result_holder << "    erro = " << error_holder << "\n";

  I.SimpsonRule(n*100, result_holder, error_holder);
  cout << "(Método Simpson) I = " << result_holder << "    erro = " << error_holder << "\n";

  IntegratorMC M(xxmin, xxmax, f1);

  M.UniformRandom(n, result_holder, error_holder);
  cout << "(Método UniformRandom) I = " << result_holder << "    erro = " << error_holder << "\n";

  M.AcceptanceRejection(n*100, result_holder, error_holder);
  cout << "(Método AcceptanceRejection) I = " << result_holder << "    erro = " << error_holder << "\n";

  cout << "\nf(x) = (x+y)/(x^2+y^2): \n";

  IntegratorMC M2(xxmin, xxmax, NULL, f2, 2);

  M2.UniformRandom(n*10000,result_holder, error_holder);
  cout << "(Método UniformRandom) I = " << result_holder << "    erro = " << error_holder << "\n";

  return 0;

}
