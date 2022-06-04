#include "../src/discretization_and_round.h"

using namespace std;

int main()
{
  Function * F = new Function(5e-7,1e-1);
  F->SetParam(3.);
  F->plot();
  return 0;
}
