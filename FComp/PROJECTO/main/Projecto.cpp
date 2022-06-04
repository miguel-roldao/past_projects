#include <iostream>
#include "PIC.h"

using namespace std;

int main () {

	double xmin=  0.0;
//	double xmax= 30.0;
	double xmax= 29.0;
	int Npart = 100000;
	int ngrid = 1000;
	double dt = 0.04;
	double vb = 5.0;
	vector<double> velvec(2);
	velvec[0]= -vb; //velocity of first beam (negative)
	velvec[1]=  vb; //velocity of second beam (positive)
	PIC twofluid=PIC(velvec,Npart,xmin,xmax,ngrid);
	twofluid.FdistV(velvec, false, false);
	twofluid.Plot_Phase_Space(true, false);
	twofluid.Density(false, false);
	twofluid.Poisson(false, false);
	for (int i = 0; twofluid.GetTime() < 60; i++) //< 60; i++)
	{
		double t = twofluid.GetTime();
		twofluid.TimeStep(dt);
		twofluid.Density((t > 15.0)?true:false, false);
		twofluid.Poisson((i%10 == 0)?true:false, false);
		twofluid.Plot_Phase_Space((t>15.0)?true:false, false);
		//cout << "t = " << twofluid.GetTime() << "\n";
	}

	return 0;
}
