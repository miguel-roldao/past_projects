#include <iostream>
#include "TF1.h"
#include "TGraph.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TAxis.h"

#define PI 3.14159

using namespace std;

int main ()
{
  TCanvas *c = new TCanvas("c", "Exercicio 54 - Integral", 0, 0, 500, 500);
  TCanvas *cerror = new TCanvas("cerror", "Exercicio 54 - Erro", 0, 0, 500, 500);

  TRandom3 rgen(0); // garantir que a semente é única

  double xmin = .2*PI;
  double xmax = .5*PI;

  TF1 *f = new TF1("f","cos(x)", xmin, xmax);

  int MIN_SAMPLES = 20;
  int MAX_SAMPLES = 100000;

  double * NSamples =  new double[MAX_SAMPLES - MIN_SAMPLES];
  double * Estimate = new double[MAX_SAMPLES - MIN_SAMPLES];
  double * Error = new double[MAX_SAMPLES - MIN_SAMPLES];

  for (int j = MIN_SAMPLES; j < MAX_SAMPLES; j++)
  {
  	NSamples[j - MIN_SAMPLES] = j;

  	double F = 0.;
  	double F_SQUARED = 0.;

  	for (int i = 0 ; i < j; i++)
    {
  		double x = xmin + (xmax-xmin) * gRandom->Uniform();
  		double func = f->Eval(x);

  		F += func;
  		F_SQUARED += func * func;
  	}

  	// mean
  	double fm = F / j;

    // mean of f^2
    double f2m = F_SQUARED / j;

  	// integrals
  	double I = (xmax-xmin)/(double) j * F;

  	//variances
  	double var = sqrt(f2m - fm*fm);

  	//errors
  	double E = (xmax - xmin)/ sqrt ((double) j) * var;

  	Estimate[j - MIN_SAMPLES] = I;

    Error[j - MIN_SAMPLES] =  E;
  }

  c->SetLogx();
  c->SetLogy();
  c->SetGridx();
  c->SetGridy();

  cerror->SetLogx();
  cerror->SetLogy();
  cerror->SetGridx();
  cerror->SetGridy();

  c->cd();

  TGraph* gr = new TGraph(MAX_SAMPLES - MIN_SAMPLES, NSamples, Estimate);
  gr->SetMarkerStyle(24);
  gr->SetTitle("Monte Carlo Integral");
  gr->GetXaxis()->SetTitle("Number of Samples");
  gr->GetYaxis()->SetTitle("Integral");
  gr->Draw("AP");
  c->Modified();
  c->SaveAs("Integral_cos.eps");

  cerror->cd();

  TGraph* grerror = new TGraph(MAX_SAMPLES - MIN_SAMPLES, NSamples, Error);
  grerror->SetMarkerStyle(24);
  grerror->SetTitle("Monte Carlo Integral");
  grerror->GetXaxis()->SetTitle("Number of Samples");
  grerror->GetYaxis()->SetTitle("Error");
  grerror->Draw("AP");
  cerror->Modified();
  cerror->SaveAs("IntegralError_cos.eps");


  return 0;
}
