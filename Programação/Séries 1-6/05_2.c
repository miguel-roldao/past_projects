#include <stdio.h>
#include <stdlib.h>

void help (int t)
  {
   switch (t)
     {
     case 1:
       printf("\n** Introduza 2 inteiros como argumentos! **\n");
       break;
 
     case 2:
       printf("\n** Erro: <./05_2> <N> <M>, com N menor ou igual a M **\n");
       break;

     case 3:
       printf("\n** Erro na abertura do ficheiro! **");
       break;

     case 4:
       printf("\n** Erro: leitura incorreta do sscanf! **");
       break;
     } 
  }

void sort (double *v, unsigned long int len)   // bubble sort
  {
    int t;
    unsigned long int i;
    double trade;
       
    while (1)
      {
	t = 0;
	
	for (i=0; i < (len-1); i++)
	  { 
	    if (v[i] > v[i+1])
	      {
		trade = v[i];
		v[i] = v[i+1];
		v[i+1] = trade;
		t = 1;
	      }
	  }
	
	if(t==0)
	  break;
      }
  }

unsigned long int re_alloc(double *v, unsigned long int len)
  {
    unsigned long int i, j;

    /* Elimina os valores repetidos */

    for(i=1, j=0; i<(len+1); i++)
      {
	if(v[i] != v[j])
	  {
	    j++;
	    v[j] = v[i];
	  }
      }
    
    v = (double*) realloc (v, j * sizeof(double));

    return j;
    
  }
	
		
int main(int argc, char **argv)
  {    
    unsigned long int n, m, len, i, j, k;
    double *v;
  
    FILE *C;

    C = fopen("dados.txt", "wt");
    
    if (argc != 3)
      {
	help(1);
        return 1;
      }

    if (C == NULL) // testa a abertura do ficheiro
      {
        help(3);
	return 1;
      }

    if (sscanf(argv[1], "%lu", &n) !=1 || sscanf(argv[2], "%lu", &m) != 1)
      {
	help(4);
	return 1;
      }

    printf("\n N: %lu\n M: %lu\n", n, m);
    
    if (m < n)
      {
        help(2);
	return 1;
      }

    len = n*m;
    
    v = (double *) malloc((len)*sizeof(double));

    for (i = 1, k=0; i < n+1; i++)
      {
	for (j = 1; j < m+1; j++, k++)
	  v[k] = (double) i / (double) j;	   
      }
        
    sort(v, len);
        
    len = re_alloc(v, len);
    
    for (k = 0; k < len; ++k)
      fprintf(C, "v[%lu] = %lf \n", k, v[k]);
                
    fclose(C);

    free(v);
    
    return 0;
    
  }
