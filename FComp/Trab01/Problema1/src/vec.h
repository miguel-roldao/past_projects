#ifndef H_VEC_H
#define H_VEC_H

using namespace std;

/* Os objetos da classe Vec são vetores, e os seus métodos permitem realizar operações sobre vetores em Rn.
   A partir destes, define-se a classe FCmatrix, cujos métodos usam vários dos operadores aqui definidos. */

class Vec {

  private:
    int N; //number of elements
    double *entries; // pointer to array of doubles

  public:
    Vec(int n = 1, double d = 0.); // default constructor

    Vec(int n, double *ptr); // constructor

    ~Vec(); // destructor

    Vec (const Vec &v); // copy constructor

    void SetEntries (int n, double* ptr); // muda as entradas de uma matriz

    void Print(); // imprime o vetor

    void Swap(int m, int n); // troca duas componentes do vetor

    int Size() const { return N; } // retorna o tamanho de um vetor constante (número de elementos)
    int Size() { return N; } // retorna o tamanho do vetor (número de elementos)

    double* GetEntries() const { return entries; } // retorna o conteúdo do vetor (ponteiro para doubles)
    double* GetEntries() { return entries; } // retorna o conteúdo do vetor (ponteiro para doubles)

    double dot(const Vec u) const; // produto interno

    Vec cross(const Vec &rhs); // produto externo

    Vec & operator= (const Vec &rhs); // assignement operator

    Vec operator+ (const Vec & rhs) const; // soma de vetores
    Vec operator- (const Vec & rhs) const; // subtração de vetores

    Vec & operator+= (const Vec & rhs);
    Vec & operator-= (const Vec & rhs);
    Vec & operator*= (const Vec & rhs);

    Vec & operator- (); // negativo de um vetor
    Vec & operator+ (); // positivo de um vetor

    Vec operator* (const double & scalar) const; // produto por um escalar
    Vec operator* (const Vec & rhs) const; // produto de vetores componente a componente

    double operator[] (int i) const; // aceder à entrada i (para vetores constantes)
    double& operator[] (int i); // aceder à entrada i

  };

#endif
