#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef vector<vector<int> > MATRIZ;

int Trace(MATRIZ mx, int n) //calcula traço
{
  int t = 0;

  for(int i = 0; i < n; i++)
    t += mx[i][i];

  return t;
}

vector<int> Mrow (int i, MATRIZ mx)
{
  return mx[i];
}

vector<int> Mx_vect (MATRIZ mx, int n, int m, vector<int> x)
{
  int k;
  vector<int> v;
  for(int i = 0; i < n; i++)
  {
    k = 0;
    for(int j = 0; j < m; j++)
      k += mx[i][j] * x[j];

    v.push_back(k);
  }
  return v;
}

MATRIZ Mx_product (MATRIZ nx, int p, int q, MATRIZ mx, int n, int m)
{
  int t;
  vector<int> v;
  MATRIZ NxM;

  if (q != n)
  {
    cout<<"As matrizes não têm as dimensões apropriadas."<<endl;
    return NxM;
  }
  // matriz resultado N x M

  for(int i = 0; i < p; i++)
  {
    for(int j = 0; j < m; j++)
    {
      t = 0;
      for(int k = 0; k < q; k++)
        t += nx[i][k] * mx[k][j];
      v.push_back(t);
    }
    NxM.push_back(v);
    v.clear();
  }

  return NxM;
}

int main()
{

  int n = 3;  // nº de linhas de Mx
  int m = 3;  // nº de colunas de Mx
  int p = 2;  // nº de linhas de Nx
  int q = 3;  // nº de colunas de Nx
  int s;
  MATRIZ Mx;
  MATRIZ Nx;
  MATRIZ NxM;
  int l;
  vector<int> v;
  vector<int> line;

  cout<<"matriz M: "<<endl;

  for (int i = 0; i<n; i++)
  {
    for(int j = 0; j < m; j++)
    {
      cout<<"["<<i<<"]["<<j<<"] ";
      cin>>s;
      line.push_back(s);
    }
    Mx.push_back(line);
    line.clear();
  }

  cout<<"\nA matriz M é: \n"<<endl;
/* Impressão da matriz M */
  for(int i = 0; i < n; i++)
  {
    cout<<"|";

    for(int j = 0; j < m; j++)
      cout<<" "<<setw(2)<<Mx[i][j]<<" ";

    cout<<"|"<<endl;
  }

  cout<<"\nSelecione uma linha da matriz M: ";
  cin>>l;
  l--; // linha 1 --> line[0]
  if(l < 0 && l >= n)
  {
    cout<<"Valor inválido! *reiniciar programa*"<<endl;
    return 1;
  }
  line.clear();
  line = Mrow(l, Mx);

/*Impressão da linha*/
  cout<<"\n|";

  for(int i = 0; i < m; i++)
    cout<<" "<<setw(2)<<line[i]<<" ";

  cout<<"|\n"<<endl;

  cout<<"\n O traço da matriz M é: "<<Trace(Mx, n)<<endl;

  line.clear();

  cout<<"vetor v: "<<endl;

    for(int i = 0; i < m; i++)
    {
      cout<<"["<<i<<"] ";
      cin>>s;
      v.push_back(s);
    }

  line = Mx_vect (Mx, n, m, v);

  cout<<"\n M . v = "<<endl;

  for(int i = 0; i < m; i++)
    cout<<"       | "<<setw(3)<<line[i]<<" |\n";

  cout<<"matriz N: "<<endl;

  for (int i = 0; i<p; i++)
  {
    for(int j = 0; j < q; j++)
    {
      cout<<"["<<i<<"]["<<j<<"] ";
      cin>>s;
      line.push_back(s);
    }
    Nx.push_back(line);
    line.clear();
  }

  cout<<"\nA matriz N é: \n"<<endl;
/* Impressão da matriz N */
  for(int i = 0; i < p; i++)
  {
    cout<<"|";

    for(int j = 0; j < q; j++)
      cout<<" "<<setw(3)<<Nx[i][j]<<" ";

    cout<<"|"<<endl;
  }

  cout<<endl<<" NxM = \n"<<endl;

  NxM = Mx_product(Nx, p, q, Mx, n, m);

/*  Impressão da matriz NxM  */
  for(int i = 0; i < p; i++)
  {
    cout<<"|";

    for(int j =0; j < m; j++)
      cout<<" "<<setw(3)<<NxM[i][j]<<" ";

    cout<<"|"<<endl;
  }

  return 0;
}
