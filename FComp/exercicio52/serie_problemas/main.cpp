#include <iostream>
#include <cmath>
#include <iomanip>
#include "../src/RootFinder.h"

using namespace std;

#define M_EARTH 5.972E24
#define M_MOON  7.348E22
#define G  6.674E-11
//#define W  1.022E3
#define W 0.00000266169
#define R  384.4E9
#define R_EARTH 6.371E6
#define R_MOON 1.371E6

double LagrangePoint(double r)
{
  return (G*M_EARTH)/(r*r) - (G*M_MOON)/((R-r)*(R-r)) - W*W*r;
}

double DLagrangePoint(double r)
{
  return (-2*G*M_EARTH)/(r*r*r) + (-2*G*M_MOON)/((R-r)*(R-r)*(R-r)) - W*W;
}

int main ()
{
  cout << "Método da Bissecção: r = " << Bissection(R_EARTH, R/2, &LagrangePoint, 1e-5) << " m" << endl;
  cout << "Método Regula Falsi: r = " << RegulaFalsi(R_EARTH, R/2, &LagrangePoint, 100000) << " m" << endl;
  cout << "Método de Newton Rhapson: r = " << NewtonRaphson(Bissection(R_EARTH, R/2, &LagrangePoint, 1e-1), &LagrangePoint, &DLagrangePoint, 1e-5) << " m" << endl;
  cout << "Método da Secante: r = " <<  Secant(R_EARTH, R/2, &LagrangePoint, 1e-3) << " m" << endl;
  return 0;
}
