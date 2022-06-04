#include "PIC.h"
#define PI atan(1) * 4

/*
       _____           _   _      _        _____          _____     _ _
      |  __ \         | | (_)    | |      |_   _|        / ____|   | | |
      | |__) |_ _ _ __| |_ _  ___| | ___    | |  _ __   | |     ___| | |
      |  ___/ _` | '__| __| |/ __| |/ _ \   | | | '_ \  | |    / _ \ | |
      | |  | (_| | |  | |_| | (__| |  __/  _| |_| | | | | |___|  __/ | |
      |_|   \__,_|_|   \__|_|\___|_|\___| |_____|_| |_|  \_____\___|_|_|

      IMPORTANTE:

          1. Se usar dt < 0.01, mudar a precisão do número de casas decimais nas
          variavéis 'filename' para que os ficheiros não sejam substituídos.
*/

using namespace std;

// inicialização da variável estática
bool PIC::HasDrawnAnyPlots = false;

PIC::PIC(vector<double> vel, int N, double min, double max, int grid) // construtor
{
  velocity = vel;
  Npart = N;
  xmin = min;
  xmax = max;
  ngrid = grid;
  r = new double[Npart];
  xgrid = new double[ngrid+1];
  density = new double[ngrid+1];
  potential = new double[ngrid+1];
  Efield = new double [Npart];
  v = new double [Npart];
  t = 0;

  SetGrid();

  // x[0] = t; x[1] = r; x[2] = v; x[3]= E;
  TFormula* dr_dt = new TFormula("dr_dt","0*x[0]*x[1] + x[2] + 0*x[3]");
  TF.push_back(*dr_dt);

  TFormula* dr2_dt2 = new TFormula("dr2_dt2","0*x[0]*x[1]*x[2] - x[3]");
  TF.push_back(*dr2_dt2);

  TFormula* dE_dt = new TFormula("dE_dt","0*x[0] * x[1] * x[2]*x[3]");
  TF.push_back(*dE_dt);

  // Densidade Média
  n0 = (double) Npart / (xmax - xmin);
}

PIC::~PIC() // destrutor
{
  delete[] xgrid;
  delete[] density;
  delete[] potential;
  delete[] Efield;
  delete[] v;
  delete[] r;
}

void PIC::SetGrid() // discretiza a grelha espacial
{
  for (int i = 0; i < ngrid+1; i++)
    xgrid[i] = xmin + (xmax - xmin) * (double) i / (double) ngrid;
}

