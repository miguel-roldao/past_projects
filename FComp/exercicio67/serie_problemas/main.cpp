#include <iostream>
#include <cmath>
#include "ODEpoint.h"
#include "ODEsolver.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TAxis.h"
#define PI atan(1) * 4

using namespace std;

int main()
{
  double t = 0;
  double tmax = 2*PI;
  double y[] = {2,0};
  int N = 2;
  double g = 10;
  double l = 0.5;
  double k = g/l;

  TCanvas *c = new TCanvas("c", "canvas Pendulum", 0, 0, 700, 500);

  ODEpoint teta0(0, y, 2);

  vector<TFormula> TF;

  // x[0] = t;   x[1] = teta;  x[2] = dteta_dt;
  TFormula* dteta_dt = new TFormula("dteta_dt","0*x[0]*x[1] + x[2]");
  TF.push_back(*dteta_dt);

  TFormula* dteta2_dt2 = new TFormula("dteta2_dt2","0*x[0]+ (-1) * [0]*sin(x[1]) + 0*x[2]");
  dteta2_dt2->SetParameter(0,k);
  TF.push_back(*dteta2_dt2);

  ODEsolver Pendulum(TF);

  vector<ODEpoint> sol = Pendulum.RK4solver(teta0, 0.0, tmax, 0.1);
  vector<ODEpoint> sol_verlet = Pendulum.Verlet(teta0, 0.0, tmax, 0.1);


  TMultiGraph* mg = new TMultiGraph();

  double* teta = new double[sol.size()];
  double* omega = new double[sol.size()];
  double* time = new double[sol.size()];

  for(int j = 0; j < sol.size(); j++)
  {
    time[j] = sol_verlet.at(j).Get_Time();
    teta[j] = sol_verlet.at(j).Get_Var_ptr()[0];
    omega[j] = sol_verlet.at(j).Get_Var_ptr()[1];
  }

  TGraph* PendGraph2 = new TGraph(sol.size(),time, teta);

  mg->Add(PendGraph2);
  PendGraph2->SetLineColor(4);
  PendGraph2->SetMarkerColor(4);
  PendGraph2->SetMarkerStyle(5); // '5' = cross
  PendGraph2->SetTitle("Verlet");
  PendGraph2->GetXaxis()->SetTitle("Time (s)");
  PendGraph2->GetXaxis()->SetRangeUser(0, tmax);
  PendGraph2->GetYaxis()->SetTitle("Teta (rad)");
//  PendGraph2->GetYaxis()->SetRangeUser();

for(int j = 0; j < sol.size(); j++)
{
  time[j] = sol.at(j).Get_Time();
  teta[j] = sol.at(j).Get_Var_ptr()[0];
  omega[j] = sol.at(j).Get_Var_ptr()[1];
}

TGraph* PendGraph = new TGraph(sol.size(),time, teta);

mg->Add(PendGraph);
PendGraph->SetLineColor(2);
PendGraph->SetMarkerColor(2);
PendGraph->SetMarkerStyle(5); // '5' = cross
PendGraph->SetTitle("RK4");
PendGraph->GetXaxis()->SetTitle("Time (s)");
PendGraph->GetXaxis()->SetRangeUser(0, tmax);
PendGraph->GetYaxis()->SetTitle("Teta (rad)");
//  PendGraph->GetYaxis()->SetRangeUser();

  mg->Draw("APL");

  TLegend * legend = new TLegend(0.82,0.8,0.97,0.95);
  legend->AddEntry(PendGraph2,"Verlet Method","l");
  legend->AddEntry(PendGraph,"Runge-Kutta4","l");
  legend->Draw();

  c->Modified();
  c->SaveAs("Pendulum.eps");

  TGraph* phase_space = new TGraph(sol.size(),teta, omega);

  phase_space->SetMarkerStyle(24); // '6' = small dot
  phase_space->SetTitle("Phase Space");
  phase_space->GetXaxis()->SetTitle("teta (rad)");
  //  phase_space->GetXaxis()->SetRangeUser();
  phase_space->GetYaxis()->SetTitle("omega (rad/s)");
  //  phase_space->GetYaxis()->SetRangeUser();
  phase_space->Draw("AP");
  c->Modified();
  c->SaveAs("phase_space.eps");


  return 0;
}
