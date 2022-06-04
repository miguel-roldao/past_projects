#include <iostream>
#include <iomanip> // setprecision
#include <math.h>
using namespace std;

int main()
{
  double x, sum=0;
  int i = 1;
  for (x = 0; x < 5.5; x += 0.1)
  /* a grande precisão dos doubles torna difícil avaliar a igualdade.
  O ciclo com x != 5.5 não para e entra em loop. Com desigualdade já não ocorre esse problema. :) */
  {
    sum += x;
    cout<<"ciclo "<<i<<": soma = "<<sum<<"    x = "<<x<<endl;
    i++;

    if(i==60)
      break;
  }
//  cout << "\n\nnextafter("<<setprecision(20)<<x<<",  "<<sum<<"): "<<"    "<<nextafter(x,sum)<<endl;

  return 0;
}
