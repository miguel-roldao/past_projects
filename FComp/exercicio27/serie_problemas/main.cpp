#include <iostream>
#include "pessoa.h"
using namespace std;

int main()
{
  /*pessoa alex;
  alex.GetName();
  alex.GetBornDate();
  alex.Print();
  alex.SetName("Alex");
  alex.SetBornDate(20000429);
  alex.Print();*/
  /*pessoa P[5];
  P[0].Print();*/

  int N = 5;

  pessoa** ptr = DoArray(N);

  (*ptr[0]).SetName("Afonso");
  (*ptr[0]).SetBornDate(20010728);
  (*ptr[1]).SetName("Francisca");
  (*ptr[1]).SetBornDate(20010212);
  (*ptr[2]).SetName("André");
  (*ptr[2]).SetBornDate(20010917);
  (*ptr[3]).SetName("Juna");
  (*ptr[3]).SetBornDate(20010815);
  (*ptr[4]).SetName("Rodrigo");
  (*ptr[4]).SetBornDate(20010527);


  for(int i = 0; i < N; i++)
  {
    (*ptr[i]).Print();
  }

  ClearArray(ptr, N);

  return 0;
}
