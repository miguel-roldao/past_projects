#include <iostream>
#include <vector>
#include <string>
#include "FCmatrixFull.h"

using namespace std;


/*
          ____________                __       _      ______      ____
         / ____/ ____/___ ___  ____ _/ /______(_)  __/ ____/_  __/ / /
        / /_  / /   / __ `__ \/ __ `/ __/ ___/ / |/_/ /_  / / / / / /
       / __/ / /___/ / / / / / /_/ / /_/ /  / />  </ __/ / /_/ / / /
      /_/    \____/_/ /_/ /_/\__,_/\__/_/  /_/_/|_/_/    \__,_/_/_/

                                                                              */

FCmatrixFull::FCmatrixFull() // default constructor
{
  classname = "FCmatrixFull";
}

FCmatrixFull::FCmatrixFull(double** fM, int fm, int fn)
{
  Vec v(fn);

  for (int i = 0; i < fm; i++)
    {
      v.SetEntries(fn, fM[i]);
      M.push_back(v);
    }

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
      delete[] matrix[i];
    }


  delete[] matrix;

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
      if (Get_nRows() == rhs.Get_nRows())
        {
          if (Get_nCols() == rhs.Get_nCols())
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
      if (Get_nRows() == rhs.Get_nRows())
        {
          if (Get_nCols() == rhs.Get_nCols())
            {
              for (int i = 0; i < rhs.Get_nRows(); i++)
                result.M.push_back(M[i] - rhs.GetRow(i)); // subtracao de vecs
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
      for (int i = 0; i < m; i++) // cij = linha i coluna j
      {
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
  if (i < Get_nRows() )
    return M[i];

  else
    {
      cout << "A linha a que está a tentar aceder não existe!" << endl;
      exit(EXIT_FAILURE);
    }
}

int FCmatrixFull::Get_nRows() const
{
  return M.size();
}

int FCmatrixFull::Get_nCols() const
{

  /* O tamanho de todos os Vecs (linhas da matriz) é igual, por isso basta ver o primeiro (que existe sempre)
    É possível, usando o copy constructor 2 construir uma 'matriz' com linhas de tamanho diferente, mas
    não faz sentido, pelo que isso não é testado.  */

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
  int n = Get_nRows();
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
    return M[0][0];

  vector <Vec> cofactors;
  Vec co_row;

  int sgn = 1;  // sgn()

  if (m == n)
  {

    if (n == 1)
      det = M[0][0];

    else if (n == 2)
      det = M.at(0)[0] * M.at(1)[1] - M.at(0)[1] * M.at(1)[0]; // trivial 2 x 2

    else
    {

      for (int i = 0; i < n; i++)
      {

        if (M.at(0)[i] == 0)  // evita calcular matrizes cofatores desnecessárias

        {
          if (i < n-1)
          {
            //i++;
            sgn *= -1;
            continue;
          }

          else
            break;

        }

        double* p = new double[n-1];  // no segmentation fault

        for (int j = 1; j < m; j++)
        {
          for (int k = 0, t = 0; k < n; k++)
          {

            if (k == i)
              continue;

            p[t] = M[j][k];
            t++;
          }

          co_row.SetEntries(n-1, p);

          cofactors.push_back(co_row);
        }

        delete[] p;

        FCmatrixFull mx (cofactors); //matriz dos cofatores

        cofactors.clear();

        det += sgn * M[0][i] * mx.Determinant();
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
    if(abs(v[j]) > abs(v[0]))
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
//  Vec l = GetRow(i);
  int max_i = i;
  double w = 0;

  for(int k = i+1; k < Get_nCols(); k++)
    w += abs(GetRow(0)[k]);

  double max_rel = v[0] - w;  //evita possíveis divisoes por zero

  int n = Get_nRows();

  for (int j = i+1; j < n; j++)
  {
    if(v[j] == 0)
      continue;

    Vec Row_j = GetRow(j);

    w = 0;

    for(int k = i+1; k < Get_nCols(); k++)
      w += abs(Row_j[k]);

    if(max_rel < (abs(v[j]) - w) )
    {
      max_rel = (abs(v[j]) - w);
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

Vec FCmatrixFull::GetDiagonal() const
{
  int n = Get_nRows();
  Vec d(n);

  if (!IsSquare())
    {
      cout << "A matriz não é quadrada!" << endl;
      exit(EXIT_FAILURE);
    }


  for (int i = 0; i < n; i++)
    {
      d[i] = M[i][i];
    }

  return d;
}

Vec FCmatrixFull::GetUD() const
{
  int n = Get_nRows();
  Vec d(n - 1);

  if (!IsSquare())
    {
      cout << "A matriz não é quadrada" << endl;
      exit(EXIT_FAILURE);
    }


  for (int i = 0; i < n - 1; i++)
    {
      d[i] = M[i][i + 1];
    }

  return d;
}

Vec FCmatrixFull::GetLD() const
{
  int n = Get_nRows();
  Vec d(n - 1);

  if (!IsSquare())
    {
      cout << "A matriz não é quadrada" << endl;
      exit(EXIT_FAILURE);
    }


  for (int i = 1; i < n; i++)
    {
      d[i] = M[i][i - 1];
    }

  return d;
}

bool FCmatrixFull::IsSquare() const
{
  if (Get_nRows() == Get_nCols())
    return true;

  else
    return false;
}
