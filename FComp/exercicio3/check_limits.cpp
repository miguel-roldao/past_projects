#include <iostream>
#include <climits>
#include <cfloat>
using namespace std;

int main (int argc, char ** argv)
{
  cout << "Unsigned Int Max: " << UINT_MAX << endl;
  // O mínimo é, obviamente, zero.
  cout << "Signed Int Max:   " << INT_MAX << endl;
  cout << "Signed Int Min:   " << INT_MIN << endl;
  cout << "Long Int Max:     " << LONG_MAX << endl;
  cout << "Long Int Min:     " << LONG_MIN << endl;
  cout << "Float Max:        " << FLT_MAX << endl;
  cout << "Float Min:        " << FLT_MIN << endl;
  cout << "Double Max:       " << DBL_MAX << endl;
  cout << "Double Min:       " << DBL_MIN << endl;
  return 0;
}
