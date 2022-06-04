#include <stdio.h>
#include <stdlib.h>

void ordena (int size, double *v)
  {
    int i, t=1;
    double troca;

    while(t==1)
      {
	t = 0;
	
	for(i=0; i < size; i++)
	  {
	    if(v[i] >v[i+1])
	      {
		troca = v[i];
		v[i] = v[i+1];
		v[i+1] = troca;

		t = 1;
	      }
	  }
      }
  }

int realocar(double *v, int len)
  {
    int i, j;

    for(i=1, j=0; i<=len; i++)
      {
	if(v[i] != v[j])
	  {
	    j++;
	    v[j] = v[i];
	  }
      }
    v = (double*) realloc(v, (j+1)*sizeof(double));

    return (j+1);   //  (j+1) -> new size of vector
  }    

int main(int argc, char **argv)
  {
    int  n, m, i, j, p;
    double *v;
    FILE *f;
    
    if(argc != 3 || sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1 || n < 1 || m < 1)
      {
	printf("\n Introduza dois números inteiros positivos como argumentos.\n\n");
	return 1;
      }

    if (n > m)
      {
	printf("\n **Erro: O primeiro argumento deve ser menor ou igual ao segundo!**\n\n");
	return 1;
      }

    if(n > 250 || m > 250)
      {
	printf("\n Introduza números mais pequenos!\n\n");
	return 1;
      }

    printf("\n n: %d ; m: %d\n", n, m);

    v = (double*) malloc(n * m * sizeof(double));

    for(i=0; i<n; i++)
      {
	for(j=0; j<m; j++)
	  {
	    p = i+j*n;    // Calcula a posição do vetor em que vai ser escrito cada valor.
	    v[p] = (double)(i+1)/(double)(j+1);
	    //	    printf("\n v[%d] = %lf\n", p, v[p]);
	  }
	//	printf("\n");
      }

    ordena(p, v);

    /* for(i=0; i<n*m; i++)
       printf("v[%d] = %lf\n", i, v[i]);   */
    
    p = realocar(v, p);

    // printf("\n Depois de realocar o espaço do vetor: \n\n");
    
    /*  for(i=0; i < p; i++)
      printf("v[%d] = %lf\n", i, v[i]);

      printf("\n");*/

    if((f = fopen("dados.dat", "wt")) == NULL)
      {
	printf("\n **Erro na abertura do ficheiro!** \n\n");
	return 1;
      }

    for(i=0; i < p; i++)
      {
	if(fwrite(&v[i], sizeof(double), 1, f) != 1)
	  {
	    printf("\n **Erro de escrita no ficheiro!** \n\n");
	    fclose (f);
	    free(v);
	    return 1;
	  }	
      }

    printf("\nEscrita terminada corretamente!\n\n");
    
    fclose (f);
      
    free (v);

    return 0;
  }
