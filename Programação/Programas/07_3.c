#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*

    *     *   * * *   * * * *  * * * *
    * *** *   *       *           *
    *  *  *   * **    * * *       *
    *     *   *       *           *
    *     *   * * *   *           *    

 Alexandre Barbosa e Miguel Roldão, 2018  */
                                               

void help (int h)
  {
    switch (h)
     {
      case 1:
	printf("\n ** Introduza o número até ao qual deseja saber os primos como argumento, ex: '07_3 <numero>' ** \n\n");
	break;

      case 2:
	printf("\n **ERRO: Introduza um número como argumento! ex: 07_3 57 ** \n\n");
	break;

      case 3:
      	printf("\n **ERRO: Introduza um número!** \n\n");
	break;

      case 4:
      	printf("\n **ERRO: Introduza o número 0 ou 1!** \n\n");
	break;

     case 5:
        printf("\n **ERRO: Pediu um primo que não foi calculado!**  \n\n");
	break;

     case 6:
        printf("\n **ERRO: O ficheiro não foi aberto corretamente! ** \n\n");
        break;

      default:
	printf("** Introduza o número até ao qual deseja saber os primos como argumento, ex: '07_4 <numero>' ** \n\n");
	break;
      }
   }

int main (int argc, char **argv)
  {
    int N, *v, i, j, ans, ans2, pos;
    int t;
    FILE *f;

    /* Testa o número de argumentos */
    
    if(argc != 2)
      {
	help(1);
	return 1;
      }

    /* Testa a leitura correta do sscanf */
    
    if (sscanf(argv[1], "%d", &N)!=1)
      {
	help(2);
        return 1;
      }
    
    v = (int*) malloc ((N+1)*sizeof(int)); // N+1 porque conta com o 0

    /* Preenche o vetor com todos os valores iguais a 1. */

    for (i=2; i <= N; i++)
      v[i] = 1;

    /* O 0 e o 1 não são números primos! */

    v[0] = 0;
    v[1] = 0;

    t = (int)sqrt((double)N);
    
    //  printf("%d\n", (int)t);

    /* Anula todos os múltiplos de todos os números primos anteriores */

    for (i=2; i <= t; i++)
      {
	for (j=2; i*j <= N; j++)
	      v[i*j] = 0;
      }

    f = fopen ("primos.bin", "w+");

    /* Testa a correta abertura do ficheiro */

    if (f == NULL)
      {
	help(6);
	free(v);
	return 1;
      }

    /* Escreve os números primos no ficheiro, em binário */

    for (i=0, j=0; i <= N; i++)
      {
	if (v[i]!=0)
	  {
	    printf("%6d  ", i);  // Os números primos correspondem às posições que não foram anuladas.

	    if (fwrite(&i, sizeof(int), 1, f) != 1)
	      ;
	    
	    j++;

	    if (j % 6 == 0)
	      printf("\n");
	  }
      }

     printf("\n\n Quer ver algum número primo? 1 - Sim; 0 - Não;  ");

     /* Teste de leitura do scanf (1) */

    if (scanf("%d", &ans) != 1)
      {
	help(4);
	free(v); // liberta a memória alocada ao vetor caso o programa saia em erro
	fclose(f);
	return 1;
      }
   
    while (ans == 1)
      {
	printf("\nQual é o número de ordem do número primo que deseja ver (de 1 a %d)? ", j);

        /* Teste de leitura do scanf (2) */
	
	if (scanf("%d", &ans2) != 1)
	  {
	    help(3);
	    free(v);
	    fclose(f);
	    return 1;
	  }

	/* Testa se o número lido foi calculado */

	if (ans2>j || ans2<1)
	  {
	    help(5);
	    free(v);
	    fclose(f);
	    return 1;
	  }

	pos = (ans2 - 1) * sizeof(int);   // Se ans == 1 então desejamos ver a posição 0.

	fseek(f, pos, SEEK_SET);

	fread(&i, sizeof(int), 1, f);

	printf("\nO primo que pediu é o %d.\n", i);

	printf("\nQuer ver outro número primo? 1 - Sim; 0 - Não;  ");

	/* Teste de leitura do scanf (3) */

	if (scanf("%d", &ans) != 1)
	  {
	    help(5);
	    free(v);
	    fclose(f);
	    return 1;
	  }
      }
    
   
    printf("\n   *Fim do Programa*\n\n");  
    
    free (v);
    
    fclose(f);
	  
    return 0;
  }
