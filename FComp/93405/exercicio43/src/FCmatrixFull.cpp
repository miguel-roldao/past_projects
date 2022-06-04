#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "FCmatrixFull.h"

using namespace std;

FCmatrixFull::FCmatrixFull() // default constructor
{
  //M; // 'construtor' para um vetor vazio?

  classname = "FCmatrixFull";
}

FCmatrixFull::FCmatrixFull(double** fM, int fm, int fn)
{
  Vec v(fn, 0.1);

  for (int i = 0; i < fm; i++)
    {
      v.SetEntries(fn, fM[i]);
      M.push_back(v);
    }
  //delete[] v.GetEntries();

  classname = "FCmatrixFull";
}

FCmatrixFull::FCmatrixFull(double* fM, int fm, int fn)
{
  double ** matrix;
  matrix = new double *[fm];

  for (int i = 0; i < fm; i++)
    {
      matrix[i] = new double [fn];

      for (int j = 0; j < fn; j++)
        matrix[i][j] = fM[j+i*fn];

    }

  for (int i = 0; i < fm; i++)
    {
      M.push_back(Vec(fn, matrix[i]));
      delete[] matrix[i]; // ver se é assim
    }


  delete[] matrix; // ou devia igual a NULL

  //matrix = NULL;

  classname = "FCmatrixFull";
}

FCmatrixFull::FCmatrixFull(vector<Vec> v) // copy constructor
{
  M = v;

  classname = "FCmatrixFull";
}

FCmatrixFull::FCmatrixFull(const FCmatrixFull& rhs) // copy construtor 2
{
  M = rhs.GetM();

  classname = "FCmatrixFull";
}

FCmatrixFull &FCmatrixFull::operator= (const FCmatrix & rhs)
{

  if (rhs.GetClassName() == "FCmatrixFull")
  {

    if (this != &rhs) // protege contra self-assignment inválido
      {

        // 1: Apaga o vetor antigo
        M.clear();

        // 2: Copia os valores do vetor antigo
        for (int i = 0; i < rhs.Get_nRows(); i++)
            M.push_back(rhs.GetM()[i]);

      }
  }

  else
  {
    cout << "ERRO: Conversão incorreta de uma FCmatrixBanded em FCmatrixFull" << endl; // feature, not a bug
    exit(EXIT_FAILURE);
  }

    return *this;

}

FCmatrixFull FCmatrixFull::operator+(const FCmatrix & rhs) const
{

  FCmatrixFull result;

  if (rhs.GetClassName() == "FCmatrixFull")
    {
      if (M.size() == rhs.Get_nRows())
        {
          if (M[0].Size() == rhs.Get_nCols()) // todos os vecs têm o mesmo tamanho; basta comparar o primeiro
            {
              for (int i = 0; i < rhs.Get_nRows(); i++)
                result.M.push_back(M[i] + rhs.GetRow(i)); // soma de vecs
            }

            else
                {
                    cout << "As matrizes não têm o mesmo tamanho; é impossível somá-las!" << endl;
                    exit (EXIT_FAILURE);
                }
            }
        }

    else if (rhs.GetClassName() == "FCmatrixBanded")
      {
        cout << "Uma FCmatrixFull está a ser somada a uma FCmatrixBanded; provavelmente, não quer fazer isto." << endl;
        exit (EXIT_FAILURE);
      }

  return result;

}

FCmatrixFull FCmatrixFull::operator-(const FCmatrix & rhs) const
{

  FCmatrixFull result;

  if (rhs.GetClassName() == "FCmatrixFull")
    {
      if (M.size() == rhs.Get_nRows())
        {
          if (M[0].Size() == rhs.Get_nCols()) // todos os vecs têm o mesmo tamanho; basta comparar o primeiro
            {
              for (int i = 0; i < rhs.Get_nRows(); i++)
                result.M.push_back(M[i] - rhs.GetRow(i)); // soma de vecs
            }

            else
                {
                    cout << "As matrizes não têm o mesmo tamanho; é impossível subtrair uma à outra!" << endl;
                    exit (EXIT_FAILURE);
                }
            }
        }

    else if (rhs.GetClassName() == "FCmatrixBanded")
      {
        cout << "Uma FCmatrixBanded está a ser subtraída a uma FCmatrixFull; provavelmente, não quer fazer isto." << endl;
        exit (EXIT_FAILURE);
      }

  return result;

}

FCmatrixFull FCmatrixFull::operator*(double lambda) const
{

  FCmatrixFull result;

  for (int i = 0; i < M.size(); i++)
      result.M.push_back(M[i]*lambda); // multiplica cada vec por uma constante

  return result;

}

Vec FCmatrixFull::operator*(const Vec &rhs) const
{
  double *column;
  int n = rhs.Size();
  column = new double[n];

  if (M.size() == n)
    {
      for (int i = 0; i < n; i++)
        column[i] = M[i].dot(rhs);
    }

  else
    {
      cout << "As matriz e o vetor não têm dimensões compatíveis; é impossível multiplicá-los!" << endl;
      exit (EXIT_FAILURE);
    }

  Vec result(n, column);

  delete[] column;

  return result;
}

