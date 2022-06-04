#include <iostream>
#include <vector>
#include "TF1.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "../src/Euler.h"
#include "TFormula.h"

using namespace std;

double EXAMPLE_T2(double t, double x)
{
  return t*t;
}

int main()
{
  double dt = 0.1;
  double x0 = 2.0;
  double tmin = 0;
  double tmax = 4;
  double (*f)(double,double);
  f = &EXAMPLE_T2;
  vector<double> sol = Euler(x0,tmin,tmax, f, dt);
  int i = 0;

  for (double t = tmin; t <= tmax + dt; t += dt)
  {
    cout << "f(" << t << ") = "<< sol.at(i) << endl;
    i++;
  }

  double* y = new double[sol.size()];
  double* x = new double[sol.size()];

  for(int j = 0; j < sol.size(); j++)
  {
    x[j] = j * dt;
    y[j] = sol.at(j);
  }

  TCanvas *c = new TCanvas("c", "exercicio60", 0, 0, 500, 500);
  TF1 *analytical = new TF1("analytical","(x*x*x)/3. + 2", tmin, tmax);

  TGraph* numerical = new TGraph(sol.size(), x, y);
  numerical->SetMarkerStyle(8);
  numerical->SetMarkerColor(2);
  numerical->SetTitle("");
  numerical->GetXaxis()->SetTitle("t");
  numerical->GetYaxis()->SetTitle("y");
  numerical->Draw("AP");

  analytical->SetLineWidth(2);
  analytical->SetLineColor(1);
  analytical->Draw("LSAME");


  c->Modified();


  c->Modified();
  c->SaveAs("Euler.eps");

  double* z = new double[3];
  z[0] = 1;
  z[1] = 1;
  z[2] = 0; //x[2]
  z[3] = 0;

  TFormula* form = new TFormula("form","[0] + x[3] + x[0] * x[1] * x[2]");
  form->SetParameter(0,2);
  cout << "form em (1,2,3,4) = " << form->EvalPar(z) << endl;
  form->Print();

  delete analytical;
  delete[] x;
  delete[] y;

  return 0;
}
