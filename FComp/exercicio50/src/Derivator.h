#ifndef H_DERIVATOR_H
#define H_DERIVATOR_H

#include "Func1D.h"

class Derivator: public Func1D {
  public:

  Derivator(TF1 *f=NULL);
  ~Derivator(){}
  //Func1D Deriv_1();
  double Deriv_1(double x, double h = 5e-3, int type = 0);
  double Deriv_2(double x, double h = 5e-3, int type = 0);
  double Deriv_3(double x, double h = 5e-3, int type = 0);
  double Deriv_4(double x, double h = 5e-3, int type = 0);

};

#endif
