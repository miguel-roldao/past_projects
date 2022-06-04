#include <iostream>
using namespace std;

double*** fdoublev(int n, int m, int o)
{
  double ***v;
  v = new double**[n];
  for(int i = 0; i < n; i++)
    {
      v[i] = new double*[m];

      for(int j = 0; j < m; j++)
      {
        v[i][j] = new double [o];

        for(int k = 0; k < o; k++)
          v[i][j][k] = 5.0;
      }
    }
  return v;
}
