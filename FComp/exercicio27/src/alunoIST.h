#ifndef H_ALUNOIST_H
#define H_ALUNOIST_H

using namespace std;

#include "pessoa.h"

class alunoIST : public pessoa {
    int number;
    string course;
  public:
    // default constructor (numero e curso do aluno)
    alunoIST(int n = 93405, string curso = "MEFT"){number = n; course = curso;};
    // copy constructor & copy assign
    alunoIST(const alunoIST &a1){number = a1.number; course = a1.course;}
    alunoIST& operator = (const alunoIST &a1){return *this;}

    void SetNumber(int n){ number = n;}
    int GetNumber(){return number;}
    void SetCourse(string c){course = c;}
    string GetCourse(){return course;}
    void Print();
};

#endif
