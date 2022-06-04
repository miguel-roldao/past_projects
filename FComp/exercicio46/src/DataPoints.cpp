#include <iostream>
#include "DataPoints.h"
#include "TGraph.h"
#include "TApplication.h"
#include "TCanvas.h"

using namespace std;

int DataPoints::Nplots = 0;

DataPoints::DataPoints()
{
  N = 0;
  x = NULL;
  y = NULL;
}

DataPoints::DataPoints (int n = 0, double* a = NULL, double* b = NULL)
{
  N = n;
  x = new double[N];
  y = new double[N];

  for (int i=0; i<N; i++)
  {
    x[i] = a[i];
    y[i] = b[i];
  }
  cout<<__PRETTY_FUNCTION__<<endl;
}

void DataPoints::Draw()
{
  TGraph *g = new TGraph(N,x,y);

  // Estética
  g->SetMarkerStyle(20);
  g->SetMarkerColor(kBlue); //kCherry
  g->SetMarkerSize(2.5);

  if (Nplots == 0)
  {
    //create application
    TApplication * MyRootApp;
    MyRootApp = new TApplication("Just an example...", NULL, NULL);
    MyRootApp->SetReturnFromRun(true);
  }

  TCanvas *c = new TCanvas("c","c", 600, 500);

  g->Draw("PA");
  c->Update();
  gPad->WaitPrimitive();
  delete g;

  Nplots++;
}

void DataPoints::Print(string FILE) {

  cout << "[Datapoints::Print]: " << endl;
  for (int i=0; i<N; i++)
  {
    cout << "[Datapoints] x = " << x[i] << ", y = " << y[i] << endl;
  }
  //cout << endl << "FILE: " << FILE.c_str();
}


DataPoints::~DataPoints()
{
  delete[] x;
  delete[] y;
}
