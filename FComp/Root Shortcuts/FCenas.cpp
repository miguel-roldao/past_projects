#include "FCenas.h"

void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, const char *title, const char *xtitle, const char *ytitle, const char *filename, int marker_style, const char * DrawOption)
{
  TGraph * graph = new TGraph(npoints, x, y);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();
  c->SaveAs(filename);

  delete graph;
}

void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, double xmin, double xmax, double ymin, double ymax, const char *title, const char *xtitle, const char *ytitle, const char *filename, int marker_style, const char * DrawOption)
{
  TGraph * graph = new TGraph(npoints, x, y);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetXaxis()->SetRangeUser(xmin, xmax);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->GetYaxis()->SetRangeUser(ymin, ymax);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();
  c->SaveAs(filename);

  delete graph;
}


void DrawHistogram(int nbins, double * bincontent, double min, double max, TCanvas *c, const char * title, const char * xtitle, const char * ytitle, const char *filename, double line_width, Color_t color, const char * DrawOption)
{
  TH1F* histogram = new TH1F("h", title, nbins, min, max);

  for (int j = 0; j < nbins; j++)
    histogram->Fill(bincontent[j]);

  histogram->GetXaxis()->SetTitle(xtitle);
  histogram->GetYaxis()->SetTitle(ytitle);

  histogram->SetLineColor(color);
  histogram->SetLineWidth(line_width);

  histogram->Draw(DrawOption);

  c->Modified();
  c->Update();
  c->SaveAs(filename);

  delete histogram;

}

void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, int pad, const char *title, const char *xtitle, const char *ytitle, int marker_style, const char * DrawOption)
{
  TGraph * graph = new TGraph(npoints, x, y);
  c->cd(pad);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();

}

void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, int pad, double xmin, double xmax, double ymin, double ymax, const char *title, const char *xtitle, const char *ytitle, int marker_style, const char * DrawOption)
{
  TGraph * graph = new TGraph(npoints, x, y);
  c->cd(pad);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetXaxis()->SetRangeUser(xmin, xmax);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->GetYaxis()->SetRangeUser(ymin, ymax);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();

}


void DrawHistogram(int nbins, double * bincontent, double min, double max, TCanvas *c, int pad, const char * title, const char * xtitle, const char * ytitle, double line_width, Color_t color, const char * DrawOption)
{
  TH1F* histogram = new TH1F("h", title, nbins, min, max);
  c->cd(pad);

  for (int j = 0; j < nbins; j++)
    histogram->Fill(bincontent[j]);

  histogram->GetXaxis()->SetTitle(xtitle);
  histogram->GetYaxis()->SetTitle(ytitle);

  histogram->SetLineColor(color);
  histogram->SetLineWidth(line_width);

  histogram->Draw(DrawOption);

  c->Modified();
  c->Update();

}

void DrawTGraph2D(int npoints, double * x, double * y, double * z, TCanvas *c, const char *title, const char *xtitle, const char *ytitle, const char *ztitle, const char *filename, int marker_style, const char *DrawOption)
{
  TGraph2D * graph = new TGraph2D(npoints, x, y, z);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->GetZaxis()->SetTitle(ztitle);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();
  c->SaveAs(filename);

  delete graph;
}

void DrawTGraph2D(int npoints, double * x, double * y, double * z, TCanvas *c, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, const char *title, const char *xtitle, const char *ytitle, const char *ztitle, const char *filename, int marker_style, const char *DrawOption)
{
  TGraph2D * graph = new TGraph2D(npoints, x, y, z);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetXaxis()->SetRangeUser(xmin, xmax);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->GetYaxis()->SetRangeUser(ymin, ymax);
  graph->GetZaxis()->SetTitle(ztitle);
  graph->GetZaxis()->SetRangeUser(zmin, zmax);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();
  c->SaveAs(filename);

  delete graph;
}

void DrawTGraph2D(int npoints, double * x, double * y, double * z, TCanvas *c, int pad, const char *title, const char *xtitle, const char *ytitle, const char *ztitle, int marker_style, const char *DrawOption)
{
  TGraph2D * graph = new TGraph2D(npoints, x, y, z);
  c->cd(pad);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->GetZaxis()->SetTitle(ztitle);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();
}

void DrawTGraph2D(int npoints, double * x, double * y, double * z, TCanvas *c, int pad, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, const char *title, const char *xtitle, const char *ytitle, const char *ztitle, int marker_style, const char *DrawOption)
{
  TGraph2D * graph = new TGraph2D(npoints, x, y, z);
  c->cd(pad);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetXaxis()->SetRangeUser(xmin, xmax);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->GetYaxis()->SetRangeUser(ymin, ymax);
  graph->GetZaxis()->SetTitle(ztitle);
  graph->GetZaxis()->SetRangeUser(zmin, zmax);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();
}

