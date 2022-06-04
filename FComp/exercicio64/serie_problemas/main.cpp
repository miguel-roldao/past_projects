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
  double t = 0.5;
  double y[] = {1.0, 2.0};
  int N = 2;

  ODEpoint X(t, y, N);

  X.Print();

  TCanvas *c = new TCanvas("c", "exercicio64", 0, 0, 500, 500);
  c->Divide(2,2);

  TGraph2D* grafic_eul = new TGraph2D();
  TGraph2D* grafic_heu = new TGraph2D();
  TGraph2D* grafic_rk2 = new TGraph2D();
  TGraph2D* grafic_rk4 = new TGraph2D();

  vector<TFormula> TF;

  TFormula* form = new TFormula("form","x*x*x");
  TF.push_back(*form);
/*
  form = new TFormula("form","x*x + 1");
  TF.push_back(*form);

  form = new TFormula("form","x + 1");
  TF.push_back(*form);*/

  form = new TFormula("form","cos(x) + 1");
  TF.push_back(*form);

  ODEsolver teste(TF);

  vector<ODEpoint> sol_eul = teste.Eulersolver(X, 0.5, 6, 0.1);
  vector<ODEpoint> sol_heu = teste.Heun(X, 0.5, 6, 0.1);
  vector<ODEpoint> sol_rk2 = teste.RK2solver(X, 0.5, 6, 0.1);
  vector<ODEpoint> sol_rk4 = teste.RK4solver(X, 0.5, 6, 0.1);

  for(int i = 0; i < sol_eul.size(); i++)
  {
    grafic_eul->SetPoint(i, sol_eul.at(i).Get_Time(), sol_eul.at(i).Get_Var_ptr()[0], sol_eul.at(i).Get_Var_ptr()[1]);
    grafic_heu->SetPoint(i, sol_heu.at(i).Get_Time(), sol_heu.at(i).Get_Var_ptr()[0], sol_heu.at(i).Get_Var_ptr()[1]);
    grafic_rk2->SetPoint(i, sol_rk2.at(i).Get_Time(), sol_rk2.at(i).Get_Var_ptr()[0], sol_rk2.at(i).Get_Var_ptr()[1]);
    grafic_rk4->SetPoint(i, sol_rk4.at(i).Get_Time(), sol_rk4.at(i).Get_Var_ptr()[0], sol_rk4.at(i).Get_Var_ptr()[1]);

    //sol_heu.at(i).Print();
    //sol_rk2.at(i).Print();
    //sol_rk4.at(i).Print();
  }
  c->cd(1);
  grafic_eul->SetTitle("Euler Method");
  grafic_eul->Draw("surf1");
  c->cd(2);
  grafic_heu->SetTitle("Heun Method");
  grafic_heu->Draw("surf1");
  c->cd(3);
  grafic_rk2->SetTitle("RK2 Method");
  grafic_rk2->Draw("surf1");
  c->cd(4);
  grafic_rk4->SetTitle("RK4 Method");
  grafic_rk4->Draw("surf1");

  c->Modified();


  c->Modified();
  c->SaveAs("exercicio64.eps");

  delete form;
  return 0;
}