void PIC::FdistV(vector<double> veloc, bool save_plot, bool show_plot)
{
  TRandom3 rgen(0); // garante que a semente é única

  // Parâmetros dos Gráficos
  double vmax  = 10;
  double nbins = 100;

  // Gera Npart eletrões com posição r[i], i = 0, ..., Npart - 1
  for (int i = 0; i < Npart; i++)
     r[i] = xmin + (xmax - xmin) * rgen.Uniform(0,1);

  // A TApplication tem de ser inicializada antes da Canvas!
  if(show_plot && !HasDrawnAnyPlots)
    {
      TApplication * MyRootApp;
      MyRootApp = new TApplication("Phys. Comp.", NULL, NULL);
      MyRootApp->SetReturnFromRun(true);
      HasDrawnAnyPlots = true;
    }

  // Cria o canvas para a distribuição real e analítica
  gStyle->SetOptStat(0); // esconde a estatística
  TCanvas *c = new TCanvas("chistogram", "Velocity", 0, 0, 500, 500);
  TH1F* histogram = new TH1F("h", "F (v)", nbins, -vmax, vmax);

  bool VelocityParameter;

  // Método de Aceitação-Rejeição
  for (int j = 0; j < Npart; j++)
  {
    if (rgen.Uniform(0,1) > 0.5)
      VelocityParameter = true;

    else
      VelocityParameter = false;

    // Método de Box–Muller
    v[j] = sqrt(-2*log(rgen.Uniform(0,1)))*cos(2*PI*rgen.Uniform(0,1)) + veloc[VelocityParameter];
    histogram->Fill(v[j]);
  }

  // Estética (Histograma da Distribuição de Velocidades)
  histogram->GetXaxis()->SetTitle("v");
  histogram->SetLineColor(kBlue);
  histogram->SetLineWidth(1.2);

  // Normaliza a escala (só funciona com .eps por razões misteriosas!)
  Double_t norm = Npart;
  histogram->Scale(1/norm, "height");

  // Desenha o histograma
  histogram->Draw("HIST3");
  c->Modified();
  c->cd();
  c->SetSelected(c);

  // Mostra a distribuição real (se show_plot)
  if(show_plot)
    {
        c->Update();
        gPad->WaitPrimitive();
    }

  // Cria o canvas e a função de distribuição analítica de velocidades
  TCanvas *d = new TCanvas("canalytical", "Analytical Velocity Distribution", 0, 0, 500, 500);
  TF1* PDF = new TF1("Distribution", "1/sqrt(8*pi)*(exp(-(x-[0])*(x-[0])/2) + exp(-(x+[1])*(x+[1])/2))", -vmax, vmax);

  // Desenha a distribuição analítica
  PDF->SetParameters(veloc[0], -veloc[1]);
  PDF->Draw();
  d->Modified();
  d->cd();
  d->SetSelected(d);

  // Mostra a distribuição analítica (se show_plot)
  if(show_plot)
    {
        d->Update();
        gPad->WaitPrimitive();
    }

  // Grava os plots (se save_plot)
  if (save_plot)
  {
    c->SaveAs("../Velocity_Distribution.eps");
    d->SaveAs("../Analytical_Velocity_Distribution.eps");
  }

  delete c;
  delete d;
}

void PIC::Plot_Phase_Space(bool save_plot, bool show_plot)
{
  // Cria a TApplication (se necessário)
  if(show_plot && !HasDrawnAnyPlots)
  {
    TApplication * MyRootApp;
    MyRootApp = new TApplication("Phys. Comp.", NULL, NULL);
    MyRootApp->SetReturnFromRun(true);
    HasDrawnAnyPlots = true;
  }

  // O nome do TCanvas deve ser único!
  char canvas_name[100];
  sprintf(canvas_name, "cphasespace%.2lf", t);

  // Desenha o Espaço de Fases
  TCanvas *c = new TCanvas(canvas_name, "Phase Space", 0, 0, 500, 500);
  TGraph * phase_space = new TGraph(Npart, r, v);

  // Estética e Títulos dos Eixos/Gráfico
  phase_space->SetMarkerStyle(6); // '6' = small dot
  phase_space->SetTitle("Phase Space");
  phase_space->GetXaxis()->SetTitle("Position (x)");
  phase_space->GetXaxis()->SetRangeUser(xmin, xmax);
  phase_space->GetYaxis()->SetTitle("Velocity (v)");
  phase_space->GetYaxis()->SetRangeUser(3 * velocity.at(0), 3 * velocity.at(1));
  phase_space->Draw("AP");
  c->Modified();

  // Mostra-o
  if(show_plot)
  {
    c->Update();
    gPad->WaitPrimitive();
  }

  // O novo do ficheiro deve ser único
  char filename[100];
  sprintf(filename, "../Phase_Space_t=%.2lf_L=%.1lf.png", t, xmax-xmin);

  // Grava o ficheiro
  if (save_plot)
    c->SaveAs(filename);

  delete c;
}

