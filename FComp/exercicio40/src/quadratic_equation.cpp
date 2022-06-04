#include <iostream>
#include <cmath>
#include <iomanip>
#include "quadratic_equation.h"

using namespace std;

double * quadratic::solve()
{
  double * result = new double[2];
  result[0] = ((- b + sqrt(b*b-4*a*c))/(2*a));
  result[1] = ((- b - sqrt(b*b-4*a*c))/(2*a));

  return result;

}

double * quadratic::solve_case()
{
  double * result_case = new double[2];

  if (b*b > c && a == 1)
    {

      if (b > 0)
        {
          result_case[0] = - b + sqrt(b*b - solve()[0]* solve()[1]);
          result_case[1] = c/result_case[0];
        }

      if (b < 0)
          {
            result_case[0] = - b - sqrt(b*b - solve()[0]* solve()[1]);
            result_case[1] = c/result_case[0];
          }
    }

  else
  {
    cout << "A equação que introduziu não é da forma x^2 - 2bx + c = 0" << endl;
  }

  return result_case;
}