FCmatrixFull FCmatrixFull::operator*(const FCmatrix & rhs) const
{

  FCmatrixFull result;

  int m = Get_nRows();
  int n = Get_nCols();
  int p = rhs.Get_nRows();
  int q = rhs.Get_nCols();
  double *d;
  d = new double[q];
  Vec row(q, d);

  if (rhs.GetClassName() == "FCmatrixFull")
  {
    if (n == p) // o número de colunas da primeira tem de ser igual ao número de linhas da segunda
    {
      for (int i = 0; i < m; i++) // cij = row i column j
      {
      //  row = new double[m];
        for (int j = 0; j < q; j++)
        {
          row[j] = GetRow(i).dot(rhs.GetCol(j));
        }

        result.M.push_back(row);
      }
    }

    else
    {
      cout << "As matrizes não têm dimensões compatíveis; é impossível multiplicá-las!" << endl;
      delete[] d;
      exit (EXIT_FAILURE);
    }
  }

  else if (rhs.GetClassName() == "FCmatrixBanded")
  {
    cout << "Uma FCmatrixBanded está a multiplicada por uma FCmatrixFull; provavelmente, não quer fazer isto." << endl;
    delete[] d;
    exit (EXIT_FAILURE);
  }

  delete[] d;

  return result;
}

void FCmatrixFull::swapRows(int i, int j)
{
  Vec swap = M[i];
  M[i] = M[j]; // troca a linha i com a linha j
  M[j] = swap; // troca a linha j com a cópia da linha i
}

Vec & FCmatrixFull::operator[] (int i)
{
  return M[i];
}

int FCmatrixFull::Get_nRows() const
{
  return M.size();
}

int FCmatrixFull::Get_nCols() const
{
  return M[0].Size();
}

Vec FCmatrixFull::GetRow(int i) const
{
  if (i > Get_nRows())
    {
      cout << "A coluna a que está a tentar aceder não existe!" << endl;
      exit(EXIT_FAILURE);
    }

  return M[i];
}

Vec FCmatrixFull::GetCol(int i) const
{
  int n = M.size();
  Vec v(n);

  if (i > n)
    {
      cout << "A coluna a que está a tentar aceder não existe!" << endl;
      exit(EXIT_FAILURE);
    }

  for (int j = 0; j < n; j++)
    v[j] = M[j][i];

  return v;
}


double FCmatrixFull::Determinant() const
{

  double det = 0;

  int m = Get_nRows();
  int n = Get_nCols();

  if (n == 1 && m == 1) // caso trivial
    return M.at(0)[0];

  vector <Vec> cofactors;
  Vec co_row;

  int sgn = 1;  // sgn()

  if (m == n)
  {
    if (n == 2)
      det = M.at(0)[0] * M.at(1)[1] - M.at(0)[1] * M.at(1)[0]; // trivial 2 x 2

    else

    {
      for(int i = 0; i < n; i++)
      {
        if (M.at(0)[i] == 0)  // evita calcular matrizes cofatores desnecessárias
        {
          if (i < n-1)
          {
            i++;
            sgn *= -1;
          }

          else
            break;
        }

        double* p = new double[n-1];  // no segmentation fault

        for(int j = 1; j < m; j++)
        {
          for(int k = 0, t = 0; k < n; k++, t++)
          {
            if(k == i)
              k++;

            p[t] = (M.at(j))[k];
          }

          co_row.SetEntries(n-1, p);

          cofactors.push_back(co_row);
        }

        delete[] p;

        FCmatrixFull mx (cofactors); //matriz dos cofatores

        cofactors.clear();

        det += sgn * M.at(0)[i] * mx.Determinant();
        sgn *= -1; // alterna sinal

      }
    }
  }

  else
  {
    cout << "A matriz não é quadrada! O determinante não está definido!" << endl;
    exit(EXIT_FAILURE);
  }

  return det;
}


int FCmatrixFull::GetRowMax(int i) const
{
  Vec v = GetRow(i);
  double max = v[0];
  int max_i = 0;

  for (int j = 0; j < Get_nRows(); j++)
  {
    if(fabs(v[j]) > fabs(v[0]))
    {
      v[0] = v[j];
      max_i = j;
    }
  }

  return max_i;

}

int FCmatrixFull::GetColMax(int i) const
{
  Vec v = GetCol(i);
  double max = v[0];
  int max_i = 0;

  for (int j = 1; j < Get_nCols(); j++)
  {
    if(fabs(v[j]) > fabs(v[0]))
    {
      v[0] = v[j];
      max_i = j;
    }
  }

  return max_i;
}

void FCmatrixFull::Print() const
{
  for (int i = 0; i < Get_nRows(); i++)
    GetRow(i).Print();
}

bool FCmatrixFull::IsSquare()
{
  if (Get_nRows() == Get_nCols())
    return true;

  else
    return false;
}
