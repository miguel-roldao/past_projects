#include <iostream>
#include "../src/FCtools.h"
#include "../src/FCmatrix.h"
#include "../src/FCmatrixFull.h"
#include "../src/FCmatrixBanded.h"
#include "../src/Vec.h"

using namespace std;

/*
            *     *   * * *   * * * *  * * * *           * * * *     * * *
            * * * *   *       *           *              *         *
            *  *  *   * **    * * *       *     * * *    * * *     *
            *     *   *       *           *              *         *
            *     *   * * *   *           *              *           * * *


            Alexandre Barbosa e Miguel Roldão (D02), 2019-2020                  */

int main()
{
  // build matrices
  double ** A;
  A = new double*[3];

  for (int i = 0; i < 3; i++)
    A[i] = new double[4];


  A[0][0] = 8;
  A[0][1] = -2;
  A[0][2] = 1;
  A[0][3] = 4;
  A[1][0] = 3;
  A[1][1] = 1;
  A[1][2] = -1.5;
  A[1][3] = 5;
  A[2][0] = 0.5;
  A[2][1] = 0;
  A[2][2] = 3;
  A[2][3] = 3;

  double ** B;
  B = new double*[4];


  for(int i = 0; i < 4; i++)
    B[i] = new double[3];

    B[0][0] = 2;
    B[0][1] = -1;
    B[0][2] = 3;
    B[1][0] = 1;
    B[1][1] = 8;
    B[1][2] = -0.5;
    B[2][0] = 2.5;
    B[2][1] = 6;
    B[2][2] = 2;
    B[3][0] = 3;
    B[3][1] = 4;
    B[3][2] = 5;

    double ** E;
    E = new double*[4];

    for (int i = 0; i < 4; i++)
      E[i] = new double[4];

    E[0][0] = 1;
    E[0][1] = 3;
    E[0][2] = 2;
    E[0][3] = 3;
    E[1][0] = 2;
    E[1][1] = -4;
    E[1][2] = 3;
    E[1][3] = 0;
    E[2][0] = 2;
    E[2][1] = 1;
    E[2][2] = 1;
    E[2][3] = 3;
    E[3][0] = 0;
    E[3][1] = 2;
    E[3][2] = 4;
    E[3][3] = 1;
  // build objects
  FCmatrixFull MA(A, 3, 4);
  FCmatrixFull MB(B, 4, 3);
  FCmatrixFull ME(E, 4, 4);

  for (int i = 0; i < 3; i++)
  {
    delete[] A[i];
    delete[] B[i];
    delete[] E[i];
  }

  delete[] B[3];
  delete[] E[3];

  delete[] A;
  delete[] B;
  delete[] E;

  cout<<"Matriz A:\n"<<endl;
  MA.Print();

  cout<<"\nMatriz B:\n"<<endl;
  MB.Print();


  double a = 2.5;

  FCmatrixFull MC(MA * a); //copy constructor and operator* (constant x Matrix)
  // cout<<"\n111\n"<<endl;
  FCmatrixFull MD(MA * MB);

  // print
  cout<<"\nA * 2.5:\n"<<endl;
  MC.Print();



  cout<<"\nA * B:\n"<<endl;
  MD.Print();

  cout<<"\nMatriz E:\n"<<endl;
  ME.Print();

  // other methods
  for(int i = 0; i < ME.Get_nRows(); i++)  // ME é quadrada
  {
    cout<<"\nO indice do máximo da coluna "<<i+1<<" é: "<<ME.GetColMax(i)<<endl;
    cout<<"O indice do máximo da linha "<<i+1<<" é: "<<ME.GetRowMax(i)<<endl;
  }

  cout<<"\nDeterminante da matriz E: "<< ME.Determinant()<<endl;

  MC.swapRows(1,2);
  cout<<"\nC(L2 <-> L3):\n"<<endl;
  MC.Print();

  cout<<"\n\nMatriz F:"<<endl;

  double** F = new double*[3];

  F[0] = new double[6];
  F[1] = new double[7];
  F[2] = new double[6];

  for(int i = 0; i < 6; i++)

  {
    F[0][i] = 1;
    F[1][i] = 2;
    F[2][i] = 3;
  }

  F[1][6] = 2;

  FCmatrixBanded MF(F, 7, 7);

  MF.Print();

  cout << "A entrada a1 da matriz F é:  " << MF['a'][0] << endl;

  cout << "A entrada c2 da matriz F é:  " << MF['c'][1] << endl;

  cout << "O determinante de F é:  " << MF.Determinant() << endl;

  for(int i = 0; i < 3; i++)
    delete[] F[i];

  delete[] F;

  FCtools cools;

  vector<Vec> Lili = cools.ReadFile2Vec("../matrixbanded.txt");

  cout<<"Matriz lida de ficheiro txt em formato full:"<<endl;

  FCmatrixFull L(Lili);
  L.Print();

  /** cout<<"\nTeste do método FULLtoTRIform"<<endl;
  FCmatrixBanded LiliBanded(cools.TRItoFULLform(Lili, 3, 3));
  LiliBanded.Print(); **/

  return 0;
}
