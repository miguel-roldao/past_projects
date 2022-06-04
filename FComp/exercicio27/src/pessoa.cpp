#include <iostream>
#include "pessoa.h"
// #include "caeiro.h"
// #include "campos.h"
// #include "reis.h"

using namespace std;

void pessoa::SetName(string n)
{
  name = n;
  //cout<<__PRETTY_FUNCTION__<<endl;
}

void pessoa::SetBornDate(unsigned int d)
{
  DataN = d;
  //cout<<__PRETTY_FUNCTION__<<endl;
}

void pessoa::Print()
{
  cout<<"Name: "<<name<<"    Born date(AAAAMMDD): "<<DataN<<endl;
  //cout<<__PRETTY_FUNCTION__<<endl;
}

pessoa** DoArray(int N)
{
/*  pessoa* P[N];  // array de N ponteiros para pessoas
  pessoa* (*ptr)[N] = &P;   // ponteiro para o array
*/
  pessoa** ptr;
  ptr = new pessoa*[N];
  for (int i = 0; i < N; i++)
    ptr[i] = new pessoa;
  return ptr;
}

void ClearArray(pessoa** ptr, int N)
{
  for(int i = 0; i < N; i++)
    delete ptr[i];
  delete ptr;
}
