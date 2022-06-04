#ifndef H_EULER_H
#define H_EULER_H

#include <vector>

using namespace std;

vector<double> Euler (double x0, double tmin, double tmax, double (*f) (double,double), double dt);

#endif
