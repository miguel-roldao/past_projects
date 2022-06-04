#include <iostream>
#include <vector>
#include "TCanvas.h"
#include "TH1F.h"
#include "Vec.h"
#include "TStyle.h"
#include "EqSolver.h"

void Laplace1D(double length, double boundary_0 = 0, double boundary_L = 0, int n = 1000, char * title = NULL, char * filename = NULL);

using namespace std;

int main ()
{
  string s = "T(x)";
  string s1 = "68_2cm.png";
  string s2 = "68_10cm.png";
  char plot1[15];
  strcpy(plot1, s.c_str());
  char file1[15]; // = "68_2cm.png";
  strcpy(file1, s1.c_str());
  Laplace1D(100, 40, 10, 5000, plot1, file1);

  char plot2[15];
  strcpy(plot2, s.c_str());
  char file2[15]; // = "68_10cm.png";
  strcpy(file2, s2.c_str());
  Laplace1D(100, 40, 10, 1000, plot2, file2);

  return 0;
}

void Laplace1D (double length, double boundary_0, double boundary_L, int n, char * title, char * filename)
{
  //int n = (int) length / step;

  double step = length / n;

  Vec UD(n-1, 1. / (step*step));  // 'UD' = Upper Diagonal
  Vec MD(n,     -2. / (step*step)); // 'MD' = Main Diagonal
  Vec LD(n-1, 1. / (step*step));  // 'LD' = Lower Diagonal
  Vec b (n,     0.);          // Vetor (matriz aumentada)

  b[0] = (-1) * boundary_0 / (step*step);
  b[ n - 1 ] = (-1)*boundary_L / (step*step);

  FCmatrixBanded M(UD, MD, LD);
  EqSolver FiniteDifferences(M, b);

  Vec sol = FiniteDifferences.TridiagonalSolver();

  double * solution = sol.GetEntries();

  /*for (int i = 0; i < n; i++)
    solution[i] = FiniteDifferences.TridiagonalSolver().GetEntries()[i];*/

  gStyle->SetOptStat(0); // esconde a estatística do histogramas

  // Cria o canvas e o histograma
  TCanvas *c = new TCanvas(title, title, 0, 0, 500, 500);
  TH1F* histogram = new TH1F(title, title, n, 0, length);

  // Preenche o histograma
  for (int j = 0; j < n; j++)
  {
    histogram->SetBinContent(j, solution[j]);
    cout << solution[j] << "\n";//  cout << "Dimmm===" << sol.Size() << "\n";

  }
  histogram->SetBinContent(n,boundary_L);

  // Estética do histograma
  histogram->GetXaxis()->SetTitle("x");
  histogram->SetLineColor(kRed);
  histogram->SetLineWidth(2);

  // Desenha o histograma
  histogram->Draw("L");

  c->Modified();
  c->cd();
  c->SetSelected(c);

  c->SaveAs(filename);
}
