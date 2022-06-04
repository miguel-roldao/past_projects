#include <iostream>
#include <cmath>
#include "Groot.h"
#include "ODEpoint.h"
#include "ODEsolver.h"

using namespace std;

int main()
{
  double m = 100;
  double k = 0.08;
  double g = 9.8;
  double y0 = 8000;
  double tmax = 60;
  double vterminalteo = sqrt(2*m*g/k);

  TF1* anal_sol = new TF1("anal","[0]*[0] / (4*[1]*[2] * x * x) - [3]*exp((-1)*x/[4])/[4]", 0, 1e-3);//[0] + ([1]*x*(exp((-1)*x)-1)) + (-1)* [2]/2 * x * x * exp((-1)*x)",0,10);
  anal_sol->SetParameter(0,1.602e-19);
  anal_sol->SetParameter(1,M_PI);
  anal_sol->SetParameter(2,8.854e-12);
  anal_sol->SetParameter(3,1.744e-16);
  anal_sol->SetParameter(4,0.33e-10);

  TCanvas* c = new TCanvas("c1", "free_fall", 0, 0, 500, 500);

  anal_sol->Draw("L");

  c->Modified();
  c->SaveAs("Anal_Solution.eps");

  //x[0] = t; x[1] = y;  x[2] = v;
  TFormula* F1 = new TFormula("dx_dt","0*x[0]*x[1] + x[2]");
//  TFormula* F2 = new TFormula("dv_dt","0*x[0]*x[1]*x[2] + x[3]");
  TFormula* F2 = new TFormula("a(v)","0* x[0]*x[1] + (-1)*[0] - [1]* fabs(x[2]) * x[2]");
  F2->SetParameter(0,g);
  F2->SetParameter(1,k/m);

  vector<TFormula> TF;
  TF.push_back(*F1);
  TF.push_back(*F2);

  double init[] = {y0, 0};
  ODEpoint p0(0, init, 2);

  ODEsolver ODE(TF);

  vector<ODEpoint> sol = ODE.RK4solver(p0, 0, tmax, 0.1);

  double* h = new double[sol.size()];
  double* velocity = new double[sol.size()];
  double* time = new double[sol.size()];

  for(int j = 0; j < sol.size(); j++)
  {
    time[j] = sol.at(j).Get_Time();
    h[j] = sol.at(j).Get_Var_ptr()[0];
    velocity[j] = sol.at(j).Get_Var_ptr()[1];

  //cout << "t=" << time[j] << "    h="<< h[j]<< "\n";
  }

  TGraph* fall = new TGraph(sol.size(),time, h);

  fall->SetLineColor(2);
  fall->SetMarkerColor(2);
  fall->SetMarkerStyle(6); // '6' = small dot
//  fall->SetTitle("RK4");
  fall->GetXaxis()->SetTitle("Time (s)");
  fall->GetXaxis()->SetRangeUser(0, tmax);
  fall->GetYaxis()->SetTitle("h (m)");
  //  fall->GetYaxis()->SetRangeUser();

  fall->Draw("APL");
  c->Modified();
  c->SaveAs("fall.eps");

  TGraph* vel = new TGraph(sol.size(),time, velocity);
  vel->SetLineColor(2);
  vel->SetMarkerColor(2);
  vel->SetMarkerStyle(6); // '6' = small dot
//  vel->SetTitle("RK4");
  vel->GetXaxis()->SetTitle("Time (s)");
  vel->GetXaxis()->SetRangeUser(0, tmax);
  vel->GetYaxis()->SetTitle("v (m/s)");
  //  vel->GetYaxis()->SetRangeUser();

  vel->Draw("APL");

  c->Modified();
  c->SaveAs("vel.eps");

  return 0;
}

/*

  Definindo o sentido positivo o ascendente:

  F = m*a = m * d(dx/dt)/dt
  Ftotal = -m * g + k * v^2
  Força de atrito sentido contrário à velocidade que tem sentido negativo

  a = d(dx/dt)/dt = -g + k/m * v^2
  d(dx/dt)/dt = -g + k/m * (dx/dt)^2

  Resolvendo a equação diferencial analiticamente obtemos algo como:

  x(t) = x0 + (vterminal*t*(exp(-t)-1) - g/2 * t^2 * exp(-t)
  com v0 = 0
  e
  vterminal = sqrt(2*m*g/k);

  A soluçao teorica nao é esta por constantes nao calculadas (escala temporal)... Mas a forma é esta e intuitivamente e fisicamente faz sentido.
*/
