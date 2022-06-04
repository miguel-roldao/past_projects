#ifndef H_FCMATRIXBANDED_H
#define H_FCMATRIXBANDED_H

//#include <vector>
#include "FCmatrix.h"

using namespace std;

class FCmatrixBanded : public FCmatrix
{
  public:
    // constructors
    FCmatrixBanded();
    FCmatrixBanded(double** fM, int fm, int fn);
    FCmatrixBanded(double* fM, int fm, int fn);
    FCmatrixBanded(vector<Vec>);
    // copy constructor
    FCmatrixBanded(const FCmatrixBanded& );
    //destructor
    ~FCmatrixBanded(){}
    // operators
    FCmatrixBanded operator=(const FCmatrixBanded &); // equal 2 matrices of any kind
    FCmatrixBanded operator+(const FCmatrixBanded &) const; // add 2 matrices of any kind
    FCmatrixBanded operator-(const FCmatrixBanded &) const; // sub 2 matrices of any kind
    //FCmatrixBanded operator*(const FCmatrixBanded &) const; // mul 2 matrices of any kind
    FCmatrixBanded operator*(double lambda) const; // mul matrix of any kind by scalar
    Vec operator*(const Vec &) const; // mul matrix by Vec
    Vec& operator[] (int i);

    // virtual inherited
    int Get_nRows() const;   //retorna numero de linhas
    int Get_nCols() const;   //retorna numero de colunas
    Vec GetRow(int) const; // retrieve row i
    Vec GetCol(int) const; // retrieve column i
    double Determinant() const;
    int GetRowMax(int i=0) const;  // in row-i, return column-index of max element (in absolute value)
    int GetColMax(int j=0) const; // in column-j, return row-index (>=j) for which relative amplitude of M ij on the row is highest.
    void Print() const; //print e.g. row by row (GetRow to the res
};

#endif
