#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//acrescentar comentários sarcásticos quando a pessoa introduzir um número maior quando lhe dizem que é menor e  quando precisa de muitas tentativas (> log2 n)

int main()
{
  srand(time(NULL));
  int i, n, d, guess;
  int max = 1000; 

  //n = (int)(((double)rand()/(double) RAND_MAX)*(double) max);

  n = rand() % (max+1); // mas não são exatamente equiprováveis!

  //printf("%d\n", n);

  printf("Adivinhe em que número pensei (de 0 a 1000)! ");
  scanf("%d", &guess);
  i = 0;
  
  while(1)
    {
      if (guess < n)
	{
	  printf("Erraste! :(\nTenta um número maior!");
	  d = abs(guess-n);
          if (d > 250)
	    printf("Estás muito longe!");
	  if (d > 100 && d <= 250)
	    printf("Estás longe!");
	  if (d > 50 && d <= 100)
	    printf("Já estás perto!");
	  if (d <= 50)
	    printf("Estás mesmo quase!");
	  scanf("%d", &guess);
	  i++;
	}

      if (guess > n)
	{
	  printf("Erraste! :(\nTenta um número mais pequeno!");
	  d = abs(guess-n);
          if (d > 250)
	    printf("Estás muito longe!");
	  if (d > 100 && d <= 250)
	    printf("Estás longe!");
	  if (d > 50 && d <= 100)
	    printf("Já estás perto!");
	  if (d <= 50)
	    printf("Estás mesmo quase!");
	  scanf("%d", &guess);
	  i++;
	}
      if(guess == n)
	{
	  printf("Parabéns, acertaste!! :)\n\nTiveste %d palpites errados.\n", i);
	  break;
	}
     
    }
  
  return 0;
}
