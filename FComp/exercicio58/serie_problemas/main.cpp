#include <iostream>
#include <cmath>
#include <iomanip>
#include "TF1.h"
#include "Integrator.h"
#include "IntegratorMC.h"
#define PI atan(1) * 4

using namespace std;

int main ()
{
  int n = 1000;
  double xmin = 0.2 * PI;
  double xmax = 0.5 * PI;
  double result_holder = 0;
  double error_holder = 0;
  double xxmin[] = {xmin};
  double xxmax[] = {xmax};


  TF1 *f1 = new TF1("f1","cos(x)", xmin, xmax);
  double maxf = f1->GetMaximum(xmin,xmax);

  Integrator I(xmin, xmax, f1);
  I.TrapezoidalRule(n, result_holder, error_holder);
  cout << "(Método Trapezoidal) I = " << result_holder << "    erro = " << error_holder << "\n";

  I.SimpsonRule(n*100, result_holder, error_holder);
  cout << "(Método Simpson) I = " << result_holder << "    erro = " << error_holder << "\n";

  IntegratorMC M(xxmin, xxmax, f1, NULL);

  M.UniformRandom(n, result_holder, error_holder);
  cout << "(Método UniformRandom) I = " << result_holder << "    erro = " << error_holder << "\n";

  M.AcceptanceRejection(n*100, result_holder, error_holder);
  cout << "(Método AcceptanceRejection) I = " << result_holder << "    erro = " << error_holder << "\n";

  return 0;

}
