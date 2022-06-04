#include <iostream>
#include "../src/DataPoints.h"
#include "../src/Spline3Interpolator.h"
#include "../src/Func1D.h"
#include "../src/Derivator.h"

using namespace std;

int main ()
{
  TF1* f1 = new TF1("Cosseno","cos(x)",-2,2);

  Func1D Func_f(f1);
  Func_f.GetFunc()->SetTitle("cos(x)");
  Func_f.Draw();
  Derivator f_linha(f1);

  double* x = new double[40];
  double* y = new double[40];

  for(int i = 0; i < 40; i++)
    {
      //  cout<< "cos[" << (double)i*0.01 - 2 << "] = " << f_linha.Deriv_1( (double)i*0.1-2.5) << endl;
      x[i] = (double)i * 0.1 - 2;
      y[i] = f_linha.Deriv_1(((double)i*0.1) - 2);
    }

  Spline3Interpolator S(40,x,y);
  S.Nplots_increment();
  S.Draw();

  delete f1;
  delete[] x;
  delete[] y;
  return 0;
}
