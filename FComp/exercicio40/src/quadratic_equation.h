using namespace std;

class quadratic {

  private:
    double a, b, c;

  public:
    quadratic() {a = 0; b = 0; c = 0; } // default constructor

    quadratic(double x, double y, double z)
      {
        a = x; b = y; c = z;
      }

    void print();

    double * solve();
    double * solve_case();

};
