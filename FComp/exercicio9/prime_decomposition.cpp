#include <iostream>
#include <cmath>
using namespace std;

bool check_prime(int n)
{
  if (n < 1)
    return false;

  for (int i = 2; i < (int) (sqrt(n) + 1); i++)
    {
      if (n % i == 0)
        return false;
    }

    return true;
}

void factorize(int n)
{

  cout << n << " = ";

  int j = 0; // iterador potências

  // Caso 1: n é par
  while (n % 2 == 0)
    {
        n = n/2;
        j++;
    }

  if (j > 0)
    {
      if (j == 1)
        cout << "2";

      else
        cout << "2^" << j;

      if (n != 1)
          cout << "*";
    }

  for (int i = 3; i < (int) (sqrt(n) + 1); i = i + 2)
    {
      if (check_prime(i))  // não tenho a certeza se isto é mais ou menos eficiente
      {
        j = 0;

        while (n % i == 0)
        {
           j++;
           n = n / i;
        }

        if (j > 0)
        {
          if (j == 1)
            cout << i;

          else
            cout << i << "^" << j;

          if (n != 1)
            cout << "*";
        }
      }
    }

    if (n > 2)
        cout << n;

    cout << endl;
}

int main(int argc, char ** argv)
{
    int n;
    cout << "Introduza um numero inteiro: ";
    cin >> n;

    if (check_prime(n) == false)
    {
        if (n > 0)
          {
            cout << endl << n << " não é um número primo. " << endl;
            factorize(n);
          }

        else
          cout << n << " não é um número inteiro positivo!" << endl;
    }

    else
      cout << endl << n << " é um número primo: " << n << " = " << n << " * 1" << endl;

    return 0;
}
