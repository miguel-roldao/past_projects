#include <algorithm>
#include <iostream>
#include <vector>
#include "polynomial.h"

bool sortbysecond(const pair<int,int> &a, // chamado por sort() em Order()
                  const pair<int,int> &b)
{
    return (a.second < b.second);
}

void Polynomial::Fill(int size)
{
  int a, b;

    for (int i = 0; i < size; i++)
    {
      cout << "Introduza o coeficiente de a_" << i << " : " ;
      cin >> a;
      cout << "Introduza o expoente de a_" << i << " : " ;
      cin >> b;
      poly.push_back(make_pair(a,b));
    }

    cout << endl;
}

void Order(vector<pair<int,int> > &p)
{
   sort(p.begin(), p.end(), sortbysecond);
}

void Squeeze(vector<pair<int,int> > &p)
{

 for (int i = 0; i < p.size(); i++)
    {
      if (p[i].first == 0)
          p.erase (p.begin() + i); // elimina os monomios nulos

      for (int j = 0; j < p.size(); j++)
        {
          if (p[i].second == p[j].second && i != j)
            {
              p[i].first += p[j].first; // soma os termos com o mesmo expoente
              p.erase (p.begin() + j); // e apaga os monomios repetidos
            }
        }

    }
}

void Polynomial::Print()
{

  Order(poly);
  Squeeze(poly);

  /** O primeiro termo é tratado à parte, porque o sinal que o precede depende apenas do seu sinal e não também do sinal do termo seguinte **/

  if (poly[0].first != 0)
    {
      if (poly[0].first == 1 || poly[0].first == -1 && poly[0].second != 0)
          cout << "x";

      if (poly[0].second == 0)
          cout << poly[0].first;

      else if (poly[0].first != 1 && poly[0].first != -1)
        cout << poly[0].first << "x";

      if (poly[1].first != 0 && poly.size() > 1)
        (poly[1].first >= 0 ? cout << " + " : cout << " - ");
    }

    for (int i = 1; i < poly.size(); i++)
    {

      if (poly[i].first != 0)
        {

          if (poly[i].first == 1 || poly[i].first == -1 && poly[i].second != 0) // imprime "x" em vez de (-)1x
              cout << "x";

          if (poly[i].second == 0) // não imprime zero como expoente
              cout << poly[i].first;

          else if (poly[i].first != 1 && poly[i].first != -1 && poly[i].first > 0) // imprime x se x é positivo
            cout << poly[i].first << "x";

          else if (poly[i].first != 1 && poly[i].first != -1 && poly[i].first < 0) // e -x se x é negativo
              cout << -poly[i].first << "x";

          if (poly[i].second != 0 && poly[i].second != 1)
                  cout << "^" << poly[i].second;

          if (i != poly.size() - 1 && poly[i].first != 0) // imprime os sinais certos
              (poly[i+1].first >= 0 ? cout << " + " : cout << " - ");
        }
    }

    cout << endl;
}

Polynomial Polynomial::operator+ (const Polynomial &rhs)
{

  Polynomial p;

  for (int i = 0; i < poly.size(); i++)
    p.poly.push_back(make_pair (poly[i].first, poly[i].second));

  for (int i = 0; i < rhs.poly.size(); i++)
    p.poly.push_back(make_pair (rhs.poly[i].first, rhs.poly[i].second));

  Squeeze(p.poly);
  Order(p.poly);

  return p;
}

Polynomial Polynomial::operator- (const Polynomial &rhs)
{

  Polynomial p;

  for (int i = 0; i < poly.size(); i++)
    p.poly.push_back(make_pair (poly[i].first, poly[i].second));

  for (int i = 0; i < rhs.poly.size(); i++)
    p.poly.push_back(make_pair (-rhs.poly[i].first, rhs.poly[i].second));

  Squeeze(p.poly);
  Order(p.poly);

  return p;
}

Polynomial Polynomial::operator* (const Polynomial &rhs)
{

  Polynomial p;

  for (int i = 0; i < poly.size(); i++)
    {
      for (int j = 0; j < rhs.poly.size(); j++)
          p.poly.push_back(make_pair(poly[i].first * rhs.poly[j].first, poly[i].second + rhs.poly[j].second));
    }

  Squeeze(p.poly);
  Order(p.poly);

  return p;
}
