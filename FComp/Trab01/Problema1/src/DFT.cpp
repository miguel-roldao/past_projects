#include <iostream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
#include "Signal.h"
#include "FCtools.h"
#include "vec.h"
#include "DFT.h"

using namespace std;

DFT::DFT()
{
  cout << __PRETTY_FUNCTION__ << endl;
}

DFT::DFT(Signal & S)
{
  sig1d = S;
  Np_signal = S.Size();
}

vector<double> DFT::MultCOS(Signal& S, double & f)
{
  double w = 2 * 3.14 * f;
  vector<double> result;
  for(int i = 0; i < S.Size(); i++)
    result.push_back(cos(w * S[i].first) * S[i].second);

  return result;
}

vector<double> DFT::MultSIN(Signal& S, double & f)
{
  double w = 2 * 3.14 * f;
  vector<double> result;
  for(int i = 0; i < S.Size(); i++)
    result.push_back(sin(w * S[i].first) * S[i].second);

  return result;
}

double DFT::Sum(vector<double> V)
{
  double sum = 0;

  for(int i = 0; i < V.size(); i++)
  {
    sum += V.at(i);
  //  cout<<i<<endl;
  //cout<<"\nsum: "<<sum<<"  i: "<<i<<endl;

  }

  return sum;
}

double DFT::GetPowSpec(double f)
{
  int N = sig1d.Size();
  //cout<<N<<endl;
  double pow_spec = 0;
  pow_spec = (Sum(MultCOS(sig1d,f))/((double)N)) * (Sum(MultCOS(sig1d,f))/((double)N)) + (Sum(MultSIN(sig1d,f))/((double)N))*(Sum(MultSIN(sig1d,f))/((double)N)); //erro

  return pow_spec;
}

double DFT::GetAmpSpec(double f)
{
  double P = GetPowSpec(f);
//  cout<<"\nP: "<<P<<endl;
  double A = sqrt(P);

  return A;
}
