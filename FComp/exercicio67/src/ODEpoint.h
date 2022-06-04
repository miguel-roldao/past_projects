#ifndef H_ODEPOINT_H
#define H_ODEPOINT_H

#include <vector>

using namespace std;

class ODEpoint {
  public:
    ODEpoint();  // default constructor
    ~ODEpoint() {} // destructor
    ODEpoint(double tval, double* funct, int Ndimf); // usa um double *
    ODEpoint(double tval, vector<double> funct); // usa um vector
    ODEpoint(const ODEpoint&); // copy constructor

     // Funções de Acesso aos Membros da Classe
    vector<double> Get_Var_vec() const {return var; } // retorna y (as variáveis dependentes)
    double * Get_Var_ptr() const; // retorna o mesmo como double *
    double * Get_VarTime() const; // retorna y e depois t
    double * Get_TimeVar() const; // retorna t e depois y
    int GetNdim() const {return Ndim;} // retorna o número de variáveis dependentes
    double Get_Time() const {return t; } // retorna só a variável independente (t)
    void Set_Time(double tval) {t = tval; } // define o valor de t
    void Set_Var(vector<double> funct) {var = funct; Ndim = var.size();} // define o valor de y

     // Operadores
    ODEpoint & operator=(const ODEpoint& P);
    const double& operator[](int i) const {return var[i];}
    double& operator[] (int i) {return var[i];}
    void Print() const;

  private:
    double t;
    vector<double> var;
    int Ndim;

};

#endif
