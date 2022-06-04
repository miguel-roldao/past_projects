#include <iostream>
#include <vector>
#include "Euler.h"

using namespace std;

vector<double> Euler (double x0, double tmin, double tmax, double (*f) (double,double), double dt)
{
  vector<double> sol;
  double dx;
  sol.push_back(x0);

  for (double t = tmin; t <= tmax; t += dt)
  {
    dx = dt * f(t, x0);
    x0 += dx;
    sol.push_back(x0);
  }

  return sol;
}
