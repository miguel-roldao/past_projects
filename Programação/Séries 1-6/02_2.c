#include <stdio.h>
#include <math.h>

double convert_arg(double x)
   {
     double y = fmod(x, 2*M_PI);
     if (y < 0)
       y = y + 2*M_PI;
     return y;
   }

double factorial(int n)
  {
    int i;
    double j = (double) n;
    for (i = 1; i < n; i++)
      j = j * (double) i;
    return j;
  }

double sin_taylor(double x)
  {
    double sinx = 0;
    double err = 1;
    int i;
    
    for (i = 0; fabs(err) >= 1e-10; i++)
      {
	err = pow(-1, i) * (pow(x, 2*i+1)/factorial(2*i+1));
	sinx = sinx + err;
	//printf("%d %lf\n", i, err);
      }
    
    return sinx;
  }
    
int main (int argc, char **argv)
  {
    double x, *v, y;
    int n;
    sscanf(argv[1], "%lf", &x);

    x = convert_arg(x);

    y = sin_taylor(x); // não funciona

    printf("%lf\n", y);

    printf("%lf\n", sin(x));

    /* Teste convert_arg 
       printf("%lf", x); */

    /*   sscanf(argv[1], "%d", &n);
       y = factorial (n);
       printf("%lf", y); */
    
    return 0;
  }
