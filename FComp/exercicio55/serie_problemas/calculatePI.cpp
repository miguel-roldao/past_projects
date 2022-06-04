#include <iostream>
#include <cmath>
#include <iomanip>
#include "TF1.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TRandom3.h"

using namespace std;

int main()
{
  TCanvas *c = new TCanvas("c", "exponential distribution",0,0,600,700);
  c->Divide(2,0);
  int N = 1000;
  int nexp = 10000;
  int Nbins = 100;
  double it, er;

  TRandom3 r1(0);
  //TRandom3 r2(0);

  int count;
  TH1D * h1 = new TH1D("h1", "PI", Nbins, 2.5,4.);
  TH1D * h2 = new TH1D("h2", "error", Nbins, 0.,0.03);

  for(int i = 0; i < nexp; i++)
  {
    count = 0;
    for (int j = 0; j < N; j++)
    {
      if (sqrt(pow(r1.Uniform(0,1), 2) + pow(r1.Uniform(0,1), 2)) < 1)
        count++;
    }
    it = ((double)count) / ((double)N);
    h1->Fill(4 * it);
    er = 1/((double)N) * sqrt(count*(1 - it));
    h2->Fill(er);
  }
  c->cd(1);
  h1->SetLineWidth(2);
  h1->SetLineColor(9);
  h1->Draw();
  c->cd(2);
  h2->SetLineWidth(2);
  h2->SetLineColor(4);
  h2->Draw();

  cout << "\nPi (" << N << ")= " << setprecision(7) << h1->GetMean() << "; STD Deviation = " << h1->GetRMS() << endl;

  c->Modified();
  c->SaveAs("Pie4.eps");

  h1->Reset();
  h2->Reset();

  N = 10000;

  for(int i = 0; i < nexp; i++)
  {
    count = 0;
    for (int j = 0; j < N; j++)
    {
      if (sqrt(pow(r1.Uniform(0,1), 2) + pow(r1.Uniform(0,1), 2)) < 1)
        count++;
    }

    it = ((double)count) / ((double)N);
    h1->Fill(4 * it);
    h2->Fill(1/((double)N) * sqrt(count * (1-it)));
  }
  c->cd(1);
  h1->SetLineWidth(2);
  h1->SetLineColor(9);
  h1->Draw();
  c->cd(2);
  h2->SetLineWidth(2);
  h2->SetLineColor(4);
  h2->Draw();

  cout << "\nPi (" << N << ")= " << setprecision(7) << h1->GetMean() << "; STD Deviation = " << h1->GetRMS() << endl;

  c->Modified();
  c->SaveAs("Pie5.eps");


  h1->Reset();
  h2->Reset();

  N = 100000;

  for(int i = 0; i < nexp; i++)
  {
    count = 0;

    for (int j = 0; j < N; j++)
    {
      if (sqrt(pow(r1.Uniform(0,1), 2) + pow(r1.Uniform(0,1), 2)) < 1)
        count++;
    }
    it = ((double)count) / ((double)N);
    h1->Fill(4 * it);
    h2->Fill(1/((double)N) * sqrt(count * (1-it)));
  }

  c->cd(1);
  h1->SetLineWidth(2);
  h1->SetLineColor(9);
  h1->Draw();
  c->cd(2);
  h2->SetLineWidth(2);
  h2->SetLineColor(4);
  h2->Draw();

  cout << "\nPi (" << N << ")= " << setprecision(7) << h1->GetMean() << "; STD Deviation = " << h1->GetRMS() << endl;

  c->Modified();
  c->SaveAs("Pie6.eps");

  return 0;
}
