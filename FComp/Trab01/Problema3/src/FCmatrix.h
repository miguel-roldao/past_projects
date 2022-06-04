#ifndef H_FCMATRIX_H
#define H_FCMATRIX_H

#include "vec.h"
#include <vector>
#include <string>

using namespace std;

/* A classe FCmatrix é puramente virtual; é a classe mãe de FCmatrixFull e FCmatrixBanded.
   Aqui definem-se os métodos herdados por ambas as classes.                               */

class FCmatrix {

  protected:
    vector<Vec> M; // a matriz é um vetor de objetos da classe Vec
    string classname; // identifica a classe derivada

  public:
    // construtores

    FCmatrix(){} // default
    FCmatrix(double** fM, int fm, int fn){} // matriz fm x fn a partir de um ponteiro de ponteiro de doubles
    FCmatrix(double* fM, int fm, int fn){} //  matriz fm x fn a partir de um único ponteiro
    FCmatrix(vector<Vec>){} // matriz fm x fn a partir de um vetor de objetos da classe Vec

    //destrutor
    ~FCmatrix(){}

    string GetClassName() const; // método que retorna o nome da classe
    vector<Vec> GetM() const; // método que retorna a matriz M (vetor de objetos da classe Vec)

    // operadores
    virtual Vec& operator[] (int i) = 0; // retorna a linha i ao escrever [i]

    // métodos
    virtual int Get_nRows() const = 0;         // retorna o numero de linhas
    virtual int Get_nCols() const = 0;         // retorna o numero de colunas
    virtual Vec GetRow(int i = 0) const = 0;   // retorna uma linha
    virtual Vec GetCol(int i = 0) const = 0;   // retorna uma coluna
    virtual double Determinant() const = 0;    // calcula o determinante
    virtual Vec GetDiagonal() const = 0;       // Diagonal Principal
    virtual Vec GetUD() const = 0;             // 'UD' = Upper Diagonal
    virtual Vec GetLD() const = 0;             // 'LD' = Lower Diagonal
    virtual void Print() const;                // imprime a matriz (linha por linha)
    virtual int GetRowMax(int i=0) const = 0;  // na linha-i, retorna o índice da coluna com o elemento máximo em *valor absoluto*
    virtual int GetColMax(int j=0) const = 0;  // na coluna-j, return o índice da linha (>=j) para o qual a amplitude relativa de M [i][j] nessa linha é maior
};

#endif
