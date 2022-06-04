#include <iostream>
#include <cmath>
#include "RootFinder.h"
#define PI atan(1)*4
#define EPS0 8.854e-12
#define R0 0.33e-10
#define EL 1.602e-19
#define POTENT0 1.744e-16

using namespace std;

double dV_dr(double r)
{
  return (EL*EL /(4* PI * EPS0 * r * r) - POTENT0/R0 * exp(-r /(R0)));
}

int main()
{

  double epsilon0 = 8.854e-12;
  double r0 = 0.33e-10;
  double e = 1.602e-19;
  double V0 = 1.744e-16;

/*
Potencial:
V(r) = -e^2/(4*PI*epsilon0*r) + POTENT0*exp(-r/r0)

dV/dr = e^2/4*PI*epsilon0*r*r) - POTENT0/r0 *exp(-r/r0)

*/

  double root_bissection = Bissection(2*R0, 1e-3, &dV_dr, 1e-9);

  cout << "(bissecao)\n comprimento de ligação = " << root_bissection << " m \n";

  cout << "f(root)" << dV_dr(root_bissection) << "\n";

  return 0;
}
