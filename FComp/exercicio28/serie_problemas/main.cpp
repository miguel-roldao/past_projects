#include <iostream>
#include "../../exercicio27/src/pessoa.h"
using namespace std;

void Dummy(alunoIST** a, const int b);

int main()
{
  /*alunoIST a;
  a.SetName("Miguel");
  a.SetBornDate(20000721);
  a.Print();*/

  int N = 5;
  // alunoIST Arr[5];
  alunoIST** ptr = DoArray_IST(N);
  //  Arr[0].SetName("Afonso Guerreiro");
  (*ptr[0]).SetName("Afonso");
  (*ptr[0]).SetBornDate(20010728);
  (*ptr[0]).SetNumber(96501);
  (*ptr[0]).SetCourse("MEMEC");
  (*ptr[1]).SetName("Francisca Paiva");
  (*ptr[1]).SetBornDate(20010212);
  (*ptr[1]).SetNumber(96525);
  (*ptr[1]).SetCourse("MEBiom");
  (*ptr[2]).SetName("André Lopes");
  (*ptr[2]).SetBornDate(20010917);
  (*ptr[2]).SetNumber(96510);
  (*ptr[2]).SetCourse("LEGM");
  (*ptr[3]).SetName("Juna Santos");
  (*ptr[3]).SetBornDate(20010815);
  (*ptr[3]).SetNumber(96549);
  (*ptr[3]).SetCourse("LMAC");
  (*ptr[4]).SetName("Rodrigo Simões");
  (*ptr[4]).SetBornDate(20010527);
  (*ptr[4]).SetNumber(96564);
  (*ptr[4]).SetCourse("MEEC");

  Dummy(ptr, N);

  ClearArray_IST(ptr, N);

  return 0;
}
