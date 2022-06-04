#ifndef H_TURMA_H
#define H_TURMA_H

using namespace std;

#include "alunoIST.h"

class Turma {
    string nome;    // nome da turma
    alunoIST** stu;  // ponteiro com alunos
    int nr;          // numero de alunos
  public:
    //constructor
    Turma(string s = "Looney Tunes", alunoIST** va = NULL, int N = 0){ nome = s; stu = va; nr = N;}
    //copy constructor
    Turma(const Turma &t){nome = t.nome; stu = t.stu; nr = t.nr;}
    Turma& operator = (const Turma &t){ return *this;} // copy assign
    ~Turma(){
      cout<<__PRETTY_FUNCTION__<<endl;
      for (int i = 0; i < nr; i++)
        delete stu[i];
      delete stu;
    } //destructor
    void AddAluno(alunoIST* al);
    void Print();
    alunoIST* FindAluno(int N){return stu[N];}
    int GetNr(){return nr;}
};

#endif
