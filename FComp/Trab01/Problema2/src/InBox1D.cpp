#include <iostream>
#include "InBox1D.h"

using namespace std;

InBox1D::InBox1D(double x0, double v0, double WALLR, double alpha0)
{
  x = x0;
  v = v0;
  WR = WALLR;
  alpha = alpha0;
  hasreflected = false;
}

InBox1D::InBox1D(const InBox1D& rhs) // copy construtor 2
{
  x = rhs.x;
  v = rhs.v;
  WR = rhs.WR;
  alpha = rhs.alpha;
  hasreflected = false;
}

double InBox1D::GetX() const
{
  return x;
}

double InBox1D::GetV() const
{
  return v;
}

double InBox1D::GetWR() const
{
  return WR;
}

double InBox1D::GetALPHA() const
{
  return alpha;
}

void InBox1D::AdvanceX(double t)
{
  x = x + v*t;

  if (x <= 0 || x >= WR)
    hasreflected = true;

/*  if (x < -1 || x > WR + 1)
    {
      cout << "O corpo ultrapassou a parede!" << endl;
    } */
}

void InBox1D::AdvanceV(double t)
{
  //cout << alpha << endl;

   v = v * alpha; // testar

  if (hasreflected)
  {
    v = -v;
    hasreflected = false;
  }

}

void InBox1D::StepInTime(double dt)
{
  AdvanceX(dt);
  AdvanceV(dt);
}
