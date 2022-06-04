#include <iostream>
using namespace std;

void convert2bin(long int n, char *bin)
{

  int i = 0;
  int j = 0;
  char placeholder;

  if (n == 0)
    bin[i] = 48; // 48 (ASCII) = 0;

  while (n != 0)
    {
        bin[i] = n % 2;
        n = n/2;
        i++;
    }

    // Coloca o terminador no final
    bin[i+1] = 0; // ASCII '0', não o caracter 0!

  for (j = 0; j < i/2; j++)
    {
      placeholder = bin[j];
      bin[j] = bin[i-j-1];
      bin[i-j-1] = placeholder;
    }
}


int main(int argc, char ** argv)
{
    long int n;
    int i = 0;
    char *bin;
    bin = new char [100];
    cout << "Introduza um número inteiro: ";
    cin >> n;

    convert2bin(n, bin);

    cout << n << " (10) = ";
    for (i = 0; bin[i] != 0; i++) cout << bin[i];
    cout << " (2)" << endl;

    delete bin;
    return 0;
}