void PIC::Density(bool save_plot, bool show_plot)
{
  // Espaçamento entre Células
  double h = (xmax - xmin) / ngrid; // = x(j+1) - x(j)
  int nbins = (ngrid + 1) / 10;

  // Para quando calcular novamente
  for (int k = 0; k < ngrid+1; k++)
  {
    density[k] = 0;
  }

  // Calcula a densidade eletrónica na grelha
  for (int i = 0; i < Npart; i++)
  {
    if(r[i] <= xgrid[1])
      density[ngrid] += (xgrid[1] - r[i]) / (h * h);

    if(r[i] >= xgrid[ngrid-1])
      density[0] += (r[i] - xgrid[ngrid-1]) / (h * h);

    for (int j = 0; j < ngrid; j++)
    {
      if (xgrid[j] <= r[i] && xgrid[j+1] >= r[i])
      {
        density[j] += (xgrid[j+1] - r[i]) / (h * h);
        density[j+1] += (r[i] - xgrid[j]) / (h * h);
        break;
      }
    }
  }

  // Normalização
  for (int k = 0; k < ngrid + 1; k++)
    density[k] /= n0;

  // Cria a TApplication (se necessário)
  if(show_plot && !HasDrawnAnyPlots)
    {
      TApplication * MyRootApp;
      MyRootApp = new TApplication("Phys. Comp.", NULL, NULL);
      MyRootApp->SetReturnFromRun(true);
      HasDrawnAnyPlots = true;
    }

  // O nome do canvas deve ser único!
  char name[100];
  sprintf(name, "histdensity_t=%.2lf", t);

  // Esconde a estatística e cria o canvas e o histograma
  gStyle->SetOptStat(0);
  TCanvas *c = new TCanvas(name, "Density", 0, 0, 500, 500);
  TH1F* histogram = new TH1F(name, "Densidade", nbins, xmin, xmax);

  double sum = 0;

  if(ngrid % nbins != 0)
  {
    cout << "\n *Warning: nbins não é multiplo de ngrid!*\n"<<endl;

    nbins -= ngrid % nbins;
  }

  int binwidth = ngrid / nbins;  //divisão inteira.

  // Preenche o histograma
  for (int j = 0, k = 0; j < ngrid+1; j++)
  {
    sum += density[j] - 1;

    if(j % binwidth == 0)
    {
      sum /= binwidth;   // densidade média
      histogram->SetBinContent(k, sum);
      sum = 0;
      k++;
    }
  }

  // Estética do histograma
  histogram->GetXaxis()->SetTitle("x");
  histogram->GetXaxis()->SetRangeUser(xmin, xmax);
  histogram->GetYaxis()->SetRangeUser(-1, 1);
  histogram->SetLineColor(kRed);
  histogram->SetLineWidth(2.0);

  // Desenha o histograma
  histogram->Draw("HIST3");

  c->Modified();
  c->cd();
  c->SetSelected(c);

  // Mostra-o (se show_plot)
  if(show_plot)
  {
    c->Update();
    gPad->WaitPrimitive();
  }

  // Guarda o ficheiro
  char filename[100];
  sprintf(filename, "../Density_t=%.2lf.png", t);

  if (save_plot)
    c->SaveAs(filename);

  delete c;
}

void PIC::Eletric_Effect(double dt) // calcula o campo elétrico, as novas velocidades e posições
{
  ODEsolver Eletric(TF);

  for(int i = 0; i < Npart; i++)
  {
    double init[] = {r[i], v[i], Efield[i]};  // condicoes iniciais de i {posicao, velocidade, campo}
    ODEpoint r0(t, init, 3);                  // apesar de não depender do tempo

    sol = Eletric.RK4solver(r0,t,t+dt,dt);
    r[i] = sol.back().Get_Var_ptr()[0];
    v[i] = sol.back().Get_Var_ptr()[1];
  }
}

