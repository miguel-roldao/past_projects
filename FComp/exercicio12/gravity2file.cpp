#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char ** argv)
{
    double h = 5, v0 = 20, g = 9.8, h0 = 5, t = 0;
    ofstream file;
    file.open ("trajectory.txt");

    // Legenda das colunas
    file << "       t           h(t)  \n";


    while (h >= 0)
      {
        h = h0 + v0*t - 0.5 * g * t * t;
        if (h > 0) // evitar valor negativo no final
          file << setw(10) << setprecision(4) << fixed << t << "    " << setw(10) << setprecision(4) << fixed << h << "\n" << flush;
        t += 0.0001;
      }

      // Imprime o valor do tempo de voo
      file << setw(10) << setprecision(4) << fixed << ((v0+sqrt(v0*v0+2*h0*g))/g) << "        " << 0.0000 << "\n" << flush;

    file.close();
    return 0;
}
