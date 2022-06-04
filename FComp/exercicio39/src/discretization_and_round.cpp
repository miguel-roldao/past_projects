#include <iostream>
#include <fstream>
#include <string>
#include "discretization_and_round.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TStyle.h"

using namespace std;

float f1(float x)
  {
    return exp(2.0*x);
  }

float f1d (float x)
  {
    return 2.0 * exp(2.0*x);
  }

float Function::DRError (double *x, double *p )
{
 return ( ( f1 (p[0]+x[0]) - f1(p[0]) ) / x[0] - f1d(p[0]) );
}

void Function::SetParam(float p)
{
	g->SetParameter(0, p);
}

Function::Function(double a, double b)
{
   g = new TF1("Discretization and Round-Off Error", this, &Function::DRError, a, b, 1);
}

float Function::GetRand()
{
	return g->GetRandom();
}

void Function::plot()
{
  TCanvas *c = new TCanvas("c", "Exercício 39", 0, 0, 500, 500);

  TPad *pad = new TPad("pad","pad", 0.0, 0.00, 1.00, 1.00, 0);

  pad->SetLeftMargin(0.133);
  pad->SetBottomMargin(0.1326316);
  pad->SetRightMargin(0.04);
  pad->SetLogx();
  pad->SetLogy();
  pad->Draw();
  pad->cd();

	g->Draw();
  g->GetHistogram()->GetXaxis()->SetTitle("h");
  g->GetHistogram()->GetYaxis()->SetTitle("Erro");
  c->Update();
	c->Modified();
	c->SaveAs("../discretization_and_round.eps");
}
