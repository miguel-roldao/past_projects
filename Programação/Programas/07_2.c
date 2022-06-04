#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct 
  { double re;
    double im;
    double mod; } complexo; 

double modulo (complexo *z1)
  {
    return sqrt(z1->re*z1->re + z1->im*z1->im);
  }

void ordena (complexo **v, int N)
  {
    int i, t;
    complexo *p;
   
    while (1)
      {
	t = 0;
	for (i=0; i < N-1; i++)
	  {	    
	    if (v[i]->mod < v[i+1]->mod)
	      {
		p = v[i];
		v[i] = v[i+1];
		v[i+1] = p;
		t = 1;
      	      }

	  }

	 if (t == 0)
	      break;
      }
  }

void troca (complexo **v, int i, int j)
 {
   complexo *p;

   p = v[i];
   v[i] = v[j];
   v[j] = p;
 }
   
int main (int argc, char **argv)
  {
    int i, N, ans, tr1, tr2;
    complexo **v;

    if (argc != 2)
      return -1; // help!

    if(sscanf(argv[1],"%d", &N) != 1)
       return 1;
       
    srand(time(NULL));

    v = (complexo**) malloc(N*sizeof(complexo*));
    
    for (i = 0; i < N; i++)
      {
	v[i] = (complexo*) malloc(sizeof(complexo));
	v[i]->re = (((double)rand()/(double)RAND_MAX)*21-7);
        v[i]->im = (((double)rand()/(double)RAND_MAX)*21-7);
	v[i]->mod = modulo(v[i]); // é igual
	//printf("z = %lf + %lf i, ||z|| = %lf \n", v[i]->re, v[i]->im, v[i]->mod);
      }

    ordena(v, N);
    
    for (i = 0; i < N; i++)
      printf("z = %lf + %lf i, ||z|| = %lf \n", v[i]->re, v[i]->im, v[i]->mod);

    printf("Deseja trocar algum par de complexos? (1 - Sim; 0 - Não) ");

    if (scanf("%d", &ans)==1)
      {
	while(ans==1)
	  {
	    printf("Indique o par de complexos que deseja trocar: ");

	    if(scanf("%d %d", &tr1, &tr2)==2) //testar que os complexos existem.
	      troca(v, tr1,tr2);

	    else
	      {
		printf(" Não inseriu nºs.\n");
		return 1; //erro
	      }
	 
	    for (i = 0; i < N; i++)
	      printf("z = %lf + %lf i, ||z|| = %lf \n", v[i]->re, v[i]->im, v[i]->mod);

	    printf("Deseja trocar algum par de complexos? (1 - Sim; 0 - Não) ");
	    
	    scanf("%d", &ans);
	  }
      }
    
    else
      {
	printf(" Não inseriu um nº.\n");
	return 1; //erro
      }

     
    return 0;
  }
