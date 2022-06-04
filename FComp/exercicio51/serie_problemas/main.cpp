#include <iostream>
#include <cmath>
#include <iomanip>
#include "../src/DataPoints.h"
#include "../src/Spline3Interpolator.h"
#include "../src/Func1D.h"
#include "../src/Derivator.h"
#include "../src/Integrator.h"

using namespace std;

int main ()
{
  TF1* f1 = new TF1("Cosseno","cos(x)",-2,2);
  double res_holder = 0;
  double error_holder = 0;
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
  S.Draw();

  Integrator I(0,M_PI/2, f1);
//  Integrator F(0,M_PI/2, f1);

//  double& result = res_holder;
//  double& error = error_holder;

  I.TrapezoidalRule(50, res_holder, error_holder);

  cout << "O integral pelo método dos trapézios é " << setprecision(6) << res_holder << " com um erro de " << error_holder << endl;

  I.SimpsonRule(50, res_holder, error_holder);

  cout << "O integral pelo método de Simpson é " << setprecision(17) << res_holder << " com um erro de " << error_holder << endl;
  //cout << "pp"<<endl;

  delete[] x;
  delete[] y;
//  delete f1;
  return 0;
}
