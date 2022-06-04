#include <iostream>
#include "DataPoints.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "NevilleInterpolator.h"
#include "TGraph.h"
#include "TF1.h"
#include "TStyle.h"
#include <cstdio>
#include <string>

using namespace std;

NevilleInterpolator::NevilleInterpolator(int fN, double *fx, double *fy, TF1* fF0) : DataPoints(fN, fx, fy)
{
  DataPoints::Print();
  F0 = fF0;
  FInterpolator = new TF1("FInterpolator", this, &NevilleInterpolator::fInterpolator, x[0]-0.001 ,x[N-1]+0.001, 0);
}

double NevilleInterpolator::Interpolate (double xaux)
{
  double* yaux = new double[N];

  for (int i=0; i < N; i++)
    yaux[i] = y[i]; // auxiliar vector

  for (int k = 1; k < N; k++)
  {
    for (int i = 0; i < N-k; i++)
    {
      yaux[i] = ( (xaux-x[i+k])*yaux[i] - (xaux-x[i])*yaux[i+1]) / (x[i]-x[i+k]);
    }
  }

  double A = yaux[0];
  delete [] yaux;
  return A;
}

void NevilleInterpolator::Draw()
{
  if (Nplots == 0)
  {
    //create application
    TApplication * MyRootApp;
    MyRootApp = new TApplication("Drawing Nevile...", NULL, NULL);
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
	FInterpolator->SetTitle("Neville");

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
  c2->SaveAs("plot_Neville.eps");
  gPad->WaitPrimitive();
  // delete MyRootApp;
  delete g;
  delete c2;
  Nplots++;
}

void NevilleInterpolator::SetFunction(TF1* function)
{
  F0 = function;
}
