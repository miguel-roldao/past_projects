#ifndef H_NEVILLE_INTERPOLATOR_H
#define H_NEVILLE_INTERPOLATOR_H

#include "DataPoints.h"
#include "TF1.h"
using namespace std;

class NevilleInterpolator: public DataPoints {

  public:
    NevilleInterpolator(int n=0, double *a=NULL, double *b=NULL, TF1* fF0=NULL);
    ~NevilleInterpolator() {}
    double Interpolate(double x);
    void Draw();  //draw everything (points and interpolation function)
    TF1* GetInterpolationFunction() {return FInterpolator;}
    void SetFunction(TF1* function);

    // void Print(string FILE="");  // print results to file (optional)

  private:

    double fInterpolator(double *fx, double *par) {return Interpolate(fx[0]);}
    TF1* FInterpolator; //interpolation function
    TF1* F0;  //eventual underlying function};

  };

#endif
