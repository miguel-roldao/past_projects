#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/*
     *     *   * * *   * * * *  * * * *
     * * * *   *       *           *
     *  *  *   * *     * * *       *
     *     *   *       *           *
     *     *   * * *   *           *

Miguel Roldão nº 93405
17/12/2018

teste individual

 */


void troca (double *v, double *w)
  {
    double p;

    p = *v;
    *v = *w;
    *w = p;
  }
   
void ordena (double *v, int n)
  {
    int i, t = 1;

    n--;    // Para o bubble sort não chegar ao último termo.
    
    while(t == 1)
      {
	t = 0;

	for(i = 0; i < n; i++)
	  {
	    if(v[i] > v[i+1])
	      {
		troca(&v[i], &v[i+1]);
		t = 1;
	      }
	  }
      }
  }

int main(int argc, char **argv)
  {
    int n, i, ans;
    double min, max, delta, *v;
    FILE *f;    

    if(sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%lf", &min) != 1 || sscanf(argv[3], "%lf", &max) != 1 || n < 0 || min >= max)
      {
	printf("\n ** ERRO: Introduza como argumentos os valores de N(>0), Min e Max! (Exemplo: ./Prog_name 15 -10 10 ) **\n\n");
	return 1;
      }

    delta = max - min;
    
    printf("\n N: %d   Min: %.3lf   Max: %.3lf    delta: %.3lf \n\n", n, min, max, delta);

    f = fopen("dados.bin","wt");

    if(f == NULL)
      {
	printf("\n ** ERRO: O ficheiro não foi aberto corretamente! **\n\n");
	return 1;
      }

    if(fwrite(&n, sizeof(int), 1, f) != 1 || fwrite(&min, sizeof(double), 1, f) != 1 || fwrite(&max, sizeof(double), 1, f) != 1)
      {
	printf("\n** ERRO: A escrita no ficheiro não foi efetuada corretamente! **");
	fclose (f);
	return 1;
      }
        
    v = (double*) malloc(n*sizeof(double));

    srand(time(NULL));

    while(1)
      {
	for(i = 0; i < n; i++)
	  {
	    v[i] = (((double) rand() / (double) RAND_MAX) * delta) + min;
	    printf("v[%2d] : %lf       ", i, v[i]);
	    
	    if(i % 5 == 4)
	      printf("\n");
	  }

	ordena(v, n);

	printf("\n\nDepois de ordenar:\n\n");
    
	for(i = 0; i < n; i++)
	  {
	    printf("v[%2d] : %lf       ", i, v[i]);
	    
	    if(fwrite(&v[i], sizeof(double), 1, f) != 1)
	      {
		printf("\n** ERRO: A escrita no ficheiro não foi efetuada corretamente! **");
		fclose (f);
		free(v);
		return 1;
	      }
	      
	    if(i % 5 == 4)
	      printf("\n");
	  }
    
	printf("\n\n Pretende efetuar nova simulação?(1-Sim 0-Nao) ");

	if(scanf("%d", &ans) != 1 || ans != 1)
	  break;

	printf("\nIntroduza novos argumentos: <N> <MIN> <MAX>   ");

	if(scanf("%d %lf %lf", &n, &min, &max) != 3 || n < 0 || min >= max)
	  {
	    printf("\n *Introduziu valores invalidos! (Exemplo: 15 -10 10 ) *\n");
	    break;
	  }

	v = (double*) realloc(v, n*sizeof(double));

	delta = max - min;

	printf("\n N: %d   Min: %.3lf   Max: %.3lf    delta: %.3lf \n\n", n, min, max, delta);

      }

    fclose (f);
    
    free(v);

    printf("\n ***PROGRAMA TERMINADO! ***\n");

    return 0;
  }
