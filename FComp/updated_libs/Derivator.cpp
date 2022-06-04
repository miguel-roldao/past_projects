#include "Derivator.h"

using namespace std;

Derivator::Derivator(TF1 *f) : Func1D(f) {}

double Derivator::Deriv_1(double x, double h, int type)
{
  switch (type)
  {
    case 0: // Central
      return ( (Evaluate(x+h) - Evaluate(x-h)) / (2*h) );
      break;

    case 1: // Forward
      return ( (Evaluate(x+h) - Evaluate(x)) / h);
      break;

    case 2: // Backward
      return ( (Evaluate(x) - Evaluate (x-h) ) / h);
      break;

    default: // Central
      return ( (Evaluate(x+h) - Evaluate(x-h)) / (2*h) );
  }
}

double Derivator::Deriv_2(double x, double h, int type)
{
  switch (type)
  {
    case 0:
      return ( (Evaluate (x+h) - 2 * Evaluate(x) + Evaluate(x-h)) / (h*h) );
      break;

    case 1:
      return ( (Evaluate(x + 2 * h) - 2 * Evaluate(x + h) + Evaluate(x)) / (h*h) );
      break;

    case 2:
      return ( (Evaluate(x) - 2 * Evaluate(x - h) + Evaluate (x - 2 * h) ) / (h*h) );
      break;

    default:
      return ( (Evaluate (x+h) - 2 * Evaluate(x) + Evaluate(x-h)) / (h*h) );
  }
}


double Derivator::Deriv_3(double x, double h, int type)
{
  switch (type)
  {
    case 0:
      return ( (- Evaluate (x - 2 * h) + 2 * Evaluate(x - h) - 2 * Evaluate(x + h) + Evaluate (x + 2*h)) / (2 * (h*h*h) ) );
      break;

    case 1:
      return ( (- Evaluate (x) + 3 * Evaluate(x+h) - 3 * Evaluate (x + 2*h) + Evaluate(x + 3 * h) ) / (h*h*h) );
      break;

    case 2:
      return ( (- Evaluate (x) + 3 * Evaluate(x-h) - 3 * Evaluate (x - 2*h) + Evaluate(x - 3 * h) ) / (h*h*h) );
      break;

    default:
      return ( (- Evaluate (x - 2 * h) + 2 * Evaluate(x - h) - 2 * Evaluate(x + h) + Evaluate (x + 2*h)) / (2 * (h*h*h) ) );
  }
}

double Derivator::Deriv_4(double x, double h, int type)
{
  switch (type)
  {
    case 0:
      return ( (Evaluate (x - 2 * h) - 4 * Evaluate(x - h) + 6 * Evaluate(x) - 4 * Evaluate(x + h) + Evaluate (x + 2*h)) / ((h*h*h*h) ) );
      break;

    case 1:
      return ( (Evaluate (x) - 4 * Evaluate(x + h) + 6 * Evaluate(x + 2 * h) - 4 * Evaluate(x + 3 * h) + Evaluate (x + 4 * h)) / ((h*h*h*h) ) );
      break;

    case 2:
        return ( (Evaluate (x) - 4 * Evaluate(x - h) + 6 * Evaluate(x - 2 * h) - 4 * Evaluate(x - 3 * h) + Evaluate (x - 4 * h)) / ((h*h*h*h) ) );
      break;

    default:
      return ( (Evaluate (x - 2 * h) - 4 * Evaluate(x - h) + 6 * Evaluate(x) - 4 * Evaluate(x + h) + Evaluate (x + 2*h)) / ((h*h*h*h) ) );
  }
}
