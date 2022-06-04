#ifndef H_Signal_H
#define H_Signal_H
#include <utility>
#include <vector>
#include <string>
using namespace std;

class Signal {

public:

// constructors
Signal();
Signal(double* t, double* sig, int n); //time and signal ptr arrays with size n
Signal(vector<double> t, vector<double> sig); //time and signal vector arrays
Signal(string filename); //read a file "filename" and assign signal and time from it.

// copy constructor
Signal(const Signal&);

// operators
Signal & operator=(const Signal &); // assign signal
Signal operator+(const Signal &); // add 2 signals of same "size"
Signal operator-(const Signal &); // subtract 2 signals of same "size"
Signal operator*(const Signal &); // multiply 2 signals of same "size"
Signal operator*(double); // multiply each signal value by a double
pair<double,double> operator[] (int);

vector<double> GetTime() const; // get the entire time array
vector<double> GetValue() const; // get the entire signal array
int Size() const; //returns the number of samples of the signal
void Plot(string) const; //plot of signal over time with input title given
double Sampling_freq() const; //return the sampling frequency i.e. 

private:
vector<double> time;
vector<double> signal;
};
#endif
