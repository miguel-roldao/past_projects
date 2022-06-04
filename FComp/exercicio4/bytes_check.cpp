#include <iostream>
using namespace std;

// char, short int, int, long int, unsigned int, float, double, long double

int main()
{
    cout << "O tamanho de um char é:         " << sizeof(char) << " byte" << endl;
    cout << "O tamanho de um short int é:    " << sizeof(short) << " bytes" << endl;
    cout << "O tamanho de um long int é:     " << sizeof(long) << " bytes" << endl;
    cout << "O tamanho de um unsigned int é: " << sizeof(unsigned int) << " bytes" << endl;
    cout << "O tamanho de um float é:        " << sizeof(float) << " bytes" << endl;
    cout << "O tamanho de um double é:       " << sizeof(double) << " bytes" << endl;
    cout << "O tamanho de um long double é:  " << sizeof(long double) << " bytes" << endl;
    return 0;
}
