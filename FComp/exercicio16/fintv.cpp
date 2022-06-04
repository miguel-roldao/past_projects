#include <iostream>
using namespace std;

int*** fintv(int n, int m, int o)
{
  int *** v;
  v = new int**[n];
  for(int i = 0; i < n; i++)
    {
      v[i] = new int*[m];

      for(int j = 0; j < m; j++)
      {
        v[i][j] = new int [o];

        for(int k = 0; k < o; k++)
          v[i][j][k] = 1;
      }
    }
  return v;
}
