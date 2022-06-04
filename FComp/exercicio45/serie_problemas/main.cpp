#include <iostream>
#include "DataPoints.h"
#include "Vec.h"
#include "FCmatrix.h"
#include "EqSolver.h"
#include "Spline3Interpolator.h"

using namespace std;

int main()
{
  double* xx = new double[10];
  double* yy = new double[10];

  xx[0] = 0;
  xx[1] = 1;
  xx[2] = 2;
  xx[3] = 3;
  xx[4] = 4;
  xx[5] = 5;
  xx[6] = 6;
  xx[7] = 7;
  xx[8] = 8;
  xx[9] = 9;
  yy[0] = 0;
  yy[1] = 0;
  yy[2] = -3;
  yy[3] = -4;
  yy[4] = -2;
  yy[5] = 0;
  yy[6] = 1.2;
  yy[7] = 9;
  yy[8] = 6;
  yy[9] = 2;


/*
  double* xx = new double[5];
  double* yy = new double[5];

  for(int i = 0; i < 5; i++)
  {
    xx[i] = (double)i;
    yy[i] = (double)i * (double)i;
  }*/

  Spline3Interpolator D(10, xx, yy);


  D.Draw();


  return 0;
}
