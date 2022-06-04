#include <iostream>
#include <vector>
#include "../src/polynomial.h"

using namespace std;

int main()
{
  vector<pair<int,int> > p, q, t;
  int tsize;

  for (int i = 0; i < 5; i++)
      p.push_back(make_pair(i + 3, 2*i));

  for (int i = 0; i < 7; i++)
          q.push_back(make_pair(i, i));

  Polynomial obj1(p);
  Polynomial obj2(q);

  cout << "*** TESTE ***" << endl << endl;

  cout << "p = ";
  obj1.Print();
  cout << "q = ";
  obj2.Print();
  cout << endl << "p + q = ";
  (obj1+obj2).Print();
  cout << endl << "p - q = ";
  (obj1-obj2).Print();
  cout << endl << "p * q = ";
  (obj1*obj2).Print();

  cout << endl << "Quantos termos tem o polinómio? ";
  cin >> tsize;

  Polynomial obj3(t);
  obj3.Fill(tsize);
  cout << endl << "O polinómio que introduziu foi t =  ";
  obj3.Print();

  Polynomial obj4 = obj3;
  cout << endl << "Uma cópia de t (usando o operador de copy constructor) é: ";
  obj4.Print();

  obj1 = obj2;
  cout << endl << "Uma cópia de q (usando o operador de assignement) é: ";
  obj2.Print();

  Polynomial obj5;


  return 0;
}
