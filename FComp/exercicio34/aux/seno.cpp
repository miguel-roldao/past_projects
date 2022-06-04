#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
  ofstream myfile;
  myfile.open("data.txt");

  double x = 0;

  while(x < 10)
  {
    myfile <<x<<"  "<<sin(x)*x<<"  3"<<endl;
    x += 0.01;
  }

  x = 0;

  while(x < 10)
  {
    myfile <<x<<"  "<<5-2*x+(x-4)*(x-4)*(x-4)<<"  4"<<endl;
    x += 0.01;
  }

  myfile.close();
  return 0;
}
