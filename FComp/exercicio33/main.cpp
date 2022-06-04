#include <iostream>
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TStyle.h"
using namespace std;

int main()
{
  gStyle->SetOptTitle(0); //no title
  TCanvas *c = new TCanvas("c", "my canvas", 0, 0, 500, 500);

  TH1F *h = new TH1F("h", "histogram",100, 0, 5);
  TF1 *f1 = new TF1("f1","[0] +[1]*x +gaus(2)", 0, 5); //funcao geradora
  f1->SetParameters(6,-1,5,3,0.2);
  for(int i = 0; i < 4000; i++)
  {
    h->Fill(f1->GetRandom());
  }
  delete f1;
  f1 = new TF1("fline","[0] + [1]*x", 0, 5);

  h->SetLineWidth(2);
  h->SetLineColor(9);
  h->Draw();

  h->GetXaxis()->SetRangeUser(0.,5.);
  h->Fit("fline", "0");   // second parameter == "0" :: do not draw fit
  TF1 *fg = h->GetFunction("fline");

  TF1 * p1[2] = {new TF1("fline1","[0] + [1]*x", 0, 2.5), new TF1("fline2","[0] + [1]*x", 3.5, 5)};

  p1[0]->SetParameters(f1->GetParameters());
  p1[0]->SetLineWidth(3);
  p1[0]->SetLineColor(6);
  p1[0]->SetLineStyle(9);
  p1[1]->SetParameters(f1->GetParameters());
  p1[1]->SetLineWidth(3);
  p1[1]->SetLineColor(6);
  p1[1]->SetLineStyle(9);


  //p1[0]->Draw();
  h->GetListOfFunctions()->Add(p1[0]);
  h->GetListOfFunctions()->Add(p1[1]);

  c->Modified();
  c->SaveAs("exercicio33.eps");
  return 0;
}
