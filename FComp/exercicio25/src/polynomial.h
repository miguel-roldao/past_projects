#ifndef H_POLYNOMIAL_H
#define H_POLYNOMIAL_H

using namespace std;

class Polynomial{

  private:
    vector<pair<int,int> > poly;

  public:

    Polynomial() // default constructor
      {
        vector<pair<int, int> >() ;
      }

    Polynomial(vector<pair<int,int> > p) // constructor
      {
        poly = p;
      }

    Polynomial (const Polynomial &q) // copy constructor
     {
       poly = q.poly;
     }

    Polynomial operator= (const Polynomial &q) // assignement operator
    {
        return *this;
    }

    void Print();
    void Fill(int size);

    Polynomial operator+ (const Polynomial& );
    Polynomial operator- (const Polynomial& );
    Polynomial operator* (const Polynomial& );
};

#endif
