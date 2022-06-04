#include <iostream>
#include <vector>
#include "ODEsolver.h"

using namespace std;

ODEsolver::ODEsolver(vector<TFormula> FF)
{
  F = FF;
}

void ODEsolver::SetODEfunc(vector<TFormula> FF)
{
  F = FF;
}

ODEpoint ODEsolver::EULER_iterator (const ODEpoint& p, double step)
{
  int dim = p.GetNdim();
  double dx;
  double t = p.Get_Time();
  vector<double> x = p.Get_Var_vec();
  for(int i = 0; i < dim; i++)
  {
    dx = step * F.at(i).Eval(p.Get_Time(), x.at(i));
    x.at(i) += dx;
  }
  ODEpoint p1((t+step), x);
  return p1;
}

vector<ODEpoint> ODEsolver::Eulersolver(const ODEpoint& P0, double tmin, double tmax, double h_step)
{
  vector<ODEpoint> sol;
  double dt = h_step;

  if(P0.Get_Time() == tmin)
  {
    sol.push_back(P0);

    for (double t = tmin; t <= tmax; t += dt)
    {
      ODEpoint place_holder = EULER_iterator(sol.back(),dt);
      sol.push_back(place_holder);
    }
  }

  else
  {
    cout << "\n *Warning_Euler* : O instante inicial não coincide com o ponto inicial." << endl;
    tmin = P0.Get_Time();
    sol.push_back(P0);

    for (double t = tmin; t <= tmax; t += dt)
    {
      ODEpoint place_holder = EULER_iterator(sol.back(),dt);
      sol.push_back(place_holder);
    }
  }

  return sol;
}

ODEpoint ODEsolver::Heun_iterator (const ODEpoint& p, double step)
{
  int dim = p.GetNdim();
  double t = p.Get_Time();
  double x_; // Euler iteration
  vector<double> x = p.Get_Var_vec();

  for(int i = 0; i < dim; i++)
  {
    x_ = x.at(i) + step * F.at(i).Eval(t, x.at(i));
    x.at(i) += step/2 * (F.at(i).Eval(t, x.at(i)) + F.at(i).Eval(t, x_));
  }
  ODEpoint p1((t+step),x);
  return p1;
}

vector<ODEpoint> ODEsolver::Heun(const ODEpoint& P0, double tmin, double tmax, double h_step)
{
  vector<ODEpoint> sol;
  double dt = h_step;

  if(P0.Get_Time() == tmin)
  {
    sol.push_back(P0);

    for (double t = tmin; t < tmax; t += dt)
    {
      ODEpoint place_holder = Heun_iterator(sol.back(),dt);
      sol.push_back(place_holder);
    }
  }

  else
  {
    cout << "\n *Warning_Heun* : O instante inicial não coincide com o ponto inicial." << endl;
    tmin = P0.Get_Time();

    sol.push_back(P0);

    for (double t = tmin; t < tmax; t += dt)
    {
      ODEpoint place_holder = Heun_iterator(sol.back(),dt);
      sol.push_back(place_holder);
    }
  }

  return sol;
}

ODEpoint ODEsolver::RK2_iterator (const ODEpoint& p, double step)
{
  int ydim = p.GetNdim();
  double * tandY = p.Get_TimeVar();   //  ...get the set (t,y1,y2,....) from ODEpoint...
  double * Y = p.Get_Var_ptr();       //...get the set (y1,y2,....) from ODEpoint...
  double t = p.Get_Time();            //...get the t-value from ODEpoint
  double * K1 = new double [ydim];
  double * K2 = new double [ydim];

  //Calculate K1
  for (int i = 0; i < ydim; i++)
    K1[i] = step * F.at(i).EvalPar(tandY);

  //Calculate K2
  for (int i = 0; i < ydim; i++)
    K2[i] = step * F.at(i).Eval(t+step/2,Y[i] + K1[i]/2);


  //Now let's advance the y-array...
  double * tmp = new double [ydim]; //the output y-array...
  for (int i = 0; i < ydim; i++)
  {
    tmp[i] = Y[i] + K2[i];
  }

  t += step;
  ODEpoint out(t,tmp,ydim);
  return out;
}

vector<ODEpoint> ODEsolver::RK2solver(const ODEpoint& P0, double tmin, double tmax, double h_step)
{
  vector<ODEpoint> sol;
  double dt = h_step;

  if(P0.Get_Time() == tmin)
  {
    sol.push_back(P0);

    for (double t = tmin; t < tmax; t += dt)
    {
      ODEpoint place_holder = RK2_iterator(sol.back(),dt);
      sol.push_back(place_holder);
    }
  }

  else
  {
    cout << "\n *Warning_RK2* : O instante inicial não coincide com o ponto inicial." << endl;
    tmin = P0.Get_Time();

    sol.push_back(P0);

    for (double t = tmin; t < tmax; t += dt)
    {
      ODEpoint place_holder = RK2_iterator(sol.back(),dt);
      sol.push_back(place_holder);
    }
  }

  return sol;
}

