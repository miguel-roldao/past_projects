#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct
 {
   double re;
   double im;
   double mod; } complexo;

double modulo(complexo *v)
  {
    return (sqrt(v->re * v->re + v->im * v-> im));
  }

void ordena(complexo **v, int n)
  {
    int i, t=1;
    complexo *troca;

    n--;
    
    while(t!=0)
      {
	t=0;
	
	for(i=0; i < n; i++)
	  {
	    if(v[i]->mod > v[i+1]->mod)
	      {
		troca = v[i];
		v[i] = v[i+1];
		v[i+1] = troca;
		t++;
	      }
	  }
      }
  }

void troca(complexo **v, int i, int j)
  {
    complexo *p;
    
    p = v[i];
    v[i] = v[j];
    v[j] = p;
  }

int main(int argc, char **argv)
  {
    int n, j, k, i=0;
    complexo **v;
    
    
    if (argc != 2 || sscanf(argv[1], "%d", &n) != 1 || n < 1)
      {
	printf("\n **Erro: Introduza o número de complexos que deseja gerar!** \n\n");
	return 1;
      }

    printf("\n n: %d\n\n", n);

    srand(time(NULL));

    v = (complexo**) malloc(n*sizeof(complexo*));

    for (i=0; i < n; i++)
      {
	v[i] = (complexo*) malloc(sizeof(complexo));
	v[i]->re = (((double) rand())/(double) RAND_MAX * 27 - 12);
	v[i]->im = (((double) rand())/(double) RAND_MAX * 27 - 12);
	v[i]->mod = modulo(v[i]);
	printf("v[%d] : %+.3lf %+.3lf i    modulo: %.3lf\n", i, v[i]->re, v[i]->im, v[i]->mod);
      }

    ordena(v,n);
    
    printf("\n Depois de ordenar:\n\n");

    j = 1;

    while (j==1)
      {
	for (i=0; i < n; i++)
	  printf("v[%d] : %+.3lf %+.3lf i    modulo: %.3lf\n", i, v[i]->re, v[i]->im, v[i]->mod);

	printf("\n");

	printf("Deseja efetuar alguma troca?(1-Sim 0-Não) ");

	if(scanf("%d", &j) != 1 || j != 1)
	  break;

	printf("Que complexos deseja trocar? ");

	if(scanf("%d", &i) !=1 || i >= n )
	   printf("\n**Introduza um número associado a um complexo gerado!**\n\n");
	    
	else
	  {
	    printf("O %d com o: ", i);

	    if(scanf("%d", &k) !=1 || k >= n)
	      printf("\n**Introduza um número associado a um complexo gerado!**\n\n");

	    else
	      troca(v, i, k);
	  }	    
      }
    
    for(i=0; i < n; i++)
      {
	free(v[i]);
      }

    free (v);

    printf("   *Programa terminado*\n");
    
    return 0;
  }
