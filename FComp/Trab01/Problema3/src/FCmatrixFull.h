#ifndef H_FCMATRIXFULL_H
#define H_FCMATRIXFULL_H

#include "FCmatrix.h"

using namespace std;

/* Os objetos da classe FCmatrixFull são matrizes genéricas de dimensões m x n cpm componentes reais
   Os métodos aqui definidos são usados na classe EqSolver para resolver sistemas de equações lineares. */

   // TESTAR GetRowMax, GetColMax, GetDiagonal, GetUD, GetLD, operadores +, -, ...


class FCmatrixFull : public FCmatrix
{
  public:
    // construtores
    FCmatrixFull(); // default
    FCmatrixFull(double** fM, int fm, int fn); // matriz fm x fn a partir de um ponteiro de ponteiro de doubles
    FCmatrixFull(double* fM, int fm, int fn);  // matriz fm x fn a partir de um ponteiro único de doubles
    FCmatrixFull(vector<Vec>); // copy constructor (a partir de um vetor de objetos da classe Vec)
    FCmatrixFull(const FCmatrixFull&); // copy construtor 2 (a partir de outra FCmatrixFull)

    // destrutor
    ~FCmatrixFull(){}

    // operadores
    FCmatrixFull & operator=(const FCmatrix &); // assignment operator
    FCmatrixFull operator+(const FCmatrix &) const; // soma matricial
    FCmatrixFull operator-(const FCmatrix &) const; // subtração matricial
    FCmatrixFull operator*(const FCmatrix &) const; // multiplicação matricial
    FCmatrixFull operator*(double lambda) const; // multiplicação de uma matriz por um escalar
    Vec operator*(const Vec &) const; // multiplicação de uma matriz por um vetor

    // herança
    Vec& operator[] (int i); // retorna a linha i (com M[i][j] acede-se à componente ij da matriz)
    int Get_nRows() const;   // retorna o numero de linhas
    int Get_nCols() const;   // retorna o numero de colunas
    double Determinant() const; // calcula o determinante
    Vec GetRow(int i) const; // retorna a linha i
    Vec GetCol(int i) const; // retorna a coluna i
    int GetRowMax(int i=0) const;  // na linha-i, retorna o índice da coluna com o elemento máximo em *valor absoluto*
    int GetColMax(int j=0) const; // na coluna-j, return o índice da linha (>=j) para o qual a amplitude relativa de M [i][j] nessa linha é maior
    void Print() const; // imprime a matriz
    Vec GetDiagonal() const; // retorna a diagonal principal (de uma matriz quadrada)
    Vec GetUD() const; // retorna a diagonal superior (de uma matriz quadrada) ['UD' = Upper Diagonal]
    Vec GetLD() const; // retorna a diagonal inferior (de uma matriz quadrada) ['LD' = Lower Diagonal]

    bool IsSquare() const; // testa se a matriz é quadrada
    void swapRows(int i, int j); // troca duas linhas da matriz

  };

  #endif
