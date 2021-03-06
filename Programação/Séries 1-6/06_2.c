#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char **argv)
  {
    unsigned short int u = 0;
    unsigned int p[16], i, s;
    char str[17];

    p[0] = 1;

    srand(time(NULL));

    for (i = 0; i < 16; i++)
      {
	if (i < 15)
	  p[i+1] = 2 * p[i];
	
	if ((rand() % 2) == 1)
	  u = u | p[i];

	str[i] = (u & p[i] ? 49 : 48);
      }

    str[16] = 0;  

    
    printf("\n A string é '%s'\n\n", str);
    
    //    printf("%hu\n", u);

    while(1)
      {
	printf("Qual é o spin cujo sinal pretende inverter? (1-16, 0 -> Sair)  ");

	if (scanf("%u", &s) == 1)  // testa se o input é um unsigned int
	  {
	
	    if (s < 1)
	      break;

	    if (s > 16)
	      {
		printf(" Introduza um número entre 1 e 16\n\n *Fim do programa* \n");
		return 1;
	      }

	    u = u ^ p[s-1];

	    for (i = 0; i < 16; i++)
	      str[i] = (u & p[i] ? 49 : 48);

	    printf("\n   Agora é '%s'\n\n", str);
	  }
	
	else
	  {
	    printf(" Introduza um número entre 1 e 16.\n\n *Fim do programa* \n");
	    break;
	  }
      }

    return 0;
  }
