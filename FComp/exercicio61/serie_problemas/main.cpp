#include <iostream>
#include "../src/Heun.h"
#include "TF1.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"

using namespace std;

int main ()
{
  int i = 0;
  int N = 40;
  double t = 0;
  double y = 2.;
  double h = 0.1;
  double *yarray = new double[N];
  double *tarray = new double[N];

  while (t <= 4)
  {
    // cout << Heun(t, y, h, &ODE) << endl;
    yarray[i] = y;
    tarray[i] = t;
    y = Heun(t, y, h, &ODE);
    t += h;
    i++;
  }

  TCanvas *c = new TCanvas("c", "Exercicio 61", 0, 0, 500, 500);
  TF1 *analytical = new TF1("analytical","(x*x*x)/3. + 2", 0, 4);

  TGraph* numerical = new TGraph(N, tarray, yarray);
  numerical->SetMarkerStyle(8);
  numerical->SetMarkerColor(kBlue);
  numerical->SetTitle("");
  numerical->GetXaxis()->SetTitle("t");
  numerical->GetYaxis()->SetTitle("y");
  numerical->Draw("AP");

  analytical->SetLineWidth(2);
  analytical->SetLineColor(kRed);
  analytical->Draw("LSAME");

  c->Modified();

  c->Modified();
  c->SaveAs("Heun.eps");

  delete analytical;
  delete[] yarray;
  delete[] tarray;


  return 0;
}
