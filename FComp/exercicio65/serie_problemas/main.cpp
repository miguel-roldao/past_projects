#include <iostream>
#include <vector>
#include "TFormula.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLegend.h"
#include "../src/ODEsolver.h"


using namespace std;

int main ()
{
  double t = 0.4;
  double y[] = {0.2};
  int N = 1;

  ODEpoint X(t, y, N);

  X.Print();

  TCanvas *c = new TCanvas("c", "exercicio65", 0, 0, 500, 500);

  TGraph* grafic_eul = new TGraph();
  TGraph* grafic_rk2 = new TGraph();
  TGraph* grafic_rk4 = new TGraph();

  vector<TFormula> TF;

  TFormula* form = new TFormula("form","-x + 0.5*y + 1");
  TF.push_back(*form);

  ODEsolver teste(TF);

  vector<ODEpoint> sol_eul = teste.Eulersolver(X, 0.4, 1.8, 0.1);
  vector<ODEpoint> sol_rk2 = teste.RK2solver(X, 0.4, 1.8, 0.1);
  vector<ODEpoint> sol_rk4 = teste.RK4solver(X, 0.4, 1.8, 0.1);

  for(int i = 0; i < sol_eul.size(); i++)
  {
    grafic_eul->SetPoint(i, sol_eul.at(i).Get_Time(), sol_eul.at(i).Get_Var_ptr()[0]);
    grafic_rk2->SetPoint(i, sol_rk2.at(i).Get_Time(), sol_rk2.at(i).Get_Var_ptr()[0]);
    grafic_rk4->SetPoint(i, sol_rk4.at(i).Get_Time(), sol_rk4.at(i).Get_Var_ptr()[0]);
  }
  grafic_eul->SetLineColor(2);
  grafic_eul->Draw();
  grafic_rk2->SetLineColor(4);
  grafic_rk2->Draw("SAME");
  grafic_rk4->SetLineColor(6);
  grafic_rk4->Draw("SAME");

  TLegend * legend = new TLegend(0.5,0.25,0.8,0.45);
  legend->AddEntry(grafic_eul,"Euler Method","l");
  legend->AddEntry(grafic_rk2,"Runge-Kutta2","l");
  legend->AddEntry(grafic_rk4,"Runge-Kutta4","l");
  legend->Draw();

  c->Modified();
  c->SaveAs("exercicio65.eps");

  delete form;
  return 0;
}
