#ifndef H_FCMATRIX_H
#define H_FCMATRIX_H

#include "../../exercicio41/src/vec.h"
#include <vector>
#include <string>

using namespace std;

class FCmatrix {
  protected:
    vector<Vec> M; //the matrix is a vector of Vec objects...
    string classname; //give the class a name...

  public:
    //constructors
    FCmatrix(){}
    FCmatrix(double** fM, int fm, int fn){} //matrix fm x fn given from pointer of pointers
    FCmatrix(double* fM, int fm, int fn){} //matrix fm x fn given as single pointer (what length ?!)
    FCmatrix(vector<Vec>){} //matrix fm x fn given as vector of Vec
    //destructor
    ~FCmatrix(){}

    string GetClassName() const;
    vector<Vec> GetM() const;

    // operators
    virtual Vec& operator[] (int i) = 0; //get a row by giving índex inside []

    //methods
    virtual int Get_nRows() const = 0;   //retorna numero de linhas
    virtual int Get_nCols() const = 0;   //retorna numero de colunas
    virtual Vec GetRow(int i = 0) const = 0; //retorna linha
    virtual Vec GetCol(int i = 0) const = 0; //retorna coluna
    virtual double Determinant() const = 0;
    virtual int GetRowMax(int i=0) const = 0;  // in row-i, return column-index of max element (in absolute value)
    virtual int GetColMax(int j=0) const = 0; // in column-j, return row-index (>=j) for which relative amplitude of M ij on the row is highest.
    virtual void Print() const; //print e.g. row by row (GetRow to the rescue...)
};

#endif
