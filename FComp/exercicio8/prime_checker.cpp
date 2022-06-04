#include <iostream>
#include <cmath>
using namespace std;

int check_prime(int n)
{
  if (n < 1)
    return 0;

  for (int i = 2; i < (int) (sqrt(n) + 1); i++)
    {
      if (n % i == 0)
        return 0;
    }
}

int main()
{
    int n;
    cout << "Introduza um numero inteiro: ";
    cin >> n;

    if (check_prime(n) == 0)
      cout << endl << n << " não é um número primo." << endl;

    else
      cout << endl << n << " é um número primo." << endl;

    return 0;
}
