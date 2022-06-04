#include <iostream>
#include <iomanip>
using namespace std;

int Trace(int** mx, int n);  // calcula traço

int* Mrow (int i, int** mx, int m, int n) //devolve linha i da matriz;
{
  return mx[i];
}

int* Mx_vect (int** mx, int n, int m, int* v); // Produto de matriz por vetor

int** Mx_product (int** nx, int p, int q, int** mx, int n, int m); // Produto de matrizes

int main()
{
  int i, j;
  int n = 3;  // nº de linhas de M
  int m = 3;  // nº de colunas de M
  int l;      // lª linha pedida
  int** Mx;   // matriz M
  int* v;     // vetor V
  int* line;  // linha pedida
  int** Nx;   // matriz n
  int p = 2;  // nº de linhas de N
  int q = 3;  // nº de colunas de N
  int** NxM;  // resultado de N x M

  v = new int[m];
  Mx = new int*[n];
  Nx = new int*[p];

  for(i = 0; i < n; i++)
    Mx[i] = new int[m];

  for(j = 0; j < p; j++)
    Nx[j] = new int[q];

  Mx[0][0] = 1;
  Mx[0][1] = 2;
  Mx[0][2] = 7;
  Mx[1][0] = -2;
  Mx[1][1] = 6;
  Mx[1][2] = -3;
  Mx[2][0] = 3;
  Mx[2][1] = 9;
  Mx[2][2] = 3;

  v[0] = 2;
  v[1] = 3;
  v[2] = -2;

  Nx[0][0] = 2;
  Nx[0][1] = 3;
  Nx[0][2] = 1;
  Nx[1][0] = 3;
  Nx[1][1] = 0;
  Nx[1][2] = -2;

  cout<<"A matriz M é: \n"<<endl;
/* Impressão da matriz M */
  for(i = 0; i < n; i++)
  {
     cout<<"|";

    for(j =0;j < m; j++)
      cout<<" "<<setw(2)<<Mx[i][j]<<" ";

     cout<<"|"<<endl;
  }

  cout<<"Selecione uma linha da matriz m: ";
  cin>>l;
  l--; // linha 1 --> line[0]
  line = Mrow(l, Mx, n, m);
  /*Impressao da linha*/
  cout<<"\n|";

  for(i = 0; i < m; i++)
    cout<<" "<<setw(2)<<line[i]<<" ";

  cout<<"|\n"<<endl;

  cout<<"\n O traço da matriz anterior é: "<<Trace(Mx, n)<<endl;

  line = Mx_vect (Mx, n, m, v);

  cout<<"\n M . v = "<<endl;
  for(i = 0; i < m; i++)
    cout<<"       | "<<setw(3)<<line[i]<<" |\n";

  cout<<endl<<" NxM = \n"<<endl;

  NxM = Mx_product(Nx, p, q, Mx, n, m);

  for(i = 0; i < p; i++)
  {
    cout<<"|";

    for(j =0; j < m; j++)
      cout<<" "<<setw(3)<<NxM[i][j]<<" ";

    cout<<"|"<<endl;
  }



  delete[] line;
  delete[] v;

  for(i = 0; i < n; i++)
    delete[] Mx[i];

  for(i = 0; i < p; i++)
    delete[] Nx[i];

  for(i = 0; i < p; i++)
    delete[] NxM[i];

  delete[] Mx;
  delete[] Nx;
  delete[] NxM;
  return 0;
}

int Trace(int** mx, int n)  // calcula traço
{
  int t = 0;

  for (int i = 0; i < n; i++)
    t += mx[i][i];

  return t;
}

int* Mx_vect (int** mx, int n, int m, int* v) // Produto de matriz por vetor
{
  int* a;
  a = new int[n];

  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < m; j++)
    {
      a[i] += mx[i][j] * v[j];
    }
  }
  return a;
}

int** Mx_product (int** nx, int p, int q, int** mx, int n, int m) // linhas(p,n),colunas(q,m)
{
  if (q != n)
  {
    cout<<"As matrizes não têm as dimensões apropriadas."<<endl;
    return NULL;
  }

  int** NxM;       // matriz resultado N x M
  NxM = new int*[p];
  for(int i = 0; i < p; i++)
    NxM[i] = new int[q];

  for(int i = 0; i < p; i++)
  {
    for(int j = 0; j < m; j++)
    {
      for(int k = 0; k < q; k++)
        NxM[i][j] += nx[i][k] * mx[k][j];
    }
  }
  return NxM;
}
