{
gStyle->SetOptStat(1);

TCanvas *c = new TCanvas("c", "Exercicio 32", 0, 0, 500, 500);

TH1F * h[6]; // Array de 5 histogramas

TRandom3 rgen(0); // garantir que a semente é única

int N = 100000;

h[0] = new TH1F ("h1", "f(x)", 500, -4,  4);
h[1] = new TH1F ("h2", "g(x)", 500, -4,  4);
h[2] = new TH1F ("h3", "", 500, -4,  4);
h[3] = new TH1F ("h4", "Media Amostral de f(x)", 500, -4,  4);
h[4] = new TH1F ("h5", "", 500, -4,  4);
h[5] = new TH1F ("h6", "Media Amostral de g(x)", 500, -4,  4);

// Uniforme f(x)

for (int i = 0; i < N; i++)
    h[0]->Fill(rgen.Uniform(-4, 4));

h[0]->GetXaxis()->SetTitle("x");

h[0]->SetLineColor(kBlue);
h[0]->SetLineWidth(2.0);

TPad *pad1 = new TPad("pad1","pad1", 0.00, 0.00, 0.5, 0.5, 0);

  pad1->SetLeftMargin(0.133);
  pad1->SetBottomMargin(0.1326316);
  pad1->SetRightMargin(0.04);
  pad1->Draw();
  pad1->cd();

  h[0]->Draw("HIST");

  c->Modified();
  c->cd();
  c->SetSelected(c);


// g(x)(quadratica)

TF1 *f = new TF1 ("f","[0]*x*x", -10., 10.);
f->SetParameter(0, 1);

for (int i = 0; i < N; i++)
    h[1]->Fill(f->GetRandom());

h[1]->GetXaxis()->SetTitle("x");

TPad *pad2 = new TPad("pad2","pad2", 0.5, 0.00, 1.00, 0.50, 0);

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

float mean1, mean2, stdev1, stdev2;

int sample = 10000;

h[3]->GetXaxis()->SetTitle("x");

TPad *pad3 = new TPad("pad3","pad3", 0.0, 0.5, 0.5, 1.00, 0);

for (int j = 0; j < sample; j++)
 {
   for (int i = 0; i < N / 100; i++)
      h[2]->Fill(rgen.Uniform(-4,4));

    mean1 = h[2]->GetMean();
    stdev1 = h[2]->GetStdDev();
    h[2]->Reset();
    h[3]->Fill(mean1);
 }

 pad3->SetLeftMargin(0.133);
 pad3->SetBottomMargin(0.1326316);
 pad3->SetRightMargin(0.04);
 pad3->Draw();
 pad3->cd();

 h[3]->SetLineColor(kBlue);
 h[3]->SetLineWidth(2);

 h[3]->Draw("HIST3");

 c->Modified();
 c->cd();
 c->SetSelected(c);

TPad *pad4 = new TPad("pad4","pad4", 0.5, 0.50, 1.00, 1.00, 0);

  h[5]->GetXaxis()->SetTitle("x");

  pad4->SetLeftMargin(0.133);
  pad4->SetBottomMargin(0.1326316);
  pad4->SetRightMargin(0.04);
  pad4->Draw();
  pad4->cd();

for (int j = 0; j < sample; j++)
 {
   for (int i = 0 ; i < N / 100; i++)
      h[4]->Fill(f->GetRandom());

      mean2  = h[4]->GetMean();
      stdev2 = h[4]->GetStdDev();
      h[4]->Reset();
      h[5]->Fill( mean2 );
 }

 h[5]->SetLineColor(kRed);
 h[5]->SetLineWidth(2);

 h[5]->Draw("HIST4");

 c->Modified();
 c->cd();
 c->SetSelected(c);

 c->SaveAs("limite_central.eps");

}
