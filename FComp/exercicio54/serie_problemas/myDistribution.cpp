#include <iostream>
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TRandom3.h"
#include <cmath>
#include "../src/ExpFunct.h"

using namespace std;

int main()
{
  double ga = 0.2;
  //gStyle->SetOptStat(1);
  TCanvas *c = new TCanvas("c", "exponential distribution",0,0,500,500);

  int Nbins=100;
  int Ntrials=100000;
  int b = 100;

  TH1D * h1 = new TH1D("h1", "exponential distribution", Nbins, 0.,b);
  TH1D * h2 = new TH1D("h2", "exponential distribution", Nbins, 0.,b);

  TRandom3 rgen(0);

  TF1 * f = new TF1("Exponential","[0]*exp((-1)*[0]*x)", 0, b);
  f->SetParameter(0, ga);

  for (int i=0;i<Ntrials;i++)
  {
    h1->Fill(ExpFunctgen(ga));
    h2->Fill(f->GetRandom());
  }

  h2->SetLineWidth(2);
  h2->SetLineColor(2);
  h2->Draw();


  h1->SetLineWidth(2);
  h1->SetLineColor(9);
  h1->Draw("SAME");

  TLegend * legend = new TLegend(0.5,0.5,0.8,0.65);
  legend->AddEntry(h1,"ExpFunct.cpp","l");
  legend->AddEntry(h2,"TF1::GetRandom()","l");
  legend->Draw();

  c->Modified();
  c->SaveAs("ExpHistogram.eps");

  return 0;
}
