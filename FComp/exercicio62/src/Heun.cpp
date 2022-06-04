#include "Heun.h"

using namespace std;

double ODE (double t, double y)
{
  return t * t;
}

double Heun (double t, double y, double h, double (*f) (double, double))
{
  return y + (h / 2.) * ( (*f)(t, y) + (*f) (t + h, y + h * (*f)(t, y) ) );
}
