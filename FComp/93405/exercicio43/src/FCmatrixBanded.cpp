#include <string>
#include <iostream>
#include <cmath>
#include "FCmatrixBanded.h"

using namespace std;

FCmatrixBanded::FCmatrixBanded() //default constructor
{
  //M;
  classname = "FCmatrixBanded";
}
FCmatrixBanded::FCmatrixBanded(double** fM, int fm, int fn)
{
  classname = "FCmatrixBanded";
  Vec v;
//  int n;
  double* p;
  p = new double[fn];

// diagonal superior

  for(int j = 0; j < fn-1; j++)
    p[j] = fM[j][j+1];

  v.SetEntries(fn-1, p);
  M.push_back(v);


 // diagonal principal

  for(int j = 0; j < fn; j++)
    p[j] = fM[j][j];

  v.SetEntries(fn, p);
  M.push_back(v);

  // diagonal inferior

  for(int j = 0; j < fn-1; j++)
    p[j] = fM[j+1][j];

  v.SetEntries(fn-1, p);
  M.push_back(v);

  delete[] p;
}

FCmatrixBanded::FCmatrixBanded(double* fM, int fm, int fn)
{
  classname = "FCmatrixBanded";
  Vec v;
  double* p;
  p = new double[fn];

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

  delete[] p;
}

FCmatrixBanded::FCmatrixBanded(vector<Vec> V)
{
  classname = "FCmatrixBanded";
  Vec v;
  int fn = V.size();
  double* p;
  p = new double[fn];

// diagonal superior

  for(int j = 0; j < fn-1; j++)
    p[j] = V.at(j).GetEntries()[j+1];

  v.SetEntries(fn-1, p);
  M.push_back(v);


 // diagonal principal

  for(int j = 0; j < fn; j++)
    p[j] = V.at(j).GetEntries()[j];

  v.SetEntries(fn, p);
  M.push_back(v);

  // diagonal inferior

  for(int j = 0; j < fn-1; j++)
    p[j] = V.at(j+1).GetEntries()[j];

  v.SetEntries(fn-1, p);
  M.push_back(v);

  delete[] p;
}

FCmatrixBanded::FCmatrixBanded(const FCmatrixBanded& FC)
{
  classname = FC.GetClassName();
  M = FC.GetM();
}

/*Vec FCmatrixBanded::GetRow(int i)
{
  n = M.at(i).Size(); // nº de elementos da linha
  double *p;
  p = new double[n];

  for (int j = 0; j < n; j++)
    p[j] = 0;

  if(i == 1)
  {
    p[i-1] = M.at(1).GetEntries()[i-1];
    p[i] = M.at(0).GetEntries()[i-1];
  }

  else if(i == n)
  {
    p[i-2] = M.at(2).GetEntries()[i-2];
    p[i-1] = M.at(1).GetEntries()[i-1];
  }

  else
  {
  p[i-2] = M.at(2).GetEntries()[i-2];
  p[i-1] = M.at(1).GetEntries()[i-1];
  p[i] = M.at(0).GetEntries()[i-1];
  }

  delete[] p;
}
*/
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

  if (classname == ma.GetClassName() && M.at(1).Size() == ma.GetM().at(1).Size())
  {
    for(int i = 0; i < 3; i++)
      v.at(i) = M.at(i) + ma.GetM().at(i);
  }

  else
      {
          cout << "As matrizes não têm o mesmo tamanho; é impossível somá-las!" << endl;
          exit (EXIT_FAILURE);
      }

  FCmatrixBanded result;
  result.GetM() = v;

  return result;
}

FCmatrixBanded FCmatrixBanded::operator-(const FCmatrixBanded & ma) const
{
  vector<Vec> v;

  if (classname == ma.GetClassName() && M.at(1).Size() == ma.GetM().at(1).Size())
  {
    for(int i = 0; i < 3; i++)
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

  for(int i = 0; i < 3; i++)
    v.at(i) = M.at(i) * lambda;

  FCmatrixBanded result;
  result.M = v;

  return result;
}

Vec FCmatrixBanded::operator*(const Vec & v) const
{
  int n = M.at(1).Size();

  double *p;
  p = new double[M.at(1).Size()];  // matrizes quadradas :)

  if(v.Size() == n)
  {
    for(int i = 0; i < n; i++)
      p[i] = (*this).GetRow(i).dot(v);
  }
  Vec result(n, p);
  return result;
}

Vec& FCmatrixBanded::operator[](int i)
{
  cout<<"O operador [] não está definido para FCmatrixBanded!"<<endl;
}

int FCmatrixBanded::Get_nRows() const
{
  return M.at(1).Size();
}

int FCmatrixBanded::Get_nCols() const // semelhante à anterior (matriz quadrada)
{
  return M.at(1).Size();
}

Vec FCmatrixBanded::GetRow(int i) const
{
  int n = M.at(1).Size();
  double* p;

  p = new double[n];

  if(i == 1)  // primeira linha
  {
    p[0] = M.at(1)[0];
    p[1] = M.at(0)[0];

    for(int j = 2; j < n; j++)
      p[j] = 0;
  }

  else if(i == n)  // ultima linha
  {
    for(int j = 0; j < n-2; j++)
      p[j] = 0;

    p[n-1] = M.at(2)[n-2];
    p[n] = M.at(1)[n];
  }

  else   // linhas intermedias
  {
    for(int j = 0; j < n; j++)
    {
      if(j == i-2)
        p[j] = M.at(2)[i-2];

      else if(j == i-1)
        p[j] = M.at(1)[i-1];

      else if(j == i)
        p[j] = M.at(0)[i-1];

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
  int n = M.at(1).Size();
  double* p;

  p = new double[n];

  if(i == 1)  // primeira coluna
  {
    p[0] = M.at(1)[0];
    p[1] = M.at(2)[0];

    for(int j = 2; j < n; j++)
      p[j] = 0;
  }

  else if(i == n)  // ultima coluna
  {
    for(int j = 0; j < n-2; j++)
      p[j] = 0;

    p[n-1] = M.at(0)[n-2];
    p[n] = M.at(1)[n];
  }

  else   // colunas intermedias
  {
    for(int j = 0; j < n; j++)
    {
      if(j == i-2)
        p[j] = M.at(0)[i-2];

      else if(j == i-1)
        p[j] = M.at(1)[i-1];

      else if(j == i)
        p[j] = M.at(2)[i-1];

      else
        p[j] = 0;
    }
  }

  Vec v(n, p);

  delete[] p;
  return v;
}

double FCmatrixBanded::Determinant() const
{
  cout<<"O determinante de uma FCmatrixBanded não está definido!"<<endl;
  return 0;
}

int FCmatrixBanded::GetRowMax(int i) const
{
  Vec v = (*this).GetRow(i);
  double max = v[0];

  int max_i = 0;
  int n = (*this).Get_nRows();

  for (int j = 0; j < n; j++)
  {
    if(fabs(v[j]) > fabs(v[0]))
    {
      v[0] = v[j];
      max_i = j;
    }
  }

  return max_i;
}

int FCmatrixBanded::GetColMax(int i) const
{
  Vec v = (*this).GetCol(i);
  double max = v[0];

  int max_i = 0;
  int n = (*this).Get_nCols();

  for (int j = 0; j < n; j++)
  {
    if(fabs(v[j]) > fabs(v[0]))
    {
      v[0] = v[j];
      max_i = j;
    }
  }

  return max_i;
}

void FCmatrixBanded::Print() const
{
  int n = M.at(1).Size();

  for(int i = 0; i < n; i++)
  {
    (*this).GetRow(i-1).Print();
  }
}
