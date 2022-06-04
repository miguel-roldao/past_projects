#ifndef H_PIC_H
#define H_PIC_H

#include <iostream>
#include <cmath>
#include <vector>
#include "ODEpoint.h"
#include "ODEsolver.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TFormula.h"
#include "TStyle.h"
#include "TApplication.h"
#include "Vec.h"
#include "FCmatrixBanded.h"
#include "EqSolver.h"
#include "Spline3Interpolator.h"
#include "TF1.h"
#include "TRandom3.h"
#include "ODEpoint.h"

/*  A classe PIC permite evoluir no tempo a posição e velocidade de um ensemble de partículas de dimensão N
    com uma dada distribuição de velocidade e um conjunto de condiçẽos fronteira especificados.           */

class PIC {
  public:
    PIC(std::vector<double> velocity, int Npart = 1000, double xmin = 0.0, double xmax = 1.0, int ngrid = 100);  // construtor
    ~PIC(); // destructor
    // distribuição inicial de velocidades
    void FdistV(vector<double> veloc, bool save_plot = true, bool show_plot = false);
    // espaço de fases
    void Plot_Phase_Space(bool save_plot = true, bool show_plot = false);
    // cálculo do perfil de densidade na grelha espacial
    void Density(bool save_plot = true, bool show_plot = false);
    // cálculo do potencial na grelha espacial
    void Poisson(bool save_plot = true, bool show_plot = false);
    // avanço no tempo de todas as partículas
    void TimeStep(double dt);
    // discretiza o domínio espacial
    void SetGrid();
    // impõe as condições fronteira
    void CheckBoundaries();
    // retorna o tempo atual de simulação (unidades normalizadas)
    double GetTime() {return t;}
    PIC & operator= (const PIC &rhs); // assignement operator

  private:
    std::vector<double> velocity;  // vector com a velocidade dos 2 beams (positivo e negativo)
    int Npart;                     // = 1000: número total de partículas
    double xmin;                   // = 0.0 início do domínio espacial que contém as partículas
    double xmax;                   // = 1.0: fim do domínio espacial que contém as partículas
    int ngrid;                     // = 100: numero de pontos da grelha espacial onde calcular a densidade e potencial.
    double n0;                     // densidade média
    double * r;                    // array com a posição dos Npart eletrões
    double * v;                    // array com a velocidade dos Npart eletrões
    double* xgrid;                 // coordenadas da grelha (de xmin a xmax)
    double* density;               // densidade de partículas na grelha espacial
    double* potential;             // potencial elétrico a grelha espacial
    double* Efield;                // campo elétrico para as N partículas
    void Eletric_Effect(double dt);// calcula o campo elétrico, as novas velocidades e posições
    std::vector<TFormula> TF;      // vetor de TFormulas usadas nas equações diferenciais
    std::vector<ODEpoint> sol;     // vetor-solução da ODE que permite calcular a posicao e velocidade
    double t;                      // tempo atual de simulação
    static bool HasDrawnAnyPlots;  // para decidir se cria uma TApplication

};

#endif
