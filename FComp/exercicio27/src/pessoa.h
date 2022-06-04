#ifndef H_PESSOA_H
#define H_PESSOA_H

using namespace std;
class pessoa {
  //private
    string name; //nome
    unsigned int DataN; //data de nascimento
  public:
    // constructor (nome do aluno, data de nascimento - AAAAMMDD)
    pessoa(string n = "Miguel", unsigned int d = 20000721){ name = n; DataN = d; /*cout<<__PRETTY_FUNCTION__<<endl;*/}
    void SetName(string n); //definir o nome...
    void SetBornDate(unsigned int d); //agora a data de nascimento
    string GetName(){/*cout<<__PRETTY_FUNCTION__<<endl;*/ return name;} //obter o nome
    unsigned int GetBornDate(){ /*cout<<__PRETTY_FUNCTION__<<endl;*/ return DataN;}//agora a data de nascimento.
    virtual void Print(); // print do nome e data de nascimento.
};

#endif

// Funções Auxiliares

pessoa** DoArray(int N);
void ClearArray(pessoa** ptr, int N);
