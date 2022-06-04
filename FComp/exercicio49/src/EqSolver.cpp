#include <iostream>
#include <iomanip>
#include "EqSolver.h"

using namespace std;

/*
           _____      ____        _
          | ____|__ _/ ___|  ___ | |_   _____ _ __
          |  _| / _` \___ \ / _ \| \ \ / / _ \ '__|
          | |__| (_| |___) | (_) | |\ V /  __/ |
          |_____\__, |____/ \___/|_| \_/ \___|_|
                  |_|
                                                            */

EqSolver::EqSolver() // default constructor
{
  cout << __PRETTY_FUNCTION__ << endl;
  M = FCmatrixFull();
  B = FCmatrixBanded();
  b = Vec();
}

EqSolver::EqSolver(const FCmatrixFull & A, const Vec & v) // construtor 1
{
  cout << __PRETTY_FUNCTION__ << endl;
  M = A;
  B = FCmatrixBanded();
  b = v;
}

EqSolver::EqSolver(const FCmatrixBanded & A, const Vec & v) // construtor 2
{
  cout << __PRETTY_FUNCTION__ << endl;
  M = FCmatrixFull();
  B = A;
  b = v;
}

void EqSolver::SetConstants(const Vec & rhs)
{
  b = rhs;
}

void EqSolver::SetMatrix(const FCmatrixFull& rhs)
{
  M = rhs;
}


void EqSolver::SetMatrix(const FCmatrixBanded& rhs)
{
  B = rhs;
}

Vec EqSolver::GaussEliminationSolver()
{
  int n = M.Get_nRows();
  double omega;
  Vec x(n);

    // Fase de Eliminação

    GaussElimination(M, b);

    // Fase de Substituição

    x[n - 1] = b[n - 1] / M[n - 1][n - 1];

    for (int i = n - 2; i >= 0; i--)
      {
        omega = 0;

        for (int k = i; k < n; k++) // k = i + 1?
          omega += x[k] * M[i][k];

        // cout << "omega = " << omega << endl;

        x[i] = (b[i] - omega) / (M[i][i]);
      }

    return x;
}

void EqSolver::GaussElimination (FCmatrixFull &U, Vec &c) // Transforma o sistema Ax = b em Ux = c
{
  int n = U.Get_nRows();
  double lambda;

  // A matriz é quadrada?

  if (!U.IsSquare())
    {
      cout << "A matriz não é quadrada!" << endl;
      exit(EXIT_FAILURE);
    }

  // Fase de Eliminação

  for (int i = 0; i < n - 1; i++)
  {
    // 1: Escolher um Pivot adequado em cada Linha

    int k = U.GetColMax(i);  // k é o índice da maior entrada (em módulo) em cada cada coluna


    // 2: Se a entrada k da linha é zero, então uma coluna inteira é só zeros, o que implica que A é singular e o sistema não tem solução

   if (U[i][k] == 0)
      {
        if (c[i] != 0)
          cout << "O sistema é impossível!" << endl;

        else
          cout << "O sistema é indeterminado!" << endl;

        exit(EXIT_FAILURE);
      }

    // 3: Se a entrada k da linha não é zero, troca a linha i pela linha onde está k e coloca a entrada k na diagonal principal

    if (i != k)
    {
      U.swapRows(i, k); // promove a linha i para conter o pivot
      c.Swap(i, k);    // e troca as mesmas linhas no vetor b
    }

    // 5: Verifica se o sistema não é indeterminado...

    if (U.Determinant() == 0)
      {
        cout << "O sistema é impossível ou indeterminado!" << endl;
        exit(EXIT_FAILURE);
      }

    // 6: Para j = i + 1, ..., n, faz eliminação de Gauss

    for (int j = i + 1; j < n; j++) // ou j = i +1?
      {
        lambda = U[j][i] / U[i][i];  // fator de escala
        U[j] = U[j] - U[i] * lambda; // calcula a nova linha-i
        c[j] = c[j] - c[i] * lambda; // calcula a componente índice i do vetor
      }
    }
}

