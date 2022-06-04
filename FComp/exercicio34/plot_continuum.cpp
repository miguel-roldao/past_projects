#include <iostream>
#include <fstream>
#include <string>
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"

using namespace std;

class Curves
{
    vector<double> x,y;
  public:
    void setX(double a) {x.push_back(a);}
    void setY(double b) {y.push_back(b);}
    vector<double> getX() {return x;}
    vector<double> getY() {return y;}
    void Reset() {x.clear();y.clear();}
};

vector<Curves> read_spec(string name)
{
  ifstream myfile;
  myfile.open(name);

  vector<Curves> VEC;

  if (myfile.is_open())
  {

    int i;
    double a, b;

    while(myfile >> a >> b >> i)
    {
      if(VEC.size() < i)
      {
        Curves c1;
        c1.setX(a);
        c1.setY(b);
        VEC.push_back(c1);
      }

      else
      {
        VEC[i-1].setX(a);
        VEC[i-1].setY(b);
      }
    }

    myfile.close();

  }

  else
    cout << "Unable to open file";

  return VEC;
}

TGraph *makeGraph(vector<Curves> VEC, int k)
{
  double vx[VEC[k].getX().size()];
  double vy[VEC[k].getY().size()];

    for (int i = 0; i < VEC[k].getX().size(); i++)
    {
      vx[i] = VEC[k].getX()[i];
      vy[i] = VEC[k].getY()[i];
    }


  TGraph *g1 = new TGraph(VEC[k].getX().size(), vx, vy);

  return g1;
}

int main()
{
  vector<Curves> VEC = read_spec("data.txt");
  int n = VEC.size();  // number of graphs
  //gStyle->SetOptTitle(0); //no title
  TCanvas *c = new TCanvas("c", "my canvas", 0, 0, 500, 500);

  TGraph *g[n];
  TMultiGraph *mg = new TMultiGraph();
  auto legend = new TLegend(0.7,0.1,0.9,0.25);
  legend->SetHeader("Legenda","C"); // option "C" allows to center the header

  for(int i = 0; i < n; i++)
  {
    g[i] = makeGraph(VEC, i);
    char s[10];
    sprintf(s,"plot %d",i+1);
    mg->Add(g[i]); g[i]->SetTitle(s); g[i]->SetLineWidth(3); g[i]->SetLineColor(i+2);
  }

  mg->Draw("ALP");
  gPad->Modified();
/*  mg->GetXaxis()->SetLimits(0.,30.);
  mg->SetMinimum(-20);
  mg->SetMaximum(20);*/
  for(int i = 0; i < n; i++)
  {
    char s[10];
    sprintf(s,"plot %d",i+1);
    legend->AddEntry(g[i],s,"l");
  }

  legend->Draw();

  c->Modified();
  c->SaveAs("exercicio34.eps");
  return 0;
}
