#include "Spline3Interpolator.h"
#include <cstdio>
#include <cmath>
#include <string>

using namespace std;

Spline3Interpolator::Spline3Interpolator(int n, double *a, double *b) : DataPoints(n, a, b) //, TF1* fF0
{
  //DataPoints::Print();
  SetCurvatureLines();
  FInterpolator = new TF1("FInterpolator", this, &Spline3Interpolator::fInterpolator, x[0]-0.001 ,x[N-1]+0.001, 0);
}

Spline3Interpolator::~Spline3Interpolator()
{
//  delete FInterpolator;
//  delete F0;
}

void Spline3Interpolator::SetCurvatureLines()
{
  Vec dx1(N-3,0.);
  Vec dx2(N-2,0.);
  Vec tri_b(N-2,0.);

//  cout<<x[0]<<endl;

  for(int i = 1; i < N-2; i++)
  {
    dx1[i-1] = x[i-1] - x[i];

  }

  for(int i = 0; i < N-2; i++)
  {
    dx2[i] = 2.0 * (x[i] - x[i+2]);
    tri_b[i] = 6.0 * ((y[i] - y[i+1])/(x[i] - x[i+1]) - (y[i+1] - y[i+2])/(x[i+1] - x[i+2]));
  }

  FCmatrixBanded Tri_mat(dx1,dx2,dx1);
//  Tri_mat.Print();

  EqSolver sistema(Tri_mat,tri_b);
//  sistema.PrintB();
    //Solve the system....
  Vec result = sistema.TridiagonalSolver();
//  result.Print();
   // Assign the private member K[] array pointer...

  Vec aux(N,0.);
  K = aux;
  //K.Print();

  K[0] = K[N-1] = 0;

  for(int i = 1; i < N-1; i++)
  {
    K[i] = result[i-1];
  }
//  K.Print();
}

double Spline3Interpolator::Interpolate(double fx) {

  double A;
  int i;

  for(i = 0; i < N-1; i++)   // detect in which segment is x!
  {
    if (fx < x[0])
    {
      //cout << fx << endl;
      return y[0];
    }

    else if (fx > x[N-1])
    {
    //  cout << fx << endl;
      return y[N-1];
    }

    else if(fx == x[i])
      return y[i];

    else if(fx == x[i+1])
      return y[i+1];

    else if(fx > x[i+1])
      continue;

    else if(fx > x[i] && fx < x[i+1])
    {
      break;
    }
  }

  // cout << "segmento : " << i <<endl;
  A = K[i] * (pow(fx-x[i+1],3)/(x[i]-x[i+1]) - (fx - x[i+1]) * (x[i] - x[i+1]))/6 - K[i+1] * ((pow(fx-x[i],3)/ (x[i]-x[i+1]) - (fx - x[i]) * (x[i] - x[i+1])))/6  + (y[i] * (fx - x[i+1]) - y[i+1]*(fx - x[i]) )/(x[i] - x[i+1]);


  /*A = K[i] * (((fx - x[i+1])*(fx - x[i+1])*(fx - x[i+1]))/(x[i] - x[i+1]) - (fx-x[i+1]) * (x[i] - x[i+1]))/ 6
  - K[i+1] * (((fx - x[i])*(fx - x[i])*(fx - x[i]))/(x[i] - x[i+1]) - (fx-x[i]) * (x[i] - x[i+1]))/ 6
  + (y[i] * (fx - x[i+1]) + (y[i+1] * (fx - x[i])))/(x[i] - x[i+1]);*/
   //cout << "A:" << A << "    x: "<<fx<<endl;
  return A;
}


void Spline3Interpolator::Draw() {

  if (Nplots == 0)
  {
    //create application
    TApplication * MyRootApp;
    MyRootApp = new TApplication("Just an example of Spline", NULL, NULL);
    MyRootApp->SetReturnFromRun(true);
  }

  TCanvas *c2 = new TCanvas("c1","c1",600,500);
  gPad->Clear();
  gStyle->SetLabelSize(0.06,"X");
  gStyle->SetLabelSize(0.06,"Y");
  TGraph *g = new TGraph(N,x,y);
  g->SetMarkerStyle(20);
  g->SetMarkerColor(kCherry);
  g->SetMarkerSize(0.2);

	FInterpolator->SetLineColor(kCherry);
	FInterpolator->SetLineWidth(4);
	FInterpolator->SetTitle("Cubic Spline");

  /*if (F0 != NULL) {
    F0->SetLineColor(kBlue);
    F0->SetLineWidth(4);
    F0->SetLineStyle(2);
  }*/

  gPad->DrawFrame(FInterpolator->GetXmin(), FInterpolator->GetMinimum(),
                  FInterpolator->GetXmax(), FInterpolator->GetMaximum(), FInterpolator->GetTitle());

  g->Draw("PSAME");

  FInterpolator->Draw("SAME");

  /*if (F0 != NULL)
    F0->Draw("SAME");*/

  c2->Update();
  c2->SaveAs("plot_Spline.eps");
  gPad->WaitPrimitive();
  // delete MyRootApp;


  delete g;
  delete c2;
  Nplots++;
}