void PIC::Poisson(bool save_plot, bool show_plot)
{
  double h = (xmax - xmin) / ngrid;

  Vec UD(ngrid, 1. / (h*h));  // 'UD' = Upper Diagonal
  Vec MD(ngrid + 1,     -2. / (h*h)); // 'MD' = Main Diagonal
  Vec LD(ngrid, 1. / (h*h));  // 'LD' = Lower Diagonal
  Vec b (ngrid + 1,     0.);          // Vetor (matriz aumentada)

  for (int j = 1; j < ngrid; j++)
  {
    b[j] = density[j] - 1;
  }

  // Condições Fronteira
  // b[0] = b[ngrid] = 0 -> implícito no construtor

  FCmatrixBanded M(UD, MD, LD);
  EqSolver P(M, b);

  double * raichu = P.TridiagonalSolver().GetEntries();

  for (int k = 0; k < ngrid+1; k++)
    potential[k] =  raichu[k];

  // Usa o Spline3Interpolator para calcular a derivada do potencial
  Spline3Interpolator spl(ngrid+1, xgrid, potential);
  TF1* pikachu = spl.GetDeriv1InterpolFunction();

  // Calcula o campo
  for(int k = 0; k < Npart; k++)
    Efield[k] = - (pikachu->Eval(r[k]));

  // Cria a TApplication (se necessário)
  if(show_plot && !HasDrawnAnyPlots)
    {
      TApplication * MyRootApp;
      MyRootApp = new TApplication("Phys. Comp.", NULL, NULL);
      MyRootApp->SetReturnFromRun(true);
      HasDrawnAnyPlots = true;
    }

  // Os canvas devem ter nomes diferentes!
  char name[100];
  sprintf(name, "../cpoisson_t=%.2lf", t);

  gStyle->SetOptStat(0); // esconde a estatística do histogramas

  // Cria o canvas e o histograma
  TCanvas *c = new TCanvas(name, "Potential", 0, 0, 500, 500);
  TH1F* histogram = new TH1F(name, "Potential", ngrid + 1, xmin, xmax);

  // Preenche o histograma
  for (int j = 0; j < ngrid + 1; j++)
  {
    histogram->SetBinContent(j, potential[j]);
  }

  // Estética do histograma
  histogram->GetXaxis()->SetTitle("x");
  histogram->GetYaxis()->SetTitle("Potential");
  histogram->SetLineColor(kRed);
  histogram->SetLineWidth(2);

  // Desenha o histograma
  histogram->Draw("L");

  c->Modified();
  c->cd();
  c->SetSelected(c);

  // Mostra-o (se show_plot)
  if(show_plot)
  {
    c->Update();
    gPad->WaitPrimitive();
  }

  // Grava o ficheiro
  char filename[100];
  sprintf(filename, "../Potential_t=%.2lf.png", t);

  if (save_plot)
    c->SaveAs(filename);

  raichu = NULL;

  delete c;

}

void PIC::CheckBoundaries() // condições fronteira (cíclicas) para a posição
{
  double L = xmax - xmin;

  for (int i = 0; i < Npart; i++)
  {
    if (r[i] > xmax)
      r[i] -= L;

    if (r[i] < xmin)
      r[i] += L;
  }
}

void PIC::TimeStep(double dt)   // avança a simulação no tempo
{
  Eletric_Effect(dt);
  CheckBoundaries();
  t += dt;
}

PIC &PIC::operator= (const PIC & rhs)
{

  if (this != &rhs) // protege contra self-assignment inválido
    {
      velocity = rhs.velocity;
      TF = rhs.TF;
      sol = rhs.sol;
      Npart = rhs.Npart;
      xmin = rhs.xmin;
      xmax = rhs.xmax;
      ngrid = rhs.ngrid;
      n0 = rhs.n0;
      t = rhs.t;
      HasDrawnAnyPlots = rhs.HasDrawnAnyPlots;
      double* new_r = new double[Npart];
      double* new_v = new double[Npart];
      double* new_xgrid = new double[ngrid];
      double* new_density = new double[ngrid];
      double* new_potential = new double[ngrid];
      double* new_Efield = new double [Npart];


      for(int i = 0; i < Npart; i++)
      {
        new_r[i] = rhs.r[i];
        new_v[i] = rhs.v[i];
        new_xgrid[i] = rhs.xgrid[i];
        new_density[i] = rhs.density[i];
        new_potential[i] = rhs.potential[i];
        new_Efield[i] = rhs.Efield[i];
      }

      r = new_r;
      v = new_v;
      xgrid = new_xgrid;
      density = new_density;
      potential = new_potential;
      Efield = new_Efield;

      delete[] new_r;
      delete[] new_v;
      delete[] new_xgrid;
      delete[] new_density;
      delete[] new_potential;
      delete[] new_Efield;

    }

    return *this;
}
