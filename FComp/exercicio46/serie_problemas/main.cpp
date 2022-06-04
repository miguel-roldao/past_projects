#include <iostream>
#include "../src/DataPoints.h"
#include "../src/LagrangeInterpolator.h"
#include "../src/NevilleInterpolator.h"
#include "../src/Spline3Interpolator.h"

using namespace std;

int main()
{
  int n = 3;
//  double h = 0.1;
  double* x = new double[n];
  double* y = new double[n];

/*
for(int i = 0; i < n; i++)
{
  x[i] = i*h;
  y[i] = cos(x[i]);
}*/

  x[0] = -1.2;
  x[1] = 0.3;
  x[2] = 1.1;
  y[0] = -5.76;
  y[1] = -5.61;
  y[2] = -3.69;
  // a) Neville

  NevilleInterpolator Nev = NevilleInterpolator(n, x, y);
  Nev.Draw();

  // b) Lagrange

  LagrangeInterpolator Lag = LagrangeInterpolator(n, x, y);
  Lag.Draw();

  Spline3Interpolator Spl(n, x, y);
  Spl.Draw();

/*  TCanvas *c = new TCanvas("some", "thing", 0, 0, 500, 500);
  TF1* D = Spl.GetDeriv1InterpolFunction();

  D->SetLineColor(kBlue);
  D->SetLineWidth(4);
  //F->SetTitle("Plot");

  D->Draw("L");
  c->Update();
  c->SaveAs("func1D.eps");*/

  return 0;
}
