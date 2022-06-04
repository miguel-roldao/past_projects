#include <iostream>
#include <cmath>
using namespace std;

double calc_area(double r)
{
  double a;

  a = (4/3)*M_PI*r*r*r;

  return a;
}

int main()
{

double r;

cout << "Introduza o valor do raio:  ";
cin >> r;

cout <<"A área da esfera de raio " <<r<<" é "<<(4/3)*M_PI*r*r*r<<endl;

cout << "A área da esfera de raio "<<r<<" é "<<calc_area(r)<<endl;

return 0;
}
