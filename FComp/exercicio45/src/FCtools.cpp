#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Vec.h"
#include "FCtools.h"

using namespace std;

/*
     ______   ______  _________  ______   ______   __       ______
    /_____/\ /_____/\/________/\/_____/\ /_____/\ /_/\     /_____/\
    \::::_\/_\:::__\/\__.::.__\/\:::_ \ \\:::_ \ \\:\ \    \::::_\/_
    \:\/___/\\:\ \  __ \::\ \   \:\ \ \ \\:\ \ \ \\:\ \    \:\/___/\
    \:::._\/ \:\ \/_/\ \::\ \   \:\ \ \ \\:\ \ \ \\:\ \____\_::._\:\
    \:\ \    \:\_\ \ \ \::\ \   \:\_\ \ \\:\_\ \ \\:\/___/\ /____\:\
    \_\/     \_____\/  \__\/    \_____\/ \_____\/ \_____\/ \_____\/

                                                                        */


vector<string> FCtools::ReadFile2String(string src) // lê um ficheiro e retorna um vetor de strings
{
  vector<string> vs;
  ifstream f1;

  f1.open(src);

  if (f1.is_open())
  {
    string s;

    while(getline(f1, s))
      vs.push_back(s);
  }

  // else mensagem de erro?

  return vs;
}

vector<Vec> FCtools::ReadFile2Vec(string src) // lê um ficheiro e retorna um vetor de objetos da classe Vec
{
  vector<string> vs = ReadFile2String(src); // usa o método anterior
  vector<Vec> vvec;

  for (int i = 0; i < vs.size(); i++)
  {
    int n = 0;
    vector<double> vetor;
    string s;
    stringstream ss(vs.at(i));

    while(ss >> s)
    {
      vetor.push_back(stod(s));
      n++;
    }

    double *ptr;
    ptr = new double[n];

    for (int i = 0; i < n; i++)
      ptr[i] = vetor.at(i);

    Vec v(n, ptr);

    vvec.push_back(v);
    delete[] ptr;


  }

  return vvec;
}

Vec* FCtools::ReadFile(string src) // lê um ficheiro e retorna um ponteiro para um array de objetos da classe Vec
{
  vector<Vec> V = ReadFile2Vec(src); // usa os métodos anteriores
  Vec* ptr;
  ptr = new Vec[V.size()];

  for (int i = 0; i < V.size(); i++)
    ptr[i].SetEntries(V.at(i).Size(), V.at(i).GetEntries());

  return ptr;
}

double** FCtools::TRItoFULLform(double** tri, int fm, int fn) // converte uma matriz triadiagonal numa matriz full legível
{
  double** full = new double*[fm];

  if (fm == fn && (fm > 1)) // a matriz tem de ser quadrada e não ser apenas um número
  {
    for (int i = 0; i < fm; i++)
    {
      full[i] = new double[fn];

      for (int j = 0; j < fn ; j++)
      {
        if (i == j)
          full[i][i] = tri[1][i];

        else if ((i - j) == 1)
          full[i][j] = tri[2][j];

        else if ((j - i) == 1)
          full[i][j] = tri[0][j-1];

        else
          full[i][j] = 0;
      }
    }
  }

else
  {
    cout << "A matriz triadiagonal (FCmatrixBanded) não pode ser convertida em forma de FCmatrixfull!" << endl;
    delete[] full;
    exit(EXIT_FAILURE);
  }

  return full;
}
