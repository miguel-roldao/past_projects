#include <iostream>
#include <cmath>
#include <iomanip>
#include "func.h"
using namespace std;

void print_int(int ***v, int m, int n, int o);

void print_double(double ***v, int m, int n, int o);

int main()
{
  int n = 100;
  int m = 50;
  int o = 1;

  int ***a = fintv(n, m, o);

  double ***b = fdoublev(n, m, 2);

/*  for(i=0; i<10; i++)
  {
    a[i] = i;
    b[i] = i;
    cout<<"a["<<i<<"] = "<<a[i]<<endl;
    cout<<"b["<<i<<"] = "<<b[i]<<endl;
  }*/
//teste
  cout << "This should be 1: " <<a[3][2][0]<<endl;
  cout << "This should be 5: " <<b[3][2][1]<<endl;

  print_int (a, n, m, o);
  print_double (b, n, m, 2);


// deleting cicles
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<m; j++)
    {
      delete[] a[i][j];
      delete[] b[i][j];
    }
    delete[] a[i];
    delete[] b[i];
  }
  delete[] a;
  delete[] b;

  return 0;
}

void print_int(int ***v, int m, int n, int o)
{
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < n; j++)
    {
      for(int k = 0; k < o; k++)
        cout << "a["<<setw(2)<<i<<"]"<<"["<<setw(2)<<j<<"] = "<<v[i][j][k]<< endl;
    }
  }
  cout << " ** Print of int tensor a complete **" << endl;
}

void print_double(double ***v, int m, int n, int o)
{
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < n; j++)
    {
      for(int k = 0; k < o; k++)
        cout << "b["<<setw(2)<<i<<"]"<<"["<<setw(2)<<j<<"] = "<<v[i][j][k]<< endl;
    }
  }
  cout << " ** Print of double tensor b complete **" << endl;
}
