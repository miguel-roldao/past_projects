#include <string>
#include <iostream>
#include <map>

using namespace std;

map<int, string> periodicfill()
{
  map<int, string> table;
  table.insert({1, "H"});
  table.insert({32, "Ge"});  // space
  table.insert({33, "As"});
  table.insert({34, "Se"});
  table.insert({35, "Br"});
  table.insert({36, "Kr"});
  table.insert({37, "Rb"});
  table.insert({38, "Sr"});
  table.insert({39, "Y"});
  table.insert({40, "Zr"});
  table.insert({41, "Nb"});
  table.insert({42, "Mo"});
  table.insert({43, "Tc"});
  table.insert({44, "Ru"});
  table.insert({45, "Rh"});
  table.insert({46, "Pd"});
  table.insert({47, "Ag"});
  table.insert({48, "Cd"});
  table.insert({49, "In"});  // 1
  table.insert({50, "Sn"});
  table.insert({51, "Sb"});
  table.insert({52, "Te"});
  table.insert({53, "I"});
  table.insert({54, "Xe"});
  table.insert({55, "Cs"});
  table.insert({56, "Ba"});
  table.insert({57, "La"});
  table.insert({58, "Ce"});
  table.insert({59, "Pr"});
  table.insert({60, "Nd"});
  table.insert({61, "Pm"});
  table.insert({62, "Sm"});
  table.insert({63, "Eu"});
  table.insert({64, "Gd"});
  table.insert({65, "Tb"});
  table.insert({66, "Dy"});
  table.insert({67, "Ho"});
  table.insert({68, "Er"});
  table.insert({69, "Tm"});
  table.insert({70, "Yb"});
  table.insert({71, "Lu"});
  table.insert({72, "Hf"});
  table.insert({73, "Ta"});
  table.insert({74, "W"});
  table.insert({75, "Re"});
  table.insert({76, "Os"});
  table.insert({77, "Ir"});
  table.insert({78, "Pt"});
  table.insert({79, "Au"});
  table.insert({80, "Hg"});
  table.insert({81, "Tl"});
  table.insert({82, "Pb"});
  table.insert({83, "Bi"});
  table.insert({84, "Po"});
  table.insert({85, "At"});
  table.insert({86, "Rn"});
  table.insert({87, "Fr"});
  table.insert({88, "Ra"});
  table.insert({89, "Ac"});
  table.insert({90, "Th"});
  table.insert({91, "Pa"});
  table.insert({92, "U"});
  table.insert({93, "Np"});
  table.insert({94, "Pu"});
  table.insert({95, "Am"});
  table.insert({96, "Cm"});
  table.insert({97, "Bk"});
  table.insert({98, "Cf"});
  table.insert({99, "Es"});
  table.insert({100, "Fm"});
  table.insert({101, "Md"});  // e
  table.insert({102, "No"});
  table.insert({103, "Lr"});  // g
  table.insert({104, "Rf"});
  table.insert({105, "Db"});  // i
  table.insert({106, "Sg"});
  table.insert({107, "Bh"});
  table.insert({108, "Hs"});  // l
  table.insert({109, "Mt"});  // m
  table.insert({110, "Ds"});
  table.insert({111, "Rg"});
  table.insert({112, "Cn"});
  table.insert({113, "Nh"});
  table.insert({114, "Fl"});
  table.insert({115, "Mc"});
  table.insert({116, "Lv"});
  table.insert({117, "Ts"});  // u
  table.insert({118, "Og"});  // v
  table.insert({119, "Fr"});  // usam-se as maiusculas W,X,Y,Z
  table.insert({120, "Ra"});
  table.insert({121, "Ac"});
  table.insert({122, "Th"});

  return table;
}
