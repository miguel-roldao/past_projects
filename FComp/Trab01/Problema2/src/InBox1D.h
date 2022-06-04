#ifndef H_InBox1D_H
#define H_InBox1D_H

#include <iostream>
#include <vector>
using namespace std;

class InBox1D {

public:
	InBox1D(double x0=0.5, double v0=1.0, double WALLR=1.0, double alpha0=0.99);
	InBox1D(const InBox1D &);
	void StepInTime(double dt); //time step both x and v by dt seconds
	double GetX() const; //Get x value
	double GetV() const; //Get v value
	double GetWR() const; //Get the Wall x-positon at the right
	double GetALPHA() const; //Get the velocity damping value
private:
	double x; //position
	double v; //velocity with sign
	double WR; //Wall position at the right
	double alpha;  //velocity damping value
	bool hasreflected; //if particle bounced on any of the walls
	void AdvanceX(double); //time step x
	void AdvanceV(double); //time step v
};
#endif
