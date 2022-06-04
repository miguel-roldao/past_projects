#ifndef H_DISCRETIZATION_AND_ROUND_H
#define H_DISCRETIZATION_AND_ROUND_H

#include "TF1.h"

class Function {
  TF1 * g;
public:
  Function(double a, double b);
  float DRError(double *x, double *p);
  void SetParam(float p);
  void plot();
  float GetRand();
  ~Function() { delete g; }
};

#endif
