#ifndef H_SPLINE3INTERPOLATOR_H
#define H_SPLINE3INTERPOLATOR_H

#include "DataPoints.h"
#include "EqSolver.h"
#include "TGraph.h"
#include "TF1.h"
#include "TStyle.h"
#include "DataPoints.h"
#include "TApplication.h"
#include "TCanvas.h"

using namespace std;

class Spline3Interpolator : public DataPoints {

  public:
    Spline3Interpolator(int n=0, double *a=NULL, double *b=NULL);  // , TF1* fF0=NULL);
    ~Spline3Interpolator();
    void SetCurvatureLines();
    double Interpolate(double fx);
    void Draw();
    TF1* GetInterpolationFunction() { return FInterpolator;}
    // void SetFunction(TF1* function);

    // void Print(string FILE="");  // print results to file (optional)

  private:
    Vec K;
    double fInterpolator(double *fx, double *par) {return Interpolate(fx[0]);}
    TF1* FInterpolator;
  //  TF1* F0;

};


#endif
