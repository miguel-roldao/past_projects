#ifndef H_FUNC1D_H
#define H_FUNC1D_H

#include <string>
#include "TGraph.h"
#include "TF1.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "Vec.h"
#include "FCmatrix.h"
#include "EqSolver.h"

class Func1D
{
  public:Func1D(TF1* ff=NULL);
  ~Func1D();
  void SetFunc(TF1*);
  TF1* GetFunc() const;
  void Draw();
  double Evaluate(double x);
  void Nplots_increment();

  protected:
    TF1* F;
    static int Nplots;

  };

#endif
