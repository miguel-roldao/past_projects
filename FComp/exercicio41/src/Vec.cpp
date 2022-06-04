#include <iostream>
#include <iomanip>
#include "Vec.h"

using namespace std;

Vec::Vec (int n, double d) // default constructor
{
  N = n;
  entries = new double[N];

  for(int i = 0; i < N; i++)
    entries[i] = d;
}

Vec::Vec (int n, double *ptr) // constructor (n, ptr)
{
  N = n;
  entries = new double[N];

  for(int i = 0; i < n; i++)
    entries[i] = ptr[i];
}

Vec::~Vec() { delete[] entries; } // destructor

Vec::Vec (const Vec &v) // copy constructor
{
  N = v.N;
  entries = new double[N];

  for (int i = 0; i < N; i++)
    entries[i] = v.entries[i];
}

void Vec::SetEntries (int n, double* ptr)
{
  N = n;

  delete[] entries;

  entries = new double[N];

  for (int i = 0; i < n; i++)
    entries[i] = ptr[i];
}

void Vec::Print()
{
  cout << "| ";

  for (int i = 0; i < N; i++)
    cout << setw(6) << setprecision(4) << entries[i] << " ";

  cout << " |" << endl;
}

void Vec::Swap(int m, int n)
{
  double p = entries[m];
  entries[m] = entries[n];
  entries[n] = p;
}

double Vec::dot(Vec u) const
{
  if( N == u.Size())
  {
    double ans = 0;
    for(int i = 0; i < N; i++)
      ans += entries[i] * u[i];

    return ans;
  }

  else
  {
    cout << "Os vetores não têm o mesmo tamanho; é impossível calcular o produto interno!" << endl;
    exit (EXIT_FAILURE);
  }
}

Vec Vec::cross (const Vec &rhs)
{

  Vec v(N);

  if (N == 3 && rhs.N == 3)
    {
      v[0] = entries[1] * rhs.entries[2] - entries[2] * rhs.entries[1];
      v[1] = entries[0] * rhs.entries[2] - entries[2] * rhs.entries[0];
      v[2] = entries[0] * rhs.entries[1] - entries[1] * rhs.entries[0];
    }

  else if (N == 7 && rhs.N == 7)
      cout << "É possível definir um produto externo em R7, mas provavelmente não o quer calcular..." << endl;

  else
  {
    cout << "Os vetores não são ambos de R3 ou de R7; não é possível definir um produto externo! " << endl;
    exit (EXIT_FAILURE);
  }

  return v;
}

Vec Vec::operator+ (const Vec &rhs) const
{

  Vec v(N);

  if (N == rhs.N)
    {
      for (int i = 0; i < N; i++)
        v.entries[i] = rhs.entries[i] + entries[i];
    }

  else
  {
    cout << "Os vetores não têm o mesmo tamanho; é impossível somá-los!" << endl;
    exit (EXIT_FAILURE);
  }

  return v;
}

Vec Vec::operator- (const Vec &rhs) const
{

  Vec v(N);

  if (N == rhs.N)
    {
      for (int i = 0; i < N; i++)
        v.entries[i] = entries[i] - rhs.entries[i];
    }

  else
  {
    cout << "Os vetores não têm o mesmo tamanho; é impossível subtraí-los!" << endl;
    exit (EXIT_FAILURE);
  }

  return v;
}

Vec Vec::operator* (const Vec &rhs) const
{

  Vec v(N);

  if (N == rhs.N)
    {
      for (int i = 0; i < N; i++)
        v.entries[i] = rhs.entries[i] * entries[i];
    }

  else
  {
    cout << "Os vetores não têm o mesmo tamanho; é impossível multiplicar as suas componentes!" << endl;
    exit (EXIT_FAILURE);
  }

  return v;
}

Vec Vec::operator* (const double & scalar) const
{

  Vec v(N);

  for (int i = 0; i < N; i++)
        v.entries[i] = scalar * entries[i];

  return v;

}

Vec &Vec::operator= (const Vec & rhs)
{

  if (this != &rhs) // protege contra self-assignment inválido
    {
      // 1: Aloca nova memória e copia os elementos
      double * new_entries = new double[rhs.N];

      for (int i = 0; i < rhs.N; i++)
        new_entries[i] = rhs.entries[i];

      // 2: Liberta a memória antiga
      delete[] entries;

      // 3: Faz o assignement da nova memória ao objeto
      entries = new_entries;
      N = rhs.N;
    }

    return *this;
}


Vec &Vec::operator+= (const Vec & rhs)
{
  if (N == rhs.N)
    {
      for (int i = 0; i < N; i++)
        entries[i] += rhs.entries[i];
    }

  else
    {
      cout << "Os vetores não têm o mesmo tamanho; é impossível somá-los!" << endl;
      exit (EXIT_FAILURE);
    }

}

Vec &Vec::operator-= (const Vec & rhs)
{
  if (N == rhs.N)
    {
      for (int i = 0; i < N; i++)
        entries[i] -= rhs.entries[i];
    }

    else
      {
        cout << "Os vetores não têm o mesmo tamanho; é impossível subtraí-los!" << endl;
        exit (EXIT_FAILURE);
      }
}

Vec &Vec::operator*= (const Vec & rhs)
{
  if (N == rhs.N)
    {
      for (int i = 0; i < N; i++)
        entries[i] *= rhs.entries[i];
    }

  else
    {
      cout << "Os vetores não têm o mesmo tamanho; é impossível multiplicar as suas componentes!" << endl;
      exit (EXIT_FAILURE);
    }

}

Vec Vec::operator- ()
{
  double * new_entries = new double[N];

  for (int i = 0; i < N; i++)
    new_entries[i] = -entries[i];

  Vec u(N, new_entries);

  return u;
}

Vec Vec::operator+ ()
{
  double * new_entries = new double[N];

  for (int i = 0; i < N; i++)
    new_entries[i] = entries[i];

  Vec u(N, new_entries);

  return u;
}

double Vec::operator[] (int i) const
{
  if (i <= Size())
    return GetEntries()[i];

  else
    {
      cout << "A componente a que está a tentar aceder não existe!" << endl;
      exit(EXIT_FAILURE);
    }
}


double& Vec::operator[] (int i)
{
  if (i <= Size())
    return GetEntries()[i];

  else
    {
      cout << "A componente a que está a tentar aceder não existe!" << endl;
      exit(EXIT_FAILURE);
    }
}
