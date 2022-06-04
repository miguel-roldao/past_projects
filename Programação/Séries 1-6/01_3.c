#include <stdio.h>

void fibonacci(int n, int *v)
  {
    int i;
    int f0 = 0;
    int f1 = 1;
    v[0] = f0;
    v[1] = f1;
	 
    for (i = 2; i < n; i++)
      {
	v[i] = v[i-2] + v[i-1]; // soma os termos n-2 e n-1 para obter o termo n 
      }
  }

int main()
  {
    
  int i, n, t, v[46];

  FILE *C;
  C = fopen("fibonacci.txt", "wt"); // abre o canal de escrita de texto
  
  printf("Quantos termos da sucessão de Fibonacci quer saber? ");
  t = scanf("%d", &n);

  if (t != 1) // teste de leitura
    {
	printf("Por favor, introduza um número natural menor ou igual a 45!\n");
	return 1; // erro!
    }

   if (n > 45 || n < 0)
    {
	printf("Por favor, introduza um número natural menor ou igual a 45!\n");
	return 1; // erro!
    }

   fibonacci(n, v); 
  
   for (i = 0; i < n; i++)
     {
	
	printf("F%2d : %8d   ", i, v[i]);
	fprintf(C, "F%2d :  %8d   ", i, v[i]);
	
	if (i % 6 == 5) // depois de imprimir 6 termos (a partir de 0), muda de linha
	  {
	    printf("\n");
	    fprintf(C, "\n");
	  }
     }
  
    fclose(C); // fecha o canal de escrita
    return 0;
    
   }
