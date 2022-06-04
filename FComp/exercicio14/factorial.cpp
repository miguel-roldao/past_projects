#include <iostream>
#include<cmath>
using namespace std;

void factorial_ref (int &fact, int n ) //alínea a
{

  if(n==0)
    fact = 1;

  if(n<0)
    fact = -1;

  else
  {
    while(n != 1)
      {
        n--;
        fact *= n;
      }
  }
}

void factorial_pont (int *fact, int n) //alínea b
{
  if(n==0)
    *fact = 1;

  if(n<0)
    *fact = -1;

  else
  {
    while(n != 1)
      {
        n--;
        *fact *= n;
      }
  }
}

int main()
{
  int t = 1;
  int a, x;
  int &b = (int &)a;
  int *a1 = &a;  //a1 - utilizado na alinea b);

  while (t==1)
    {
    cout << "Introduza um número natural:  ";
    cin >> a;
    x = a;

    if (a<=0 || a > 14)
      cout<<"Pah, escolhe outro!\n"<<endl;

    else
      {
      //  b = a1 = a;
        factorial_ref(b, a);
        cout<<x<<"! = "<<b<<endl;

        a = x; // reinicialização do a

        factorial_pont(a1,a);
        cout<<x<<"! = "<<*a1<<" (alinea b)"<<endl;  // dá a posição de memoria??
        t = 0;
      }
    }
  return 0;
}
