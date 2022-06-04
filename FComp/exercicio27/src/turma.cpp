#include <iostream>
#include "turma.h"

using namespace std;

void Turma::AddAluno(alunoIST* al)
{
  nr++;
  alunoIST** cpy;
  cpy = new alunoIST* [nr-1];
  //cpy = stu;

  for (int i = 0; i < (nr-1); i++)
    cpy[i] = stu[i];
  cpy[nr-1] = al;

  delete stu;
  stu = new alunoIST* [nr];

  for (int i = 0; i < nr; i++)
    stu[i] = cpy[i];
//  stu[nr-1] = al;

  delete cpy;
}

void Turma::Print()
{
  cout<<"numero de alunos: "<<nr<<endl;
  for(int i = 0; i < nr; i++)
    (*stu[i]).Print();
}
