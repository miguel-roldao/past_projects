using namespace std;

double Bissection(double a, double b, double (*f)(double), double e);
double RegulaFalsi (double a, double b, double (*f)(double), int maxi);
double NewtonRaphson(double x, double (*f)(double), double (*df)(double), double e);
double Secant(double a, double b, double (*f)(double), double e);
