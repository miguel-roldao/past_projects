#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int n, double *v)
  {
    while (1)
      {
	int i;
	int t = 0;
	for (i = 0; i < n - 1; i++) // n-1 é o número de trocas em cada ciclo!
	  {
	    double placeholder;
	    if (v[i] < v[i+1])
	      {
		placeholder = v[i];
		v[i] = v[i+1];
		v[i+1] = placeholder;
		t = 1;
	      }
	  }
	if (t == 0) break;
      }
  }

int main(int argc, int **argv)
{
  srand(time(NULL));
  int i, n;
  double max, v[10000];

  FILE *C;
  C = fopen("random.txt", "wt");
  if(argc != 3)  //N e Max não forem bem introduzidos na linha de comandos
    {
      printf("Quantos números quer gerar? ");
      scanf("%d", &n);
      printf("Qual o valor máximo? ");
      scanf("%lf", &max);
    }
  else
    {
      n = *argv[1];
      max = (double) *argv[2];
      printf("%d e %lf", n, max);
    }
  
  /*  srand(time(NULL));
  int i, n;
  double max, v[10000];

  FILE *C;
  C = fopen("random.txt", "wt");
  
  printf("Quantos números quer gerar? ");
  scanf("%d", &n);
  printf("Qual o valor máximo? ");
  scanf("%lf", &max);*/

  for (i = 0; i < n; i++)
    {
      double a = ((double) rand()/(double) RAND_MAX)* max;
      v[i]= a;
      //printf("v[%d] = %lf \n", i, v[i]);
    }

  bubble_sort(n, v);
  
  for (i = 0; i < n; ++i)
    {
      printf("v[%d] = %lf \n", i, v[i]);
      fprintf(C, "v[%d] = %lf \n", i, v[i]);
    }
  fclose(C);
  return 0;
}
