{
gStyle->SetOptStat(1);

TCanvas *c = new TCanvas("c", "Exercicio 31", 0, 0, 500, 500);

TH1F * h[3]; // Array de 3 histogramas

TRandom3 rgen(0); // garantir que a semente é única

int N = 10000;

h[0] = new TH1F ("h1", "Uniforme", 100, -10, 10);
h[1] = new TH1F ("h2", "f(x)",     100, -10, 10);
h[2] = new TH1F ("h3", "g(x)",     100, -10, 10);

// Uniforme

for (int i = 0; i < N; i++)
    h[0]->Fill(rgen.Uniform(-5, 5));

h[0]->GetXaxis()->SetTitle("x");

h[0]->SetLineColor(kBlue);
h[0]->SetLineWidth(2.0);

TPad *pad1 = new TPad("pad1","pad1",0.00, 0.00, 0.33, 1.00,0);

  pad1->SetLeftMargin(0.133);
  pad1->SetBottomMargin(0.1326316);
  pad1->SetRightMargin(0.04);
  pad1->Draw();
  pad1->cd();

  h[0]->Draw("HIST");

  c->Modified();
  c->cd();
  c->SetSelected(c);


// f (quadratica)

TF1 *f = new TF1 ("f","[0]*x*x", -10., 10.);
f->SetParameter(0, 2);

for (int i = 0; i < N; i++)
    h[1]->Fill(f->GetRandom());

h[1]->GetXaxis()->SetTitle("x");

TPad *pad2 = new TPad("pad2","pad2",0.33,0.00,0.66,1.00,0);

  pad2->SetLeftMargin(0.133);
  pad2->SetBottomMargin(0.1326316);
  pad2->SetRightMargin(0.04);
  pad2->Draw();
  pad2->cd();

  h[1]->SetLineColor(kRed);
  h[1]->SetLineWidth(2);

  h[1]->Draw("HIST2");

  c->Modified();
  c->cd();
  c->SetSelected(c);

// g (gaussiana)

TF1 *g = new TF1 ("g","gaus(0)", -10., 10.);
g->SetParameters(10., 0., 2., kTRUE);

for (int i = 0; i < N; i++)
    h[2]->Fill(g->GetRandom());

h[2]->GetXaxis()->SetTitle("x");

TPad *pad3 = new TPad("pad3","pad3",0.66,0.00,1.00,1.00,0);

  pad3->SetLeftMargin(0.133);
  pad3->SetBottomMargin(0.1326316);
  pad3->SetRightMargin(0.04);
  pad3->Draw();
  pad3->cd();

  h[2]->SetLineColor(kBlack);
  h[2]->SetLineWidth(2);

  h[2]->Draw("HIST3");

  c->Modified();
  c->cd();
  c->SetSelected(c);

  c->SaveAs("histograma_teste.eps");

}
