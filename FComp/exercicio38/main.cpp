#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{

  long int i = 0;
  float x = 0;
  double y = 0;
  double epsilon = 1e-50;

  // Float

  while (x != 1.)
  {
    i++ ;
    x = 1. ;
    x += 1 / (float) i;
  }

  cout << "A precisão de um float  é " << 1. / i << endl;

  // Double

  i = 0;

  while (fabs(y - 1.) > epsilon) // arbitrariamente pequeno
  {
    i++;
    y = 1.;
    y += pow(2, -i); // uma função que decai razoavelmente depressa, mas não sacrifica demasiado a precisão
    /* cout.precision(20);
    cout << y << endl; */
  }

  cout << "A precisão de um double é " << pow(2, -i) << endl;

  return 0;
}
