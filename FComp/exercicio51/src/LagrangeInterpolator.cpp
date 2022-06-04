#include <iostream>
#include <cstdio>
#include <string>
#include "LagrangeInterpolator.h"
#include "TGraph.h"
#include "TF1.h"
#include "TStyle.h"

using namespace std;

LagrangeInterpolator::LagrangeInterpolator(int fN, double *fx, double *fy, TF1* fF0) : DataPoints(fN, fx, fy)
{
  DataPoints::Print();
  F0 = fF0;
  FInterpolator = new TF1("FInterpolator", this, &LagrangeInterpolator::fInterpolator, x[0]-0.001 ,x[N-1]+0.001, 0);
}

LagrangeInterpolator::~LagrangeInterpolator()
{
  delete FInterpolator;
  delete F0;
}

double LagrangeInterpolator::Interpolate (double xaux)
{
  double result = 0;

  for (int i = 0; i < N; i++)
  {
    double term = y[i];

    for (int j = 0; j < N; j++)
    {
        if (j != i)
            term *= (xaux - x[j]) / (x[i] - x[j]);
    }

    // Add current term to result
    result += term;
  }

  return result;
}

void LagrangeInterpolator::Draw() {

  if (Nplots == 0)
  {
    //create application
    TApplication * MyRootApp;
    MyRootApp = new TApplication("Just an example...", NULL, NULL);
    MyRootApp->SetReturnFromRun(true);
  }

  TCanvas *c2 = new TCanvas("c1","c1",600,500);

  gPad->Clear();
  gStyle->SetLabelSize(0.06,"X");
  gStyle->SetLabelSize(0.06,"Y");
  TGraph *g = new TGraph(N,x,y);
  g->SetMarkerStyle(20);
  g->SetMarkerColor(kGreen);
  g->SetMarkerSize(2.5);

	FInterpolator->SetLineColor(kRed);
	FInterpolator->SetLineWidth(4);
	FInterpolator->SetTitle("Lagrange");

  if (F0 != NULL) {
    F0->SetLineColor(kBlue);
    F0->SetLineWidth(4);
    F0->SetLineStyle(2);
  }

  gPad->DrawFrame(FInterpolator->GetXmin(), FInterpolator->GetMinimum(),
                  FInterpolator->GetXmax(), FInterpolator->GetMaximum(), FInterpolator->GetTitle());
  g->Draw("PSAME");
  FInterpolator->Draw("SAME");

  if (F0 != NULL)
    F0->Draw("SAME");

  c2->Update();
  c2->SaveAs("plot_Lagrange.eps");
  gPad->WaitPrimitive();
  // delete MyRootApp;
  delete g;
  delete c2;
  Nplots++;
}


void LagrangeInterpolator::SetFunction(TF1* function)
{
  F0 = function;
}
