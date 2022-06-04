#include <iostream>
#include <iomanip>
#include "quadratic_equation.h"

using namespace std;


int main ()
{
    quadratic q = quadratic(1, (- 0.03 * 2.), 0.0008);

    double ax1 = q.solve()[0];
    double ax2 = q.solve()[1];
    double bx1 = q.solve_case()[0];
    double bx2 = q.solve_case()[1];

    cout.width(5);

    cout << "x1x2 = " << ax1 * ax2 << endl;
    cout << "   c = 0.0008" << endl << endl;

    cout << "As soluções da equação x^2 - 0.06 x + 0.0008 com a solução (A) são " << ax1 << " e " << ax2 << endl;
    cout << "As soluções da equação x^2 - 0.06 x + 0.0008 com a solução (B) são " << bx1 << " e " << bx2 << endl << endl;

    cout << "Método A (x1): " << ax1 << "^2 - 0.06 * " << ax1 << " + 0.0008 = " << ax1*ax1 - 0.06 * ax1 + 0.0008 << endl;
    cout << "Método A (x2): " << ax2 << "^2 - 0.06 * " << ax2 << " + 0.0008 = " << ax2*ax2 - 0.06 * ax2 + 0.0008 << endl;

    cout << "Método B (x1): " << bx1 << "^2 - 0.06 * " << bx1 << " + 0.0008 = " << bx1*bx1 - 0.06 * bx1 + 0.0008 << endl;
    cout << "Método B (x2): " << bx2 << "^2 - 0.06 * " << bx2 << " + 0.0008 = " << bx2*bx2 - 0.06 * bx2 + 0.0008 << endl;

    return 0;
}
