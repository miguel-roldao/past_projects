#include <iostream>
#include <vector>
#include "TFormula.h"
#include "TGraph2D.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "../src/ODEsolver.h"


using namespace std;

int main ()
{
  double t = 0;
  double y[] = {1,1,1};
  int N = 3;

  double sigma = 10;
  double rho = 28;
  double beta = 8./3.;

  ODEpoint X(t, y, N);

  X.Print();

  TCanvas *c = new TCanvas("c", "Lorentz Attractor", 0, 0, 700, 500);
  c->SetTheta(30);
  c->SetPhi(120);

  TGraph2D* Lograph = new TGraph2D(N);

  vector<TFormula> TF;

  TFormula* formx = new TFormula("formx","x[0]*0 + [0] * (x[2] - x[1])");
  formx->SetParameter(0,sigma);
  TF.push_back(*formx);

  TFormula* formy = new TFormula("formy","x[0]*0 + x[1] * ([1] - x[3]) - x[2]");
  formy->SetParameter(1,rho);
  TF.push_back(*formy);

  TFormula* formz = new TFormula("formz","x[0]*0 + x[1] * x[2] - [2] * x[3]");
  formz->SetParameter(2,beta);
  TF.push_back(*formz);

  ODEsolver Lorentz(TF);

  vector<ODEpoint> sol_rk4 = Lorentz.RK4solver(X, 0, 100, 1e-5);

  double * hold;

  for(int i = 0; i < sol_rk4.size(); i++) // error nan somewhere
  {
    hold = sol_rk4.at(i).Get_Var_ptr();
  //  cout << i << ": " << hold[0] << " -- " << hold[1] << " -- " << hold[2] << endl;
    Lograph->SetPoint(i, hold[0], hold[1], hold[2]);
  }

  Lograph->SetTitle("");
  Lograph->GetXaxis()->SetTitle("");
  Lograph->GetXaxis()->CenterTitle();
  Lograph->GetXaxis()->SetLabelSize(0);
  Lograph->GetXaxis()->SetTickLength(0);
  Lograph->GetYaxis()->SetTitle("");
  Lograph->GetYaxis()->CenterTitle();
  Lograph->GetYaxis()->SetLabelSize(0);
  Lograph->GetYaxis()->SetTickLength(0);  
  Lograph->GetZaxis()->SetTitle("");
  Lograph->GetZaxis()->CenterTitle();
  Lograph->GetZaxis()->SetLabelSize(0);
  Lograph->GetZaxis()->SetTickLength(0);
  Lograph->SetLineColor(46);
  Lograph->Draw("LINE");

  c->Modified();
  c->SaveAs("Lorentz.eps");

  delete formx;
  delete formy;
  delete formz;
  return 0;
}
