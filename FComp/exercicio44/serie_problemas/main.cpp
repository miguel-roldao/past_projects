#include <iostream>
#include "EqSolver.h"

using namespace std;

int main()
{
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


    E1[0][0] = 0;
    E1[0][1] = 1;
    E1[0][2] = 2;
    E1[0][3] = 1;
    E1[1][0] = 1;
    E1[1][1] = 2;
    E1[1][2] = 1;
    E1[1][3] = 0;
    E1[2][0] = 0.02;
    E1[2][1] = 0.01;
    E1[2][2] = 0;
    E1[2][3] = 0;
    E1[3][0] = 0;
    E1[3][1] = 0;
    E1[3][2] = 100;
    E1[3][3] = 200;

  // build objects
  FCmatrixFull A(E1, 4, 4);

  for (int i = 0; i < 3; i++)
    {
      delete[] E1[i];
    }

    delete[] E1;

  double x[]={0.02, 1, 4, 800};
  Vec l(4,x); //array with 5 values given by "a" pointer

  EqSolver Eq(A, l);

  cout << endl << "A solução com Eliminação de Gauss é: " << endl;

  Eq.GaussEliminationSolver().Print();

  double *b;
  b = new double [3];

  b[0] = 11;
  b[1] = -16;
  b[2] = 17;

  Vec vb (3, b);

  delete[] b;

  EqSolver J(ME, vb);
  J.Print();
  cout<<"\nV = ";



  cout << endl << "A solução com Eliminação de Gauss é" << endl;

  J.GaussEliminationSolver().Print();

  cout << "A solução com Doolittle é" << endl;

  J.LUdecompositionSolver_Doolittle().Print();

  E = new double*[3];

  for (int i = 0; i < 3; i++)
    E[i] = new double[3];


  E[0][0] = 2;
  E[0][1] = -2;
  E[0][2] = 6;
  E[1][0] = -2;
  E[1][1] = 4;
  E[1][2] = 3;
  E[2][0] = -1;
  E[2][1] = 8;
  E[2][2] = 4;

  FCmatrixFull MF(E, 3, 3);

  for (int i = 0; i < 3; i++)
  {
    delete[] E[i];
  }

  delete[] E;

  b = new double [3];

  b[0] = 16;
  b[1] = 0;
  b[2] = -1;

  vb.SetEntries (3, b);

  delete[] b;

  J.SetMatrix(MF);
  J.SetConstants(vb);

  cout<<endl;

  J.Print();
  cout<<"\nV = ";

  cout << "A solução com Doolittle é" << endl;

  J.LUdecompositionSolver_Doolittle().Print();

  cout << endl << "A solução com Eliminação de Gauss é" << endl;

  J.GaussEliminationSolver().Print();
  double** T = new double*[3];

  for(int i = 0; i < 3; i++)
    {
      T[i] = new double[5];
    }

  for(int j = 0; j < 5; j++)
    {
      T[0][j] = 1;
      T[1][j] = -2;
      T[2][j] = 1;
    }

  FCmatrixBanded MT(T, 5, 5);

  J.SetMatrix(MT);

  b = new double[5];

  b[0] = 1;
  b[1] = 2;
  b[2] = 3;
  b[3] = 4;
  b[4] = 5;

  vb.SetEntries(5, b);

  J.SetConstants(vb);

  for(int i = 0; i < 3; i++)
    delete[] T[i];

  delete[] T;

  delete[] b;
  cout << "Matriz Tridiagonal:" << endl;
  J.PrintB();
  cout << "V = ";
  J.TridiagonalSolver().Print();

  return 0;
}
