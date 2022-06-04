#include <iostream>
#include <vector>
#include "array2vec.h"
using namespace std;

int main ()
{
  int *a = new int[6]{1, 10, 5, 6, 9, 3};
  int *b = new int[5]{2, 5, 5, 7, 3};

  // Alínea a)

  cout << "a = { ";

  for (int i = 0; i < 6; i++)
    cout <<  array2vec(6, a)[i] << " ";

  cout << "}" << endl;

  cout << "b = { ";

  for (int i = 0; i < 5; i++)
    cout <<  array2vec(5, b)[i] << " ";

    cout << "}" << endl << endl;


  // Alínea b)

  cout << "Por ordem crescente: ";

  cout << "  a = { ";

  for (int i = 0; i < 6; i++)
    cout <<  array2vecs(6, a, 1)[i] << " ";

  cout << "}" << endl;

  cout << "                       b = { ";

  for (int i = 0; i < 5; i++)
    cout <<  array2vecs(5, b, 1)[i] << " ";

    cout << "}" << endl << endl;


  cout << "Por ordem decrescente: ";

  cout << "a = { ";

    for (int i = 0; i < 6; i++)
      cout <<  array2vecs(6, a, -1)[i] << " ";

  cout << "}" << endl;

  cout << "                       b = { ";

  for (int i = 0; i < 5; i++)
    cout <<  array2vecs(5, b, -1)[i] << " ";

  cout << "}" << endl;

  // Alínea c)

  cout << "max(a) = " << array2vecmax(6, a) << endl;
  cout << "max(b) = " << array2vecmax(5, b) << endl << endl;

  // Alínea d)

  (array2vecfind(6, a, 7) >= 0 ? cout << "Em a, o número 7 está na posição: = " << array2vecfind(6, a, 7) << endl : cout << "O número 7 não existe em a." << endl);
  (array2vecfind(5, b, 7) >= 0 ? cout << "Em b, o número 7 está na posição " << array2vecfind(5, b, 7) <<  "." << endl : cout << "O número 7 não existe em b." << endl);

  delete[] a;
  delete[] b;

  return 0;
}
