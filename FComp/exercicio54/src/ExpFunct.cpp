#include <iostream>
#include "TCanvas.h"
#include "TH1D.h"
#include "TF1.h"
#include "TRandom3.h"
#include <cmath>

using namespace std;

double ExpFunctgen(double ga)
{
  TRandom3 rgen(0);

  return (-log(1 - rgen.Uniform(0,1))/ga);
}
