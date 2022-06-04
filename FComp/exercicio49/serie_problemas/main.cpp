#include <iostream>
#include "../src/Func1D.h"


using namespace std;

int main ()
{
  TF1* f1 = new TF1("Cosseno","cos(x)",-2,2);

  Func1D Func_f(f1);

  Func_f.Draw();

  delete f1;
  return 0;
}
