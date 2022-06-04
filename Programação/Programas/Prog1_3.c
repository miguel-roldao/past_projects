#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <math.h>

void ordena(double *v, int n)
  {
    int i, t=1;
    double p;
    
    n--;

    while (t != 0)
      {
	t=0;	

	for(i=0; i<n; i++)
	  {
	    if(v[i] > v[i+1])
	      {
		p = v[i];
		v[i] = v[i+1];
		v[i+1] = p;
		t++;
	      }
	  }
      }
  }

int main(int argc, char** argv)
  {
    int n, i, ans, w=1;
    double min, max, delta, *v;
    FILE *f;
    
    if(argc != 4 || sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2],"%lf", &min) != 1 || sscanf(argv[3], "%lf", &max) != 1 || n < 0 || max <= min)
      {
	printf("\n**Introduza como argumentos o número de valores quer gerar e os limites do intervalo. (./Prog1_3 <N> <MIN> <MAX>)**\n\n");
	return 1;
      }

    srand(time(NULL));

    v = (double*) malloc(n*sizeof(double));

    while(w==1)
      {
	w = 0;

	v = (double*) realloc(v, n*sizeof(double));

	delta = max - min;
    
	for(i=0; i<n; i++)
	  v[i] = (double)rand()/(double)RAND_MAX * delta + min;
 
	ordena(v, n);

	f = fopen("dados.txt","wt");
    
	if(f == NULL)
	  {
	    printf("\n **Erro: O ficheiro não foi aberto corretamente!**\n\n");
	    return 1;
	  }
    
	for(i=0; i<n; i++)
	  {
	    printf("v[%d] : %5lf      ", i, v[i]);
	    fprintf(f, "v[%d] : %5lf      ", i, v[i]);

	    if(i%5 == 4)
	      {
		printf("\n");
		fprintf(f, "\n");
	      }
	
	  }
      
	printf("\n\nDeseja gerar novos valores? (1-Sim 0-Nao) ");
    
	if(scanf("%d", &ans) == 1 && ans == 1)
	  {
	    printf("\n <N> <MIN> <MAX>  ");

	    if(scanf("%d %lf %lf", &n, &min, &max) == 3 && ans >= 0 && min < max)
	      w = 1;

	      else
		break;
	  }

	else
	  break;

	fprintf(f,"\n\n");
      }
    
    fclose(f);
    
    free(v);

    return 0;
  }
