#include <iostream>

using namespace std;

class Base {
  private:
      int* i;

  public:
    Base() { cout<<__PRETTY_FUNCTION__<<endl; i = new int;}
    virtual ~Base() { cout<<__PRETTY_FUNCTION__<<endl; delete i;}
};

class Derived : public Base {
  private:
    float* f;

  public:
    Derived() { cout<<__PRETTY_FUNCTION__<<endl; f = new float;}
    ~Derived() { cout<<__PRETTY_FUNCTION__<<endl; delete f;}
};

int main()
{
  Base* obj = new Derived;

  delete obj;

  return 0;
}
