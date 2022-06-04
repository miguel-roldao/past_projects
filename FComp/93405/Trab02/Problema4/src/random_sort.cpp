#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void bubbleSort(double* arr, int N)
{
  int i, k;
  double temp;
  for (i = 0; i < N-1; i++)
  {
    for (k = 0; k < N-i-1; k++)
    {
      if (arr[k] > arr[k+1])
      {
        temp = arr[k];
        arr[k] = arr[k+1];
        arr[k+1] = temp;
      }
    }
  }
}

int main()
{
  ofstream file;
  file.open ("random.txt");

  int N = 100;

  srand(time(NULL));

  double random[100];

  for(int i = 0; i < N; i++)
  {
    random[i] = (double)rand() /(double)RAND_MAX * 10;  // de 0 a 10 why not?
    cout << random[i] << "\n";
  }

  bubbleSort(random, N);

//  cout << "\nAgora ordenados!!!\n\n";
/*
  for(int i = 0; i < N; i++)
    cout << random[i] << "\n";*/

  for(int i = 0; i < N; i++)
    file << random[i] << "\n";

  file.close();
  
  return 0;
}
