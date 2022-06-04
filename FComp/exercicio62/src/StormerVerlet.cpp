#include "StormerVerlet.h"

using namespace std;

/* double ODE (double t, double y)
{
  return t * t;
} */

double StormerVerlet (double t, double y, double y1, double h, double (*f) (double, double))
{
  return y1 + 2 * h * (*f)(t, y);
}
