#include <iostream>
#include "atom.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
  ATOM H;
  H.A = 1;
  H.Z = 1;
  H.name = "Hydrogen";
  ATOM He;
  He.A = 2;
  He.Z = 4;
  He.name = "Helium";
  ATOM Li;
  Li.A = 7;
  Li.Z = 3;
  Li.name = "Lithium";
  ATOM Be;
  Be.A = 9;
  Be.Z = 4;
  Be.name = "Beryllium";

//  cout<<"The smaller atom is "<<H.name<<" with only "<<H.Z<<" proton!"<<endl;
/*  vector<ATOM> vperiodic(4);

  vperiodic[0] = H;
  vperiodic[1] = He;
  vperiodic[2] = Li;
  vperiodic[3] = Be;
*/
  map<string, ATOM> mperiodic;
  mperiodic["H"] = H;
  mperiodic["He"] = He;
  mperiodic["Li"] = Li;
  mperiodic["Be"] = Be;

  map<string, ATOM> :: iterator it;

  it = mperiodic.find("H");
  cout<<it->second.name<<" has "<<it->second.A<<" nucleons, "<<it->second.Z<<" protons."<<endl;

  it = mperiodic.find("He");
  cout<<it->second.name<<" has "<<it->second.A<<" nucleons, "<<it->second.Z<<" protons."<<endl;

  it = mperiodic.find("Li");
  cout<<it->second.name<<" has "<<it->second.A<<" nucleons, "<<it->second.Z<<" protons."<<endl;

  it = mperiodic.find("Be");
  cout<<it->second.name<<" has "<<it->second.A<<" nucleons, "<<it->second.Z<<" protons."<<endl;

  return 0;
}