ODEpoint ODEsolver::RK4_iterator(const ODEpoint& p, double step)
{
  int ydim = p.GetNdim();
  double * tandY = p.Get_TimeVar();   //  ...get the set (t,y1,y2,....) from ODEpoint...
  double * Y = p.Get_Var_ptr();       //...get the set (y1,y2,....) from ODEpoint...
  double t = p.Get_Time();            //...get the t-value from ODEpoint
  double * K1 = new double [ydim];
  double * K2 = new double [ydim];
  double * K3 = new double [ydim];
  double * K4 = new double [ydim];

  //Calculate K1
  for (int i = 0; i < ydim; i++)
    K1[i] = step * F.at(i).EvalPar(tandY);

  double* aux = p.Get_TimeVar(); // right dimensions
  aux[0] = t + step/2.;

  for(int i = 0; i < ydim; i++)
    aux[i+1] = Y[i] + K1[i]/2.;

  //Calculate K2
  for (int i = 0; i < ydim; i++)
    K2[i] = step * F.at(i).EvalPar(aux);

  for(int i = 0; i < ydim; i++)
    aux[i+1] = Y[i] + K2[i]/2.;

  //Calculate K3
  for(int i = 0; i < ydim; i++)
    K3[i] = step * F.at(i).EvalPar(aux);

  aux[0] = t + step;

  for(int i = 0; i < ydim; i++)
    aux[i+1] = Y[i] + K3[i];

  //Calculate K4
  for(int i = 0; i < ydim; i++)
    K4[i] = step * F.at(i).EvalPar(aux);

  //Now let's advance the y-array...
  double * tmp = new double [ydim]; //the output y-array...

  for (int i = 0; i < ydim; i++)
    tmp[i] = Y[i] + 1./6. * (K1[i] + 2 * K2[i] + 2 * K3[i] + K4[i]);

  t += step;
  ODEpoint out(t,tmp,ydim);

  delete[] aux;
  delete[] K1;
  delete[] K2;
  delete[] K3;
  delete[] K4;
  delete[] tandY;
  delete[] Y;

  return out;
}

vector<ODEpoint> ODEsolver::RK4solver(const ODEpoint& P0, double tmin, double tmax, double h_step)
{
  vector<ODEpoint> sol;
  double dt = h_step;

  if(P0.Get_Time() == tmin)
  {
    sol.push_back(P0);

    for (double t = tmin; t < tmax; t += dt)
    {
      ODEpoint place_holder = RK4_iterator(sol.back(),dt);
      sol.push_back(place_holder);
    }
  }

  else
  {
    cout << "\n *Warning_RK4* : O instante inicial não coincide com o ponto inicial." << endl;
    tmin = P0.Get_Time();

    sol.push_back(P0);

    for (double t = tmin; t < tmax; t += dt)
    {
      ODEpoint place_holder = RK4_iterator(sol.back(),dt);
      sol.push_back(place_holder);
    }
  }

  return sol;
}

vector<ODEpoint> ODEsolver::Verlet(const ODEpoint& P0, double tmin, double tmax, double h_step)
{
  vector<ODEpoint> sol;
  double dt = h_step;
  double t;
  double yholder;

  if(F.size() == 2)
  {
    if(P0.Get_Time() == tmin)
    {
      sol.push_back(P0);
      t+=dt;
      double* tandY_i = P0.Get_TimeVar();
      double pfirst[] = {P0[0] + P0[1]*dt + dt*dt*F.at(1).EvalPar(tandY_i), 0};
      ODEpoint P1(tmin + dt, pfirst, 2);

      sol.push_back(P1);

      for (t; t < tmax; t += dt)
      {
        double* tandYlast = sol.back().Get_TimeVar();
        yholder = 2 * sol.back()[0] - sol.at(sol.size()-2)[0] + dt*dt*F.at(1).EvalPar(tandYlast);
        double odeholder[] = {yholder, 0};
        ODEpoint holder(t+dt, odeholder, 2);
        sol.push_back(holder);
      }
    }

    else
    {
      cout << "\n *Warning_Verlet* : O instante inicial não coincide com o ponto inicial." << endl;
      tmin = P0.Get_Time();

      sol.push_back(P0);
      double* tandY_i = P0.Get_TimeVar();
      double pfirst[] = {P0[0] + P0[1]*dt + dt*dt*F.at(1).EvalPar(tandY_i), 0};
      ODEpoint P1(tmin + dt, pfirst, 2);

      sol.push_back(P1);

      for (double t = tmin; t < tmax; t += dt)
      {
        double* tandYlast = sol.back().Get_TimeVar();
        yholder = 2 * sol.back()[0] - sol.at(sol.size()-2)[0] + dt*dt*F.at(1).EvalPar(tandYlast);
        double odeholder[] = {yholder, 0};
        ODEpoint holder(t+dt, odeholder, 2);
        sol.push_back(holder);
      }
    }

    return sol;
  }

  cout << __PRETTY_FUNCTION__ << "*this method only works with 2nd order differential equations!**\n";

}

vector<ODEpoint> ODEsolver::RK4_AdapStep(const ODEpoint& P0, double tmin, double tmax, double h_step)
{}

ODEpoint ODEsolver::RK4_AS_iterator(const ODEpoint& p, double step, vector < vector <double> >& K)
{}
