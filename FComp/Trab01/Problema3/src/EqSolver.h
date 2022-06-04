#ifndef H_EQSOLVER_H
#define H_EQSOLVER_H

#include "vec.h"
#include "FCmatrix.h"
#include "FCmatrixFull.h"
#include "FCmatrixBanded.h"

using namespace std;

/* A classe EqSolver permite resolver um sistema de equações lineares usando diversos métodos. */

class EqSolver {

  public:
    // construtores
    EqSolver(); // default
    EqSolver(const FCmatrixFull&, const Vec&);   // recebe a matriz M e um vetor de constantes
    EqSolver(const FCmatrixBanded&, const Vec&); // recebe a matriz B e um vetor de constantes
    // set
    void SetConstants(const Vec&); // define as entradas um vetor de constantes (b)
    void SetMatrix(const FCmatrixFull&); // define as entradas da matriz M
    void SetMatrix(const FCmatrixBanded&); // define as entradas da matriz B
    // resolucao
    Vec GaussEliminationSolver(); // resolução do sistema pelo método de eliminação de Gauss
    Vec LUdecompositionSolver_Doolittle(); // resolução do sistema pelo metodo Doolittle LU (M = LU)
    Vec TridiagonalSolver(); // resolve um sistema tridiagonal pelo metodo de Thomas
    void Print();  // imprime o sistema Mx = b
    void PrintB(); // imprime o sistema Bx = b

    private:
      void GaussElimination(FCmatrixFull&, Vec&); // retorna uma matriz triangular superior e o vetor de constantes alterado
      FCmatrixFull * LUdecomposition_Doolittle(FCmatrixFull&); // decomposição Doolittle LU com |L|=1
      Vec TridiagonalThomas(FCmatrixBanded &, Vec &); // resolve um sistema tridiagonal pelo metodo de Thomas
      FCmatrixFull M; // matriz de coeficientes (FCmatrixFull)
      FCmatrixBanded B; // matriz de coeficientes tridiagonal (FCmatrixBanded)
      Vec b; // vetor de constantes
  };

#endif
