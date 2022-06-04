#include <iostream>
#include <cmath>
#include "Integrator.h"
#include "IntegratorMC.h"
#include "Groot.h"

using namespace std;

int main()
{

  /* A área da secção é obviamente igual ao integral da função y = 1 + x^2  entre -1 e 1*/


  TF1* w1 = new TF1("f1","1 + x * x");
  TF1* p = new TF1("pdf", "1"); //pdf próxima de w1
  TF1* xofy = new TF1("xofy", "sqrt( x - 1)"); // inversa de w1 para x > 0
  double xbeg = -1;
  double xend = 1;
  double xxbeg[] = {0};
  double xxend[] = {xend};

  Integrator I(xbeg,xend,w1);
  IntegratorMC M(xxbeg,xxend,w1);

  double result;
  double error;

  I.SimpsonRule(10, result, error);

  cout << "A área da secção é igual a " << result << " +/- " << error << " (SimpsonRule)\n";

  M.ImportanceSampling(10000, result, error, p, xofy);   // Não funciona... Boa

  /*
   Como a função é par, podemos integrar de 0 a 1 e considerar apenas w1 para x > 0
   sendo que o integral obtido tem de ser multiplicado por 2 no final assim como o erro;
  */

  cout << "A área da secção é igual a " << result << " +/- " << error << " (ImportanceSampling)\n";

  xxbeg[0] = xbeg;
  M.SetBoundaries(xxbeg,xxend);

  M.UniformRandom(10000, result, error);

  cout << "A área da secção é igual a " << result << " +/- " << error << " (AcceptanceRejection)\n";



  return 0;
}
