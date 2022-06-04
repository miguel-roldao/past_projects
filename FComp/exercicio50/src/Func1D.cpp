#include "Func1D.h"

using namespace std;

int Func1D::Nplots = 0;

Func1D::Func1D (TF1 * ff)
{
  F = new TF1;
  F = ff;
}

Func1D::~Func1D()
{}

void Func1D::SetFunc (TF1 * ff)
{
  delete F;

  F = new TF1;

  F = ff;
}

TF1* Func1D::GetFunc() const
{
  return F;
}

void Func1D::Draw()
{
  if (Nplots == 0)
  {
    //create application
    TApplication * MyRootApp;
    MyRootApp = new TApplication("Derivator", NULL, NULL);
    MyRootApp->SetReturnFromRun(true);
  }

  TCanvas *c2 = new TCanvas("c1","c1",600,500);
  gPad->Clear();
  gStyle->SetLabelSize(0.06,"X");
  gStyle->SetLabelSize(0.06,"Y");

  F->SetLineColor(kBlue);
  F->SetLineWidth(4);
  //F->SetTitle("Plot");

  gPad->DrawFrame(F->GetXmin(), F->GetMinimum(),
                  F->GetXmax(), F->GetMaximum(), F->GetTitle());

  F->Draw("SAME");

  c2->Update();
  c2->SaveAs("func1D.eps");
  gPad->WaitPrimitive();

  delete c2;
  Nplots++;
}

double Func1D::Evaluate(double x)
{
  double f_x = F->Eval(x);

  return f_x;
}

void Func1D::Nplots_increment() { Nplots++;}
