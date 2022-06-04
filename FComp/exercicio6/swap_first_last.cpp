#include <iostream>
using namespace std;

void swap(long int n, char *swapped)
{
  int i = 0;
  char placeholder;

  // Escreve o número como uma sequência de chars
  while (n != 0)
    {
      swapped[i] = (n % 10) + 48; // Converte para números ASCII
      n = n/10;
      i++;
    }

    // Coloca o terminador no final
    swapped[i] = 0; // ASCII '0', não o caracter 0!

  // Escreve o número pela ordem certa

  for (int j = 0; j < i/2; j++)
    {
      placeholder = swapped[j];
      swapped[j] = swapped[i-j-1];
      swapped[i-j-1] = placeholder;
    }

  placeholder = swapped[0];
  swapped[0] = swapped[i-1]; // troca com o último caracter (não-nulo)
  swapped[i-1] = placeholder;

}


int main(int argc, char ** argv)
{
    long int n;
    char *swapped;
    swapped = new char [50];
    cout << "Introduza um número inteiro (positivo): ";
    cin >> n;

    if (n < 0)
    {
      cout << "Introduziu um número inválido! Escolha outro: ";
      cin >> n;
    }

    swap(n, swapped);

    cout << "O número que introduziu, com o primeiro e último dígitos trocados é: ";
    for (int i = 0; swapped[i] != 0; i++) cout << swapped[i];
    cout << endl;

    delete swapped;
    return 0;
}
