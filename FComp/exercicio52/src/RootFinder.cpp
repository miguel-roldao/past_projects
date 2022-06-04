#include <iostream>
#include "RootFinder.h"
using namespace std;

double Bissection(double a, double b, double (*f)(double), double e)
{
  double c = a; // ponto médio

  if ((*f)(a) * (*f)(b) >= 0)
    {
      cout << "O intervalo dado não tem nenhuma raíz! \n";
      exit(EXIT_FAILURE);
    }

    while ((b-a) >= e)
    {
      c = (a+b)/2;

      if ((*f)(c) == 0.00)
        return c;

      else if ((*f)(c)*(*f)(a) < 0)
            b = c;

      else
            a = c;
    }

    return c;
}

double RegulaFalsi (double a, double b, double (*f)(double), int maxi)
{

  double c = a; // ponto que interseta o eixo das abcissas

  if ((*f)(a) * (*f)(b) >= 0)
    {
      cout << "O intervalo dado não tem nenhuma raíz! \n";
      exit(EXIT_FAILURE);
    }


  for (int i = 0; i < maxi; i++)
    {
        c = (a * (*f)(b) - b * (*f)(a) ) / ((*f)(b) - (*f)(a));

        if ((*f)(c) == 0.00)
          return c;

        else if ((*f)(c) * (*f)(a) < 0)
            b = c;

        else
            a = c;
    }

  return c;
}

double NewtonRaphson(double x, double (*f)(double), double (*df)(double), double e)
{
    double h = (*f)(x) / (*df)(x);

    while (abs(h) >= e)
    {
        h = (*f)(x)/(*df)(x);

        x = x - h;
    }

    return x;
}

double Secant(double a, double b, double (*f)(double), double e)
{
    double x0, x1;

    if ((*f)(a) * (*f)(b) >= 0)
      {
        cout << "O intervalo dado não tem nenhuma raíz! \n";
        exit(EXIT_FAILURE);
      }

      do {
           x0 = (a * (*f)(b) - b * (*f)(a)) / ((*f)(b) - (*f)(a));

           if ((*f)(a) * (*f)(x0) == 0.00)
              return x0;

           a = b;
           b = x0;

           x1 = (a * (*f)(b) - b * (*f)(a)) / ((*f)(b) - (*f)(a));
       }

    while (abs(x1 - x0) >= e);


  return x0;
}
