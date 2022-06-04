#include <iostream>
#include "src/EqSolver.h"

using namespace std;

int main()
{
  // Para testar se é possível resolver por eliminação de Gauss sem pivotagem, comentar as linhas 122-126 de EqSolver.cpp
  // Verifica-se que é impossível (retorna um vetor de -nan)

  double ** E;
  E = new double*[3];

  for (int i = 0; i < 3; i++)
    E[i] = new double[3];


    E[0][0] = 0;
    E[0][1] = 1;
    E[0][2] = 0;
    E[1][0] = 2;
    E[1][1] = 0;
    E[1][2] = 0;
    E[2][0] = 0;
    E[2][1] = 0;
    E[2][2] = 4;

// build objects
FCmatrixFull ME(E, 3, 3);

  for (int i = 0; i < 3; i++)
  {
    delete[] E[i];
  }

  delete[] E;

  double ** E1;
  E1 = new double*[4];

  for (int i = 0; i < 4; i++)
    E1[i] = new double[4];


    E1[0][0] = 4;
    E1[0][1] = -2;
    E1[0][2] = 2;
    E1[0][3] = 2;
    E1[1][0] = -2;
    E1[1][1] = 1;
    E1[1][2] = 3;
    E1[1][3] = 1;
    E1[2][0] = 2;
    E1[2][1] = -2;
    E1[2][2] = 2;
    E1[2][3] = 1;
    E1[3][0] = 2;
    E1[3][1] = -1;
    E1[3][2] = 2;
    E1[3][3] = 1;

  // build objects
  FCmatrixFull A(E1, 4, 4);

  for (int i = 0; i < 3; i++)
    {
      delete[] E1[i];
    }

    delete[] E1;

  double x[]={-2, 1, 0, 2};
  Vec l(4,x); //array with 5 values given by "a" pointer

  EqSolver Eq(A, l);

  cout << endl << "A solução com Eliminação de Gauss é: " << endl;

  Eq.GaussEliminationSolver().Print();

  cout << "A solução com Doolittle é" << endl;

  Eq.LUdecompositionSolver_Doolittle().Print();

  return 0;

}
