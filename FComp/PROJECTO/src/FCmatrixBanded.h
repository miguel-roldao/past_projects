#ifndef H_FCMATRIXBANDED_H
#define H_FCMATRIXBANDED_H

#include "FCmatrix.h"

using namespace std;

/* Os objetos da classe FCmatrixFull são matrizes tridiagonais de dimensões n x n com componentes reais
   Os métodos aqui definidos são usados na classe EqSolver para resolver sistemas de equações lineares. */

class FCmatrixBanded : public FCmatrix
{
  public:
    // constructors
    FCmatrixBanded(); // default
    FCmatrixBanded(double** fM, int fm, int fn); // matriz fm x fn a partir de um ponteiro de ponteiro de doubles
    FCmatrixBanded(double* fM, int fm, int fn); // matriz fm x fn a partir de um ponteiro único de doubles
    FCmatrixBanded(Vec ld, Vec md, Vec ud); // matrix fm x fn a partir das três diagonais
    FCmatrixBanded(vector<Vec>); // copy constructor (a partir de um vetor de objetos da classe Vec)
    FCmatrixBanded(const FCmatrixBanded& ); // copy construtor 2 (a partir de outra FCmatrixBanded)
    ~FCmatrixBanded(){} // destructor

    // operadores
    FCmatrixBanded operator=(const FCmatrixBanded &); // assignment operator
    FCmatrixBanded operator+(const FCmatrixBanded &) const; // soma duas matrizes
    FCmatrixBanded operator-(const FCmatrixBanded &) const; // subtrair duas matrizes
    // FCmatrixBanded operator*(const FCmatrixBanded &) const; // não é necessário multiplicar duas matrizes tridiagonais
    FCmatrixBanded operator*(double lambda) const; // multiplica a matriz por um escalar real
    Vec operator*(const Vec &) const; // multiplica a matriz por um vetor
    Vec& operator[] (int i); // retorna uma das diagonais (0, 1 ou 2 | a, b ou c)

    // herança
    int Get_nRows() const;  // retorna numero de linhas
    int Get_nCols() const;  // retorna numero de colunas
    Vec GetRow(int) const;  // retorna a linha i
    Vec GetCol(int) const; //  retorna a coluna j
    void Print() const; // imprime a matriz
    double Determinant() const; // calcula o determinante
    int GetRowMax(int i=0) const;  // na linha-i, retorna o índice da coluna com o elemento máximo em *valor absoluto*
    int GetColMax(int j=0) const; // na coluna-j, return o índice da linha (>=j) para o qual a amplitude relativa de M [i][j] nessa linha é maior
    Vec GetDiagonal() const; // retorna a diagonal principal
    Vec GetUD() const; // retorna a diagonal superior (de uma matriz quadrada) ['UD' = Upper Diagonal]
    Vec GetLD() const;  // retorna a diagonal inferior (de uma matriz quadrada) ['LD' = Lower Diagonal]
};

#endif
