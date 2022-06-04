#include <iostream>
#include <cmath>
#include <iomanip>
#include "Integrator.h"
#include "FCenas.h"
#include "IntegratorMC.h"
#define PI atan(1)*4
#define GRAUS * PI / 180

using namespace std;

int main()
{
  double teta = 10*PI/180;
  double L = 1;
  double g = 9.8;
  double a = 0;
  double b = PI/2;
  double integral, error;
  double aa[] = {a};
  double bb[] = {b};


    TCanvas* c = new TCanvas("c1", "pendulo", 0, 0, 500, 500);

  TF1* F1 = new TF1("f1", "1/sqrt(1-((sin([0])*sin([0]))*sin(x)*sin(x)))", 0, PI/2);
  F1->SetParameter(0,teta/2);

  F1->SetLineWidth(5);
  F1->SetLineColor(1);
  F1->Draw("L");

  c->Modified();
  c->SaveAs("f.pdf");

  Integrator I(a, b, F1);
  I.SimpsonRule(10, integral, error);

  double result = 4 * sqrt(L/g) * integral;
  cout << setprecision(10) << "(SimpsonRule) T(10) = " << result << " +/- " << 4. * sqrt(L/g) * error << "\n";

  I.TrapezoidalRule(10, integral, error);

  result = 4 * sqrt(L/g) * integral;
  cout << setprecision(10) << "(TrapezoidalRule) T(10) = " << result << " +/- " << 4. * sqrt(L/g) * error << "\n";

  IntegratorMC M(aa, bb, F1);

  M.UniformRandom(1000, result, error);

  result = 4 * sqrt(L/g) * integral;
  cout << setprecision(10) << "(Monte Carlo) T(10) = " << result << " +/- " << 4. * sqrt(L/g) * error << "\n";

  M.AcceptanceRejection(1000, result, error);

  result = 4 * sqrt(L/g) * integral;
  cout << setprecision(10) << "(Monte Carlo_AR) T(10) = " << result << " +/- " << 4. * sqrt(L/g) * error << "\n";



  return 0;
}
