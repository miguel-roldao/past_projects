#include <iostream>
#include <vector>
#include <complex>
#include <ctime>
#include <cstdlib>

using namespace std;
typedef complex<double> dcomp;  // double complexo

vector<complex<double>> rand2vec(int N)
{
  vector <dcomp> v1;

  v1.reserve(N);   // reserva N posições no vetor (não é necessário para o funcionamento do programa)

  for(int i = 0; i < N; i++)
  {
    v1.push_back(polar(1.0,(double)rand()/(double)RAND_MAX * 2. * M_PI));
  }
  return v1;
}

int main()
{
  int N;
  vector <dcomp> V;

  srand(time(NULL));

  cout << "Introduza um número inteiro: ";
  cin >> N;
  V = rand2vec(N);
  for(int i = 0; i < N; i++)
    cout << "\n z["<<i<<"] = " << *(V.begin() + i) << endl;

  dcomp media;

  for(int i = 0; i < N; i++)
    media += V.at(i);

  media = media /(double)N;

  cout<<"\nA média dos complexos é: "<<media<<endl; // Quando N aumenta media tende para (0.,0.)

  //media = (1.,0.);

//  cout<<media<<endl;

  return 0;
}
