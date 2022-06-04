#include <string>
#include <iostream>
#include <cmath>
#include "FCmatrixBanded.h"

using namespace std;

/*
    ____________                __       _      _____                  __          __
   / ____/ ____/___ ___  ____ _/ /______(_)  __/ __  |____  ___   ____/ /____  ___/ /
  / /_  / /   / __ `__ \/ __ `/ __/ ___/ / |/_/ /_/ // __ `/ __ `/ __  /  __|/ __  /
 / __/ / /___/ / / / / / /_/ / /_/ /  / />  </ /_/ |/ /_/ / / / / /_/ /  _/ / /_/ /
/_/    \____/_/ /_/ /_/\__,_/\__/_/  /_/_/|_/_____/\__,__/_/ /_/\____/____/ \____/

                                                                              */

FCmatrixBanded::FCmatrixBanded() // default constructor
{
  cout << __PRETTY_FUNCTION__ << endl;
  classname = "FCmatrixBanded";
}

FCmatrixBanded::FCmatrixBanded(double** fM, int fm, int fn)
{
  classname = "FCmatrixBanded";
  Vec v;

  if(fm == 1 && fn == 1)
  {
    v.SetEntries(1, fM[0]);
    M.push_back(v);
  }

  else
  {
    // diagonal superior

    v.SetEntries(fn-1, fM[0]);
    M.push_back(v);

    // diagonal principal

    v.SetEntries(fn, fM[1]);
    M.push_back(v);

    // diagonal inferior

    v.SetEntries(fn-1, fM[2]);
    M.push_back(v);
  }
}

FCmatrixBanded::FCmatrixBanded(double* fM, int fm, int fn)
{
  classname = "FCmatrixBanded";
  Vec v;
  double* p;
  p = new double[fn];

  if(fm == 1 && fn == 1)
  {
    v.SetEntries(1, fM);
    M.push_back(v);
  }

  else
  {

    for(int i = 0, j = 0; i < 3 * fn - 2 ; i++, j++)
    {
      p[j] = fM[i];

      if(i == (fn - 2) || i == (2 * fn - 2))
      {
        j = 0;
        v.SetEntries(j+1, p);
        M.push_back(v);
      }
    }
  }

  delete[] p;
}

FCmatrixBanded::FCmatrixBanded(Vec ld, Vec md, Vec ud)
{
  classname = "FCmatrixBanded";
  if(md.Size() != 1)
  {
    M.push_back(ud);
    M.push_back(md);
    M.push_back(ld);
  }
  else
  {
    M.push_back(md);
  }
}

FCmatrixBanded::FCmatrixBanded(vector<Vec> V)
{
  classname = "FCmatrixBanded";
  Vec v;
  int fn = V.size();
  for (int i = 0; i < fn; i++)
    M.push_back(V.at(i));
}

FCmatrixBanded::FCmatrixBanded(const FCmatrixBanded& FC)
{
  classname = FC.GetClassName();
  M = FC.GetM();
}

FCmatrixBanded FCmatrixBanded::operator=(const FCmatrixBanded & ma)
{
  if (this != &ma) // protege contra self-assignment inválido
  {
    classname = ma.GetClassName();
    M = ma.GetM();
  }
  return *this;
}

FCmatrixBanded FCmatrixBanded::operator+(const FCmatrixBanded & ma) const
{
  vector<Vec> v;

  if (classname == ma.GetClassName() && M.at(0).Size() == ma.GetM().at(0).Size())
  {
    for(int i = 0; i < M.size(); i++)
      v.at(i) = M.at(i) + ma.GetM().at(i);
  }

  else
      {
          cout << "As matrizes não têm o mesmo tamanho; é impossível somá-las!" << endl;
          exit (EXIT_FAILURE);
      }

  FCmatrixBanded result(v);

  return result;
}

FCmatrixBanded FCmatrixBanded::operator-(const FCmatrixBanded & ma) const
{
  vector<Vec> v;

  if (classname == ma.GetClassName() && M.at(0).Size() == ma.GetM().at(0).Size())
  {
    for(int i = 0; i < M.size(); i++)
      v.at(i) = M.at(i) - ma.GetM().at(i);
  }

  else
      {
          cout << "As matrizes não têm o mesmo tamanho; é impossível subtraí-las!" << endl;
          exit (EXIT_FAILURE);
      }

  FCmatrixBanded result;
  result.M = v;

  return result;
}

/*FCmatrixBanded FCmatrixBanded::operator*(const FCmatrixBanded & ma) const
{
  vector<Vec> v;

  if (classname == ma.GetClassName() && M.at(1).Size() == ma.GetM().at(1).Size())
  {
    int n = M.at(1).Size();

    for(int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
        v.at(i)[j] = this.GetRow(i+1) dot ma.GetCol(j+1);
    }
  }
  FCmatrixBanded result(v);

  return result;
}*/

FCmatrixBanded FCmatrixBanded::operator*(double lambda) const
{
  vector<Vec> v;

  for(int i = 0; i < M.size(); i++)
    v.at(i) = M.at(i) * lambda;

  FCmatrixBanded result;
  result.M = v;

  return result;
}

Vec FCmatrixBanded::operator*(const Vec & v) const
{
  if(M.size() == 1 && v.Size() == 1)  // matriz 1x1
  {
    Vec r(1, M[0][0] * v[0] );
    return r;
  }
  else
  {
    int n = M.at(1).Size();

    double *p;
    p = new double[M.at(1).Size()];  // matrizes quadradas :)

    if(v.Size() == n)
    {
      for(int i = 0; i < n; i++)
        p[i] = GetRow(i).dot(v);
    }

    Vec result(n, p);
    return result;
  }
}

