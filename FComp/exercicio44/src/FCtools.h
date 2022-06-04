#ifndef H_FCTOOLS_H
#define H_FCTOOLS_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Vec.h"

using namespace std;

/* A classe FCtools é onde são definidos vários métodos úteis que permitem ler ficheiros
   A string 'src' é o nome do ficheiro a ser lido.*/


class FCtools {
  public:

  vector<string> ReadFile2String(string src);
  vector<Vec> ReadFile2Vec(string src);
  Vec* ReadFile(string src);
  double** TRItoFULLform(double** tri, int fm, int fn); // converte uma matriz triadiagonal numa FCMatrixfull legível

  ~FCtools(){}; // destrutor

};

#endif
