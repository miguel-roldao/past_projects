#include <iostream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TPaletteAxis.h"
#include "vec.h"
#include "FCtools.h"

using namespace std;

int main()
{
  int n = 50;

  double A = 21.1;
  double B = 5.85;
  double C = 1.18;
  double x;

  double vx[100];
  double vy[100];

  /*for (int i = 1; i < n; i++)
  {
    x = i * 0.025;
    vx[i] = x;
    vy[i] = A*pow(x,-2.8)/(1+B*pow(x,-1.22)+C*pow(x,-2.54));
  //  cout<<vx[i]<<" ";
  //  cout<<vy[i]<<endl;
}*/

  TCanvas* c = new TCanvas("c", "my canvas", 500, 500);
  gStyle->SetOptStat(0);
  //auto legend = new TLegend(0.7,0.1,0.9,0.25);
  //legend->SetHeader("Legenda","C");

//  TGraph *g1 = new TGraph(n, vx, vy);
  TMultiGraph *mg = new TMultiGraph();


  /*mg->Add(g1);
  g1->SetTitle("F(E)"); g1->SetLineWidth(3); g1->SetLineColor(2);
  g1->GetHistogram()->SetMinimum(0);*/
//  gPad->SetLogy();


  double* p = new double[400];


  for(int i = 0; i < 400; i++)
  {
    x = 0.1 + 0.05 * i;
    p[i] = A*pow(x,-2.8)/(1+B*pow(x,-1.22)+C*pow(x,-2.54));
  }

  Vec E(400,p);

  delete[] p;
//  E.Print();

  FCtools cools;

  vector<Vec> M = cools.ReadFile2Vec("MatrizTransferencia.dat");

  double dE = 0.05;
  double sum = 0;

  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < 400; j++)
    {
      sum += M.at(i)[j] * E[j];
    }
    vx[i] = i * dE;
    vy[i] = sum * dE;
  //  cout<<sum<<endl;
    sum = 0;
  }

  TGraph *g2 = new TGraph(n, vx, vy);
  mg->Add(g2);
  g2->SetTitle("F(E')"); g2->SetLineWidth(3); g2->SetLineColor(3);
  mg->Draw("AL");
  g2->GetHistogram()->SetMinimum(0);

  for (int i = 1; i < n; i++)
  {
    x = 0.01 + 0.05 * ((double)i);
    vx[i] = x;
    vy[i] = A*pow(x,-2.8)/(1+B*pow(x,-1.22)+C*pow(x,-2.54));
  //  cout<<vx[i]<<" ";
  //  cout<<vy[i]<<endl;
  }
  TGraph *g1 = new TGraph(n, vx, vy);
  mg->Add(g1);
  g1->SetTitle("F(E)"); g1->SetLineWidth(3); g1->SetLineColor(2);
  mg->Draw("AL");
  gPad->Modified();
  g1->GetHistogram()->SetMinimum(0);
  //gPad->SetLogy();

  c->Modified();
  c->SaveAs("Fluxoprotoes.eps");

  return 0;
}
