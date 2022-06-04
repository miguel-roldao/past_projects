#include <stdio.h>

double **matriz(char *f1, int *dim)
  {
    double **v;
    int n, m, dim, i, j;
    FILE *f;

    f = fopen(f1, "rt");
    fscanf(f1, "%d %d", &n, &m);


    v = (double**) malloc(n*sizeof(double*));

    for (i=0; i < n; i++)
      {
	v[i] = (double*) malloc(m*sizeof(double)
	
    printf("%d", dim);

    for (i=0; i<n; i++)
      {
	for(j=0; j<m; j++)
	  fscanf(f1, "%lf ", &v[i][j]);
      }	     

    return v;
    
  }

int main (int argc, char **argv)
  {
    int dim;
    FILE *f1, *f2;
    double **v;

    
  }

	// &*k = n;
