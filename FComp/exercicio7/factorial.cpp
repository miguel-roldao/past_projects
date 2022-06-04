#include <iostream>
#include<cmath>
using namespace std;

long int fatorial(long int a) //alínea a
{
  int i;

  if(a==0)
    return 1;

  if(a<0)
    return -1;

  else
  {
  for (i = a-1; i > 1; i--)
      a *= i;

  return a;
  }
}

long int fatorial_recursive(long int a,long int b)//a-resultado parcial; b-ultimo numero multiplicado
{
  if( a==0 || a==1)
    return 1;

  if(a<0)
    return -1;

  long int j = a;
  long int i = --b;
  j *= i;
  i--;

  if(i > 0)
    j = fatorial_recursive(j,b);

  return j;
}

int main()
{
  int t = 1;
  long int a, a1, b;  //a1 - utilizado na função recursiva; b - valor dado inicialmente (não alterado);

  while (t==1)
  {
    cout << "Introduza um número natural:  ";
    cin >> a;

    if (a<=0 || a > 20)
      cout<<"Pah, escolhe outro!\n"<<endl;

    else
      {
        b = a1 = a;
        a = fatorial(a);
        cout<<b<<"! = "<<a<<endl;
        a1 = fatorial_recursive(a1,a1);
        cout<<b<<"! = "<<a1<<"  (recursivamente)"<<endl;
        t = 0;
      }
    }
  return 0;
}
