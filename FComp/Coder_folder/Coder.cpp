#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "periodicfill.h"

using namespace std;

//First contact with c++
//Little script to encode the string given as argv with Periodic table elements

int main(int argc, char **argv)
{
  map<int, string> table;

  table = periodicfill();
  //cout<<argc<<endl;
  if(argc<2)
  {
    cout<<"Try to run it with a string as argument"<<endl;
    return 1;
  }
  
  for(int i = 1; i < argc; i++)
  {
    for(int j = 0; argv[i][j] != 0; j++)
      cout<<table[int(argv[i][j])]<<"-";

    if(i < argc-1)
      cout<<table[32]<<"-";
  }
  cout<<"-"<<endl;
  return 0;
}
