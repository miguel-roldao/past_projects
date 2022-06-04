#include <iostream>
#include "ODEpoint.h"
using namespace std;

ODEpoint::ODEpoint()
{
  t = 0.;
  var.push_back(0.);
  Ndim = 1;
}

ODEpoint::ODEpoint (double tval, double* funct, int Ndimf)
{
  t = tval;

  for (int i = 0; i < Ndimf; i++)
  {
    var.push_back(funct[i]);
  }

  Ndim = Ndimf;
}

ODEpoint::ODEpoint(double tval, vector<double> funct)
{
  t = tval;

  var = funct;

  Ndim = funct.size();
}

ODEpoint::ODEpoint(const ODEpoint& rhs)
{
  t = rhs.Get_Time();

  var = rhs.Get_Var_vec();

  Ndim = rhs.GetNdim();
}

double * ODEpoint::Get_Var_ptr() const
{
  double * y = new double[Ndim];

  for (int i = 0; i < Ndim; i++)
    y[i] = var[i];

  return y;
}

double * ODEpoint::Get_VarTime() const
{
  double * v = new double[Ndim + 1];

  for (int i = 0; i < Ndim; i++)
    v[i] = var[i];

  v[Ndim] = t;

  return v;
}

double * ODEpoint::Get_TimeVar() const
{
  double * v = new double[Ndim + 1];

  v[0] = t;

  for (int i = 0; i < Ndim; i++)
    v[i+1] = var[i];

  return v;
}

ODEpoint &ODEpoint::operator= (const ODEpoint & P)
{

  if (this != &P) // protege contra self-assignment inválido
      {

        // 1: Apaga o vetor antigo
        var.clear();

        // 2: Copia o vetor de y
        var = P.Get_Var_vec();

        // 3: Copia t e Ndim
        t = P.Get_Time();
        Ndim = P.GetNdim();

      }

    return *this;

}


void ODEpoint::Print() const
{
  cout << "[ODEpoint]: t = " << t << " "; // falta setprecision

  for (int i = 0; i < Ndim; i++)
    cout << "y[" << i << "] = " << var[i] << " ";

  cout << "\n";
}
