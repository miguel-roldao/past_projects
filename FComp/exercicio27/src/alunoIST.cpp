#include <iostream>
#include "alunoIST.h"
// #include "eu.h" :)


using namespace std;

void alunoIST::Print()
{
  cout<<"Name: "<<GetName()<<"    Born date(AAAAMMDD): "<<GetBornDate()<<endl;
  cout<<"alunoIST: "<<number<<"    curso: "<<course<<endl;
  //cout<<__PRETTY_FUNCTION__<<endl;
}

alunoIST** DoArray_IST(int N)
{
  alunoIST** ptr;
  ptr = new alunoIST* [N];
  for(int i = 0; i < N; i++)
    ptr[i] = new alunoIST;

  return ptr;
}

void ClearArray_IST(alunoIST** ptr, int N)
{
  for(int i = 0; i < N; i++)
    delete ptr[i];
  delete ptr;
}

void Dummy(alunoIST** aluno, const int N)
{
  for (int i = 0; i < N; i++)
    (*aluno[i]).Print();  // Print (método de aluno porque o da classe mãe é virtual)
}
