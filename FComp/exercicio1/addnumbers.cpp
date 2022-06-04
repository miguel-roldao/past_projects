#include <iostream>
#include <cstdio>
using namespace std;

/** alínea a)

int main (int argc, char ** argv)
{
  double a, b;
  cout << "--- Somar dois numeros -- \n";
  cout << "Primeiro numero: ";
  cin >> a;
  cout << "Segundo  numero: ";
  cin >> b;
  cout << "Soma = " << a + b << endl;
  return 0;
}
**/
int main (int argc, char ** argv)
{
  double a, b;
  printf ("--- Somar dois numeros -- \nPrimeiro numero: ");
  scanf("%lf", &a);
  printf ("Segundo  numero: ");
  scanf("%lf", &b);
  printf("Soma = %.2lf \n", a+b); // a partir daqui, não há precisão
  return 0;
}
