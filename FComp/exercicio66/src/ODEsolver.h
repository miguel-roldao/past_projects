#ifndef H_ODESOLVER_H
#define H_ODESOLVER_H

#include <vector>
#include "TFormula.h"
#include "ODEpoint.h"

using namespace std;

class ODEsolver{
  public:
    ODEsolver(vector<TFormula> FF);
    ~ODEsolver(){}
    vector<ODEpoint> Eulersolver(const ODEpoint& P0, double xmin, double xmax, double h_step = 0.1);
    vector<ODEpoint> RK2solver(const ODEpoint& P0, double xmin, double xmax, double h_step);
    vector<ODEpoint> RK4solver(const ODEpoint& P0, double xmin, double xmax, double h_step);
    vector<ODEpoint> RK4_AdapStep(const ODEpoint& P0, double xmin, double xmax, double h_step);
    vector<ODEpoint> Heun(const ODEpoint& P0, double xmin, double xmax, double h_step);
    //...
    void SetODEfunc(vector<TFormula> FF);

  private:
    ODEpoint Heun_iterator (const ODEpoint&, double step);
    ODEpoint EULER_iterator (const ODEpoint&, double step);
    ODEpoint RK2_iterator (const ODEpoint&, double step);
    ODEpoint RK4_AS_iterator(const ODEpoint&, double step, vector<vector<double>> &K);
    ODEpoint RK4_iterator(const ODEpoint&, double step);

    vector<TFormula> F;
};

#endif
