#include <iostream>
#include <string>
//#include "../../exercicio41/src/vec.h"
#include "FCmatrix.h"

using namespace std;

void FCmatrix::Print() const
{
  cout << "Isto resolve um problema estranho do linker, que alguém na Internet descreve como 'perhaps the most obscure error message that the linker spits out'" << endl;
}

string FCmatrix::GetClassName() const
{
  return classname;
}

vector<Vec> FCmatrix::GetM() const
{
  return M;
}
