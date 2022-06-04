#include <iostream>
#include "../../exercicio27/src/pessoa.h"

int main()
{
  int N = 3;
  int nr, born;
  string name, cr;
  Turma A;

  for(int i = 0; i < N; i++)
  {
    cout<<"Aluno["<<i<<"] (nome) ";
    cin>>name;
    cout<<"Aluno["<<i<<"] (data de nascimento) ";
    cin>>born;
    cout<<"Aluno["<<i<<"] (numero) ";
    cin>>nr;
    cout<<"Aluno["<<i<<"] (curso) ";
    cin>>cr;

    alunoIST al(nr, cr);
    al.SetName(name);
    al.SetBornDate(born);

    alunoIST* p = &al;

    A.AddAluno(p);

    A.Print();
  }
  

  return 0;
}
