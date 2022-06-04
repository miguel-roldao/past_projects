#include <iostream>
#include "test_summation.h"
using namespace std;

int main (int argc, char ** argv)
{
  int N;

  if (argc == 2)
  {
    N = stoi(argv[1]);
    SUM(N);
    cout << N << endl;
  }

  else
    return -1;

  return 0;
}
