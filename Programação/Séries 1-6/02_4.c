#include <stdio.h>
#include <stdlib.h>

struct time
  {
    int h, m, s;
  };
  
int main (int argc, char **argv)
  {
    unsigned long int s1, s2; // Há 86400 segundos num dia, portanto um int ([-32767; 32767]) ou um unsigned int ([0; 65300]) podem não ser suficientes.
    double m1, m2;  
    int t; // variável de teste
    
    if (argc != 3)
      printf("O formato dos argumentos deve ser <h:m:s>!");
    
    else     
      {
	struct time time1, time2, timesum = {0, 0, 0};
	
	sscanf(argv[1], "%d:%d:%d", &time1.h, &time1.m, &time1.s);
	sscanf(argv[2], "%d:%d:%d", &time2.h, &time2.m, &time2.s);

	/* Verifica se os valores <h:m:s> estão no formato pretendido. */

	if (time1.h > 23 || time1.h < 0 || time2.h > 23 || time2.h < 0)
	  {
	    printf("O formato das horas está errado. Deve ser um inteiro entre 0 e 23!\n");
	    t++;
      	  }
	
	if (time1.m > 59 || time1.m < 0 || time2.m > 59 || time2.m < 0)
	  {
	    printf("O formato dos minutos está errado. Deve ser um inteiro entre 0 e 59!\n");
	    t++;
       	  }
	
	if (time1.s > 59 || time1.s < 0 || time2.s > 59 || time2.s < 0)
	  {
	    printf("O formato dos segundos está errado. Deve ser um inteiro entre 0 e 59!\n");
	    t++; 
	  }

	if (t != 0)
	  return 1; // erro!

	printf("\nInstante 1: %2dh %2dmin %2ds\n", time1.h, time1.m, time1.s);
	printf("Instante 2: %2dh %2dmin %2ds\n\n", time2.h, time2.m, time2.s);

	s1 = time1.h*3600 + time1.m*60 + time1.s;
	s2 = time2.h*3600 + time2.m*60 + time2.s;
	  
	printf("O nº de segundos desde o início do dia é:\n");
	printf("Instante 1: %lu s\n", s1);
	printf("Instante 2: %lu s\n\n", s2);

	/* A divisão deve ser feita com doubles, senão é calculada primeiro com inteiros e só depois convertida em double, o que pode introduzir erros. */

	m1 = time1.h*60 + time1.m + (((double)time1.s)/60); 
	m2 = time2.h*60 + time2.m + (((double)time2.s)/60);

	printf("O nº de minutos desde o início do dia é:\n");
	printf("Instante 1: %.3lf min\n", m1);
	printf("Instante 2: %.3lf min\n\n", m2);

	timesum.s = (time1.s + time2.s);

	if (timesum.s > 59)
	  {
	    timesum.m++;
	    timesum.s = timesum.s - 60;
	  }

	timesum.m = timesum.m + (time1.m + time2.m);

	if (timesum.m > 59)
	  {
	    timesum.h++;
	    timesum.m = timesum.m - 60;
	  }

	timesum.h = (timesum.h + (time1.h + time2.h)) % 24; // ignora a mudança de dia.
	
       	printf("A soma dos dois instantes é %dh %dmin %ds. \n", timesum.h, timesum.m, timesum.s);
	
      }
    
   return 0;
   
  }