Vec& FCmatrixBanded::operator[](int i)
{
  if (i == 0 )
    return M[0];

  else if (i == 1 && M.size() == 3)
    return M[1];

  else if (i == 2 && M.size() == 3)
      return M[2];

  else if (i == 98 && M.size() == 3) // b
        return M[0];

  else if (i == 97 && M.size() == 3) // a
        return M[1];

  else if (i == 99 && M.size() == 3) // c
      return M[2];

  else
    {
      cout << "A posição à qual está a tentar aceder não existe!" << endl;
      exit(EXIT_FAILURE);
    }
}

/** Vec& FCmatrixBanded::operator[](char x)
{
  if (x == 98) // b
    return M[0];

  else if (x == 97) // a
    return M[1];

  else if (x == 99) // c
      return M[2];

  else
    {
      cout << "A posição à qual está a tentar aceder não existe!" << endl;
      exit(EXIT_FAILURE);
    }
} **/

int FCmatrixBanded::Get_nRows() const
{
  if(M.size() == 1)
    return 1;

  return M.at(1).Size();
}

int FCmatrixBanded::Get_nCols() const // semelhante à anterior (matriz quadrada)
{
  if(M.size() == 1)
    return 1;

  return M.at(1).Size();
}

Vec FCmatrixBanded::GetRow(int i) const
{
  if(M.size() == 1) //matriz 1x1
    return M.at(0);

  int n = M.at(1).Size();
  double* p;

  p = new double[n];

  if(i == 0)  // primeira linha
  {
    p[0] = M.at(1)[0];
    p[1] = M.at(0)[0];

    for(int j = 2; j < n; j++)
      p[j] = 0;
  }

  else if(i == n-1)  // ultima linha
  {
    for(int j = 0; j < n-2; j++)
      p[j] = 0;

    p[n-2] = M.at(2)[n-2];
    p[n-1] = M.at(1)[n-1];
  }

  else   // linhas intermedias
  {
    for(int j = 0; j < n; j++)
    {
      if(j == i-1)
        p[j] = M.at(2)[i-1];  //diagonal inferior

      else if(j == i)
        p[j] = M.at(1)[i];  //diagonal principal

      else if(j == i+1)
        p[j] = M.at(0)[i];  //diagonal superior

      else
        p[j] = 0;
    }
  }

  Vec v(n, p);

  delete[] p;
  return v;
}

Vec FCmatrixBanded::GetCol(int i) const
{
  if (M.size() == 1) //matriz 1x1
    return M.at(0);

  int n = M.at(1).Size();
  double* p;

  p = new double[n];

  if(i == 0)  // primeira coluna
  {
    p[0] = M.at(1)[0];
    p[1] = M.at(2)[0];

    for(int j = 2; j < n; j++)
      p[j] = 0;
  }

  else if(i == n-1)  // ultima coluna
  {
    for(int j = 0; j < n-2; j++)
      p[j] = 0;

    p[n-2] = M.at(0)[n-2];
    p[n-1] = M.at(1)[n-1];
  }

  else   // colunas intermedias
  {
    for(int j = 0; j < n; j++)
    {
      if(j == i-1)
        p[j] = M.at(0)[i-1];

      else if(j == i)
        p[j] = M.at(1)[i];

      else if(j == i+1)
        p[j] = M.at(2)[i];

      else
        p[j] = 0;
    }
  }

  Vec v(n, p);

  delete[] p;
  return v;
}


int FCmatrixBanded::GetRowMax(int i) const
{
  Vec v = GetRow(i);
  double max = abs(v[0]);

  int max_i = 0;
  int n = Get_nRows();

  for (int j = 0; j < n; j++)
  {
    if(abs(v[j]) > max)
    {
      max = abs(v[j]);
      max_i = j;
    }
  }

  return max_i;
}

int FCmatrixBanded::GetColMax(int i) const
{
  Vec v = GetCol(i);
  double max = v[0];

  int max_i = 0;
  int n = Get_nCols();

  for (int j = 0; j < n; j++)
  {
    if(abs(v[j]) > abs(v[0]))
    {
      max = abs(v[j]);
      max_i = j;
    }
  }

  return max_i;
}

void FCmatrixBanded::Print() const
{
  if (M.size() == 1)  //matriz 1x1
    GetRow(0).Print();

  else
  {

    int n = M.at(1).Size();

    for(int i = 0; i < n; i++)
    {
      GetRow(i).Print();
    }
  }
}

double FCmatrixBanded::Determinant() const
{
  if (M.size() == 1)  //matriz 1x1
    return M.at(0)[0];

  double fn, fn_1, fn_2;
  int n = Get_nCols();

  fn_2 = 0; // f(n-2) = f(-1)
  fn_1 = 1; // f(n-1) = f(0)
  fn = M[1][0]; // f(n) = f(1)

  // Uma matriz FCmatrixBanded é sempre quadrada
  for (int i = 1; i < n; i++)
    {
      double p = fn;
      fn = M[1][i] * fn - M[0][i-1] * M[2][i-1] * fn_1;
      fn_1 = p;
    }

  // cout<<"O determinante de uma FCmatrixBanded não está definido!"<<endl;
  return fn;
}

Vec FCmatrixBanded::GetDiagonal() const
{
  if (M.size() == 1)  //matriz 1x1
    return M.at(0)[0];

  return M[1];
}


Vec FCmatrixBanded::GetUD() const
{
  if (M.size() == 1)  //matriz 1x1
    return M.at(0)[0];

  return M[0];
}

Vec FCmatrixBanded::GetLD() const
{
  if (M.size() == 1)  //matriz 1x1
    return M.at(0)[0];

  return M[2];
}
