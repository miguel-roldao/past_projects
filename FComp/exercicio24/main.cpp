#include <iostream>

using namespace std;

class complexo{
  private:
    double realPart;
    double imagPart;

  public:
  //  complexo(){realPart = 0; imagPart = 0;}  // default constructor
    complexo (double r = 0, double i = 0){ realPart = r; imagPart = i;}  // constructor

    void setComplex (double r, double i){ realPart = r; imagPart = i;}

    void printComplex();

    complexo operator + (complexo a){
      return complexo((realPart + a.realPart),(imagPart + a.imagPart));
    }

    complexo operator - (complexo a){
      return complexo((realPart - a.realPart),(imagPart - a.imagPart));
    }

    complexo operator * (complexo a){
      return complexo((realPart * a.realPart - imagPart * a.imagPart),(realPart * a.imagPart + imagPart * a.realPart));
    }
};

void complexo::printComplex(){
  cout<<realPart;
  if (imagPart == -1)
    cout<<"-i";
  else if (imagPart < 0)
    cout<<imagPart<<"i";
  if (imagPart > 0)
    {
      cout<<"+";
      if (imagPart == 1)
        cout<<"i";
      else
        cout<<imagPart<<"i";
    }
}

int main()
{
  complexo a, b;
  double p, q;
  cout<<"z(realPart) = ";
  cin >> p;
  cout<<"z(imagPart) = ";
  cin >> q;
  a.setComplex(p,q);
  cout<<"w(realPart) = ";
  cin >> p;
  cout<<"w(imagPart) = ";
  cin >> q;
  b.setComplex(p,q);
  complexo c = a + b;
  cout<<"\nz + w = ";
  c.printComplex(); cout<<endl;
  //  a.setComplex(1,1); b.setComplex(-1,2);
  c = a - b;
  cout<<"z - w = ";
  c.printComplex(); cout<<endl;
  c = a * b;
  cout<<"z * w = ";
  c.printComplex(); cout<<endl;

  cout<<endl;
  return 0;
}