void AddToMultiGraph(TMultiGraph * mg, int npoints, double * x, double * y, TCanvas *c, const char *title, const char *xtitle, const char *ytitle, int marker_style, const char *DrawOption)
{
  TGraph * graph = new TGraph(npoints, x, y);
  mg->Add(graph);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();
}

void AddToMultiGraph(TMultiGraph * mg, int npoints, double * x, double * y, TCanvas *c, double xmin, double xmax, double ymin, double ymax, const char *title, const char *xtitle, const char *ytitle, int marker_style, const char *DrawOption)
{
  TGraph * graph = new TGraph(npoints, x, y);
  mg->Add(graph);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetXaxis()->SetRangeUser(xmin, xmax);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->GetYaxis()->SetRangeUser(ymin, ymax);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();
}

void AddToMultiGraph(TMultiGraph * mg, int npoints, double * x, double * y, TCanvas *c, int pad, const char *title, const char *xtitle, const char *ytitle, int marker_style, const char *DrawOption)
{
  TGraph * graph = new TGraph(npoints, x, y);
  mg->Add(graph);
  c->cd(pad);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();
}

void AddToMultiGraph(TMultiGraph * mg, int npoints, double * x, double * y, TCanvas *c, int pad, double xmin, double xmax, double ymin, double ymax, const char *title, const char *xtitle, const char *ytitle, int marker_style, const char *DrawOption)
{
  TGraph * graph = new TGraph(npoints, x, y);
  mg->Add(graph);
  c->cd(pad);
  graph->SetMarkerStyle(marker_style);
  graph->SetTitle(title);
  graph->GetXaxis()->SetTitle(xtitle);
  graph->GetXaxis()->SetRangeUser(xmin, xmax);
  graph->GetYaxis()->SetTitle(ytitle);
  graph->GetYaxis()->SetRangeUser(ymin, ymax);
  graph->Draw(DrawOption);
  c->Modified();
  c->Update();
}

void DrawHistogram2D(int nbinsx, int nbinsy, double ** bincontent, double xmin, double xmax, double ymin, double ymax, TCanvas *c, const char * title, const char * xtitle, const char * ytitle, const char *filename, double line_width, Color_t color, const char *DrawOption)
{
  TH2F* histogram = new TH2F("h", title, nbinsx, xmin, xmax, nbinsy, ymin, ymax);

  for (int i = 0; i < nbinsx; i++)
  {
    for (int j = 0; j < nbinsy; j++)
          histogram->Fill(i, j, bincontent[i][j]);
  }

  histogram->GetXaxis()->SetTitle(xtitle);
  histogram->GetYaxis()->SetTitle(ytitle);

  histogram->SetLineColor(color);
  histogram->SetLineWidth(line_width);

  histogram->Draw(DrawOption);

  c->Modified();
  c->Update();
  c->SaveAs(filename);

  delete histogram;
}

void DrawHistogram2D(int nbinsx, int nbinsy, double ** bincontent, double xmin, double xmax, double ymin, double ymax, TCanvas *c, int pad, const char * title, const char * xtitle, const char * ytitle, double line_width, Color_t color, const char *DrawOption)
{
  TH2F* histogram = new TH2F("h", title, nbinsx, xmin, xmax, nbinsy, ymin, ymax);
  c->cd(pad);

  for (int i = 0; i < nbinsx; i++)
  {
    for (int j = 0; j < nbinsy; j++)
          histogram->Fill(i, j, bincontent[i][j]);
  }

  histogram->GetXaxis()->SetTitle(xtitle);
  histogram->GetYaxis()->SetTitle(ytitle);

  histogram->SetLineColor(color);
  histogram->SetLineWidth(line_width);

  histogram->Draw(DrawOption);

  c->Modified();
  c->Update();
}

int main()
{
  double * x = new double[100];
  double * y = new double[100];

  TCanvas *c = new TCanvas("c", "Teste", 0, 0, 500, 500);
  c->Divide(2, 2);

  for (int i = 0; i < 100; i++)
  {
    x[i] = i;
    y[i] = 2*cos(i*0.1)+3;
  }

  DrawTGraph(100, x, y, c, 1, "Teste");
  DrawTGraph(100, y, x, c, 2, "Teste");
  DrawTGraph(100, x, y, c, 3, "Teste");
  DrawTGraph(100, y, x, c, 4, "Teste");

  c->SaveAs("plot.eps");
  return 0;
}