FCmatrixFull * EqSolver::LUdecomposition_Doolittle(FCmatrixFull& Lit)
{
  if(Lit.IsSquare())
  {
    int n = Lit.Get_nRows();

    for (int i = 0; i < n - 1; i++)
    {

      int k = Lit.GetColMax(i);  // como na eliminação de Gauss

      if (i != k)
      {
        Lit.swapRows(i, k); //
        b.Swap(i, k);    // e troca as mesmas linhas no vetor b
      }
    }

    FCmatrixFull* LU = new FCmatrixFull[2];

    for(int i = 0; i < 2; i++)
    {
      LU[i] = Lit;  // para as dimensões serem iguais

      for(int j = 0; j < n; j++)
      {
        for(int k = 0; k < n; k++)
        {
          LU[i][j][k] = 0; // reset
        }

        LU[0][j][j] = 1;  // porque definimos |L| = 1

      }
    }

    // Triangular Superior
    for(int i = 0; i < n; i++)
    {
      for (int k = i; k < n; k++)
      {
        double sum = 0;    // Soma L(i, j) * U(j, k)


        for (int j = 0; j < i; j++)
          sum += (LU[0][i][j] * LU[1][j][k]);

        // Construção da matriz triangular superior U(i, k)
        LU[1][i][k] = Lit[i][k] - sum;

      }

       // Triangular Inferior
      for (int k = i; k < n; k++)
      {
        if (i == k)
          LU[0][i][i] = 1; // porque definimos |L| = 1

        else
        {
          double sum = 0;  // Soma L(k, j) * U(j, i)

          for (int j = 0; j < i; j++)
            sum += (LU[0][k][j] * LU[1][j][i]);

          // Construção da matriz triangular inferior L(i, k)
          LU[0][k][i] = (Lit[k][i] - sum) / LU[1][i][i];
        }
      }
    }

  return LU;
  }
}

Vec EqSolver::LUdecompositionSolver_Doolittle()
{
  FCmatrixFull* LU = LUdecomposition_Doolittle(M);
  double omega;
  int n = b.Size();
  Vec y(n);

  y[0] = b[0];

  for(int i = 1; i < n; i++)
  {
    omega = 0;

    for(int k = 0; k < i; k++)
      omega += LU[0][i][k]*y[k];

    y[i] = b[i] - omega;
  }

  Vec x(n);

  x[n-1] = y[n-1] / LU[1][n-1][n-1];

  for(int i = n-2; i >= 0; i--)
  {
    omega = 0;

    for(int k = n-1; k > i; k--)
      omega += LU[1][i][k] * x[k];

    x[i] = (y[i] - omega) / LU[1][i][i];
  }

  delete[] LU;
  return x;
}

Vec EqSolver::TridiagonalSolver()
{
  Vec x (B.Get_nRows());
  x = TridiagonalThomas(B,b);
  return x;
}

Vec EqSolver::TridiagonalThomas(FCmatrixBanded &A, Vec &b)
{
  int n = A.Get_nRows(); // = Get_nCols(), a matriz é quadrada
  Vec x (n);

  if(n == 1)
  {
    Vec v(1, b[0]/A[0][0]);
    return v;
  }

  // 1: A matriz fica triangular superior com 1s na diagonal principal

   A[0][0] /= A[1][0];
   b[0] /= A[1][0];

   for (int i = 1; i < n-1; i++)
   {
       A[0][i] /= (A[1][i] - A[2][i - 1] * A[0][i-1]);
       b[i] = (b[i] - A[2][i - 1] * b[i-1]) / (A[1][i] - A[2][i - 1] * A[0][i-1]);
   }

   b[n - 1] = (b[n - 1] - A[2][n - 2] * b[n-2]) / (A[1][n - 1] - A[2][n - 2] * A[0][n - 2]);

  for (int i = 0; i < n-1; i++)
  {
    A[1][i] = 1;
    A[2][i] = 0;
  }
  A[1][n-1] = 1;


   // 2: A partir deste novo sistema, obtém-se a solução

   x [n - 1] = b[n - 1];

   for (int i = n - 2; i >= 0; i--)
   {
       x[i] = b[i] - A[0][i] * x[i+1];
   }

   return x;
 }

void EqSolver::Print()
{
  vector<Vec> mx = M.GetM();
  int n = mx.size();



  /*for (int i = 0; i < n; i++)
    cout << setw(6) << setprecision(4) << mx.at(0).GetEntries()[i] << " ";

  cout << "   |";

  cout << setw(3) << b[0] << " |" << endl;*/

  for(int i = 0; i < n; i++)
  {
    cout << "| ";

    for (int j = 0; j < n; j++)
      cout << setw(6) << setprecision(4) << mx.at(i).GetEntries()[j] << " ";

    //cout << " |  ";
    cout << "| " << setw(3) << b[i] << " |" << endl;
  }
}

void EqSolver::PrintB()
{
  int n = B.Get_nCols();

/*  cout << "| ";

  for (int i = 0; i < n; i++)
    cout << setw(6) << setprecision(3) << B.GetRow(0)[i] << " ";

  cout << "| " << setw(6) << setprecision(3) << b[0] << " |" << endl;*/

  for(int i = 0; i < n; i++)
  {
    cout << "| ";

    for (int j = 0; j < n; j++)
      cout << setw(6) << setprecision(3) << B.GetRow(i)[j] << " ";

  //  cout << " | ";
    cout << "| " << setw(6) << setprecision(3) << b[i] << " |" << endl;
  }
}
