#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void randgen (double *s, int* i)
{
  s[*i] = (double)rand() /(double)RAND_MAX * 50 + 50;
  *i +=1;
}

int main()
{
  srand(time(NULL));

  int j = 0;
  int *i;
  i = &j;
  double *shuffle;
  shuffle = new double[100];


  while (j<100)
  {
    randgen(shuffle,i);
    cout<<shuffle[*i-1]<<endl;
  }

  delete[] shuffle;
  return 0;
}
