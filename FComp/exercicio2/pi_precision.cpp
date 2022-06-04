#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
  float f = 4*atan(1);
  double d = 4*atan(1);
  cout << "Here is \u03C0 with 20 decimal digits:\n\n             3.14159265358979323846" << endl;
  cout <<"\u03C0 (float)  = "<<setprecision(21)<<f<<endl; // float precision is of 7 decimals
  cout <<"\u03C0 (double) = "<<setprecision(21)<<d<<endl;
  return 0;
}
