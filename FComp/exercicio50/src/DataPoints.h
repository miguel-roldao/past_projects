#ifndef H_DATAPOINTS_H
#define H_DATAPOINTS_H

#include <string>
#include "Vec.h"
#include "FCmatrix.h"
#include "EqSolver.h"

using namespace std;

class DataPoints {

  public:
    //constructors
    DataPoints();
    DataPoints(int, double*, double*);
    //virtual destructor
    virtual ~DataPoints();

    virtual double Interpolate(double x) {return 0.;}
    virtual void Draw();
    virtual void Print(string FILE="");

    void Nplots_increment();

  protected:
    int N; // number of data points
    double *x, *y; // arrays
    static int Nplots; //how many plots already done
};

#endif
