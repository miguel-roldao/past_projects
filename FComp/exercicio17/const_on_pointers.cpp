#include <iostream>
#include <cmath>
using namespace std;

/** ERRO: Assignment of read-only location

void flip_a (const double* const v, int N)
{
  int i;
  double placeholder;

  for (i = 0; i < N/2; i++)
    {
      placeholder = v[i];
      v[i] = v[N-i-1];
      v[N-i-1] = placeholder;
    }
}                                       **/



void flip_b (double* const v, int N)
{
  int i;
  double placeholder;

  for (i = 0; i < N/2; i++)
    {
      placeholder = v[i];
      v[i] = v[N-i-1];
      v[N-i-1] = placeholder;
    }
}

int main()
{
  int i;
  double a[3] = {1., 2., 3.}; // para efeitos de teste
  const double *v = a;  // ponteiro para doubles constantes (não podem ser modificados!)
  double* const V = a; // ponteiro constante para doubles (o ponteiro aponta sempre para o mesmo sítio!)

  cout << "double * const: [ ";

  for (i = 0; i < 3; i++)
  {
    /**
        flip_a (v, 3);
        cout << "const double* :" << v[i] << endl;
                                                    **/
    flip_b (V, 3);
    cout << V[i] << " ";
  }

  cout << "]" << "\nA declaração correta é a da alínea b) " << endl;

  return 0;
}
