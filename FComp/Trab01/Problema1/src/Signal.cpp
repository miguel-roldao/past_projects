#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "Signal.h"
#include "FCtools.h"
#include "vec.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TPaletteAxis.h"

using namespace std;

Signal::Signal()
{
//  cout << __PRETTY_FUNCTION__ << endl;
}

Signal::Signal(double* t, double* sig, int n)
{
  for(int i = 0; i < n; i++)
  {
    time.push_back(t[i]);
    signal.push_back(sig[i]);
  }
}

Signal::Signal(vector<double> t, vector<double> sig)
{
  time = t;
  signal = sig;
}

Signal::Signal(string filename)
{
  FCtools cools;
  vector<Vec> V = cools.ReadFile2Vec(filename);

  for(int i = 0; i < V.size(); i++)
  {
    time.push_back(V.at(i)[0]);
    signal.push_back(V.at(i)[1]);
  }
}

Signal::Signal(const Signal & S)
{
  time = S.time;
  signal = S.signal;
}

Signal & Signal::operator=(const Signal & S)
{
  if (this != &S)
  {
    time = S.GetTime();
    signal = S.GetValue();
  }

  return *this;
}

vector<double> Signal::GetTime() const
{
  return time;
}

vector<double> Signal::GetValue() const
{
  return signal;
}

int Signal::Size() const
{
  return time.size();
}

Signal Signal::operator+(const Signal & S)
{
  if (Size() == S.Size())
  {
    for(int i = 0; i < Size(); i++)
    {
      signal.at(i) += S.GetValue().at(i);
    }
  }
  else
  {
    cout << "Os sinais não têm o mesmo tamanho; é impossível somá-los!" << endl;
    exit (EXIT_FAILURE);
  }

  return *this;
}

Signal Signal::operator-(const Signal & S)
{
  if (Size() == S.Size())
  {
    for(int i = 0; i < Size(); i++)
    {
      signal.at(i) -= S.GetValue().at(i);
    }
  }
  else
  {
    cout << "Os sinais não têm o mesmo tamanho; é impossível subtraí-los!" << endl;
    exit (EXIT_FAILURE);
  }

  return *this;
}

Signal Signal::operator*(double c)
{
  for(int i = 0; i < Size(); i++)
  {
    signal.at(i) *= c;
  }

return *this;
}

Signal Signal::operator*(const Signal & S)
{
  if (Size() == S.Size())
  {
    for(int i = 0; i < Size(); i++)
    {
      signal.at(i) *= S.GetValue().at(i);
    }
  }
  else
  {
    cout << "Os sinais não têm o mesmo tamanho; é impossível multiplicá-los!" << endl;
    exit (EXIT_FAILURE);
  }

  return *this;
}

void Signal::Plot(string s) const
{
  //char *name = s + ".eps";
  char name[15];


  strcpy(name,s.c_str()); // copy string one into the result.
  strcat(name,".eps"); // append string two to the result.

  TCanvas* c = new TCanvas("c", "my canvas", 500, 500);
  //gStyle->SetOptStat(0);

  double* vx = new double[Size()];
  double* vy = new double[Size()];

  for(int i = 0; i < Size(); i++)
  {
    vx[i] = time.at(i);
    vy[i] = signal.at(i);
  }

  TMultiGraph *mg = new TMultiGraph();
  TGraph *g1 = new TGraph(Size(), vx, vy);
  mg->Add(g1);
  g1->SetTitle("Signal"); g1->SetLineWidth(3); g1->SetLineColor(2);
  mg->Draw("AL");
  gPad->Modified();

  delete[] vx;
  delete[] vy;

  c->Modified();
  c->SaveAs(name);
}

pair<double,double> Signal::operator[] (int i)
{
  pair <double,double> P ;
  P.first = time.at(i);
  P.second = signal.at(i);

  return P;
}

double Signal::Sampling_freq() const
{
  double f = 1/(time[5]-time[4]);

  return f;
}
