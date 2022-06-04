#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
  {
    int n, m, i, j;
    double p, mag, mag_soma = 0;
    char *N;

    if (argc != 3)
      {
	printf("Introduza N e M como argumentos");
	return 1;
      }
    if( sscanf(argv[1], "%d", &n)!= 1 || sscanf(argv[2], "%d", &m)!= 1)
      {
	printf("Os argumentos não foram lidos com sucesso.");
	return 1;
      }

    srand(time(NULL));
    
    N = (char*) malloc(n*sizeof(char)); //não é preciso terminador pq é um vetor de char que não é string. São só 0/1

    for (j=0; j<m; j++)
      {
	mag = 0;
	
	for (i=0; i<n; i++)
	  {
	    p = rand();

	    if (p < 1073741824) // RAND_MAX /2
	      {
		N[i] = 48;
		mag = mag - 0.5;
	      }
	    
	    else
	      {
		N[i] = 49;
		mag = mag + 0.5;
	      }

	    //	    printf("N[%d][%2d] = %c\n", j, i, N[i]);	  
	  }
	mag_soma = mag_soma + mag;
	
       	printf("\n***[%d] Magnetização: %.3lf ***\n", j+1, mag);      
      }

    printf("\n---- Magnetização média: %.4lf ----\n", mag_soma/m);
    printf("\n... Magnetização média por spin: %.4lf ...\n", mag_soma/(m*n));
    
    // RAND_MAX         2147483647

    free(N);
    
    return 0;
  }
    
