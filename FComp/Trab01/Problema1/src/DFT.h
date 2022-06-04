#ifndef H_DFT_H
#define H_DFT_H

#include <iostream>
#include <vector>
#include "Signal.h"
using namespace std;

class DFT {

public:
	DFT();
	DFT(Signal &);
	vector<double> MultCOS(Signal &, double &);
	vector<double> MultSIN(Signal &, double &);
	double Sum(vector<double> V);
	double GetPowSpec(double);
	double GetAmpSpec(double);
private:
	Signal sig1d;
	int Np_signal; // number of time samples in the signal...
};
#endif
