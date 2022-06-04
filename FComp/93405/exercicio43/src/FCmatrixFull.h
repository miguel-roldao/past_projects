#ifndef H_FCMATRIXFULL_H
#define H_FCMATRIXFULL_H

#include "FCmatrix.h"

using namespace std;

class FCmatrixFull : public FCmatrix
{
  public:
    // constructors
    FCmatrixFull();
    FCmatrixFull(double** fM, int fm, int fn);
    FCmatrixFull(double* fM, int fm, int fn);
    FCmatrixFull(vector<Vec>); // copy constructor
    FCmatrixFull(const FCmatrixFull&); // copy construtor 2
    //destructor
    ~FCmatrixFull(){}
    // operators
    FCmatrixFull & operator=(const FCmatrix &);
    FCmatrixFull operator+(const FCmatrix &) const; // add 2 matrices of any kind
    FCmatrixFull operator-(const FCmatrix &) const; // sub 2 matrices of any kind
    FCmatrixFull operator*(const FCmatrix &) const; // mul 2 matrices of any kind
    FCmatrixFull operator*(double lambda) const; // mul matrix of any kind by scalar
    Vec operator*(const Vec &) const; // mul matrix by Vec...

    // virtual inherited..
    Vec& operator[] (int i);
    int Get_nRows() const;   //retorna numero de linhas
    int Get_nCols() const;   //retorna numero de colunas
    double Determinant() const;
    Vec GetRow(int i) const; // retrieve row i
    Vec GetCol(int i) const; // retrieve column i...
    int GetRowMax(int i=0) const;  // in row-i, return column-index of max element (in absolute value)
    int GetColMax(int j=0) const; // in column-j, return row-index (>=j) for which relative amplitude of M ij on the row is highest.
    void Print() const;
    // swap 2 given rows in the matrix...
    void swapRows(int,int);
    bool IsSquare();

  };

  #endif
