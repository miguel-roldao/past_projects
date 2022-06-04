#include <iostream>
#include "../src/Vec.h"
#include "../src/FCtools.h"
#include "TCanvas.h"
#include "TF2.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TPaletteAxis.h"
using namespace std;

/*
            *     *   * * *   * * * *  * * * *           * * * *     * * *
            * * * *   *       *           *              *         *
            *  *  *   * **    * * *       *     * * *    * * *     *
            *     *   *       *           *              *         *
            *     *   * * *   *           *              *           * * *


            Alexandre Barbosa e Miguel Roldão (D02), 2019-2020                  */



int main()
{

  Vec v1(10); //array with 10 values set to zero
  v1.Print();
  Vec v2(10,5.); //array with 10 values set to 5
  v2.Print();
  double a[]={1.2, 3.0, 5.4, 5.2, 1.0, 0.0};
  Vec v3(5,a); //array with 5 values given by "a" pointer
  v3.Print();
  Vec v4(v3); //define a vector by using another one
  v4.Print();
  cout<<"\n\n"<<endl;

  // Teste dos Operadores

  double b[] = {1.0, 2.0, 3.0};
  Vec u(3, b);
  double d[] = {3.0, 2.0, 1.0};
  Vec u1(3,d);

  cout << "*** Teste dos Operadores ***" << endl;

  cout << "      u = ";
  u.Print();
  cout << "      v = ";
  u1.Print();

  Vec j = u + u1;
  cout << "  u + v = ";
  j.Print();
  cout << "  u + v = ";
  j = u - u1;
  j.Print();
  cout << "  u * v = ";
  j = u * u1;
  j.Print();
  cout << " u += v = ";
  u += u1;
  u.Print();
  cout << " u -= v = ";
  u -= u1;
  u.Print();
  cout << " u *= v = ";
  u *= u1;
  u.Print();
  cout << "     -u = ";
  //-u;
  j = -u;
  j.Print();
  cout << "     +u = ";
  //+u;
  j = +u;
  j.Print();
  cout << "  u x v = ";
  j = u.cross(u1);
  j.Print();
  j = u1 * 2;
  cout << "  2 * v = ";
  j.Print();
  cout << endl << "u dot v = " << u.dot(u1) << endl;
  cout << "   u[2] = " << u[2] << endl << endl;

  // j = u1.dot(v3); // teste de exit

/*  mais testes

  //matrix 5x5
  double CM[][5] = {{ 1.0, 7.0, 5.0, 3.0,-3.0},
                    { 5.0, 2.0, 8.0,-2.0, 4.0},
                    { 1.0,-5.0,-4.0, 6.0, 7.6},
                    { 0.0,-5.0, 3.0, 3.2, 3.3},
                    { 1.0, 7.0, 2.0, 2.1, 1.2}};

  //array of Vec’s for storing matrix rows
  Vec cv[5];

  //copy rows as arrays into Vecs
  for (int i=0; i<5; i++)
  {
    cv[i].SetEntries(5,CM[i]);
    cv[i].Print();
  }
                                                        */



  FCtools cools;
  vector<Vec> recebido_G = cools.ReadFile2Vec("../matrix.txt");

  cout<<recebido_G.size()<<endl;

  for (int i = 0; i < recebido_G.size(); i++)
    recebido_G.at(i).Print();

    cout<<endl;

  Vec *recebido_L = cools.ReadFile("../matrix.txt");

  for (int k = 0; k < recebido_G.size(); k++)   // como saber o tamanho do ponteiro?
    recebido_L[k].Print();

  TCanvas* c = new TCanvas("c", "my canvas", 500, 500);
  gStyle->SetOptStat(0);

  TH2F* h2 = new TH2F("h2", "matrix.txt", recebido_G.at(0).Size(), 0, recebido_G.at(0).Size(), recebido_G.size(), 0, recebido_G.size());

  for(int i = 0; i < recebido_G.size(); i++)
    for (int j = 0; j < recebido_G[i].Size(); j++)
    {
      h2->Fill(j, i , recebido_L[i].GetEntries()[j]);
    }

  cout << endl;


  TPad *pad1 = new TPad("pad1","pad1", 0.00, 0.25, 0.5, 0.75, 0);
  pad1->SetLeftMargin(0.133);
    //pad1->SetBottomMargin(0.1326316);
  pad1->SetRightMargin(0.04);
  pad1->Draw();
  pad1->cd();

  h2->SetLineWidth(2);
  h2->SetLineColor(9);
  h2->Draw("LEGO1");

  c->Modified();
  c->cd();
  c->SetSelected(c);

  TPad *pad2 = new TPad("pad2","pad2", 0.5, 0.25, 1.00, 0.75, 0);

  pad2->SetLeftMargin(0.07);
  //pad2->SetBottomMargin(0.1326316);
  pad2->SetRightMargin(0.133);
  pad2->Draw();
  pad2->cd();
  gStyle->SetPalette(kCherry);

  h2->SetLineWidth(2);
  h2->SetLineColor(3);
  h2->Draw("COLZ");

  gPad->Update();

  TPaletteAxis *palette = (TPaletteAxis*)h2->GetListOfFunctions()->FindObject("palette");

  palette->SetY2NDC(0.7);

  c->Modified();
  c->cd();
  c->SetSelected(c);

  c->SaveAs("../serie_problemas/exercicio41.eps");
  return 0;
}
