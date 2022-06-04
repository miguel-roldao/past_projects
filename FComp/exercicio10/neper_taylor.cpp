#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

unsigned long long int factorial(unsigned int n)
{
  long long int factorial = 1;

  if (n == 0)
    return 1;

  else
    {
      for(int i = 1; i <= n; ++i)
        factorial *= i;
    }

    return factorial;
}

int main(int argc, char ** argv)
{
    int i = 1;
    double e = 0;

    for (i = 0; i < 10; i++)
      e = e + ((double) 1 / (double) factorial(i));

    cout << setprecision(5); // 4 casas decimais

    cout << "e = " << e << endl;

    return 0;
}
