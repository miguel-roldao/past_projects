#include <stdio.h>
#include <stdlib.h>

/*  Programação, Série 8, Problema 3

    *     *   * * *   * * * *  * * * *
    * * * *   *       *           *
    *  *  *   * **    * * *       *
    *     *   *       *           *
    *     *   * * *   *           *    

 Alexandre Barbosa e Miguel Roldão, 2018  */

void help (int h)
  {
    switch (h)
     {
      case 1:
	printf("\n ** Introduza o número de linhas que deseja ver como argumento, ex: '08_3 <numero>' ** \n\n");
	break;

      case 2:
	printf("\n **ERRO: Introduza um número inteiro como argumento! ex: 08_3 12 ** \n\n");
	break;

      case 3:
      	printf("\n **ERRO: O número que introduziu não é positivo! ** \n\n");
	break;

      case 4:
      	printf("\n **ERRO: O ficheiro não foi aberto corretamente! ** \n\n");
	break;

     case 5:
        printf("\n **ERRO: O ficheiro não foi escrito corretamente! **  \n\n");
	break;

     case 6:
        printf("\n **ERRO: Introduza dois números! ex: 7 3 ** \n\n");
        break;

     case 7:
       printf("\n **ERRO: A combinação que pediu não foi calculada ou não existe! ** \n\n");
       break;

     case 8:
       printf("\n **ERRO:  O posicionamento para a leitura dos dados não foi bem sucedido ** \n\n");
       break;

     case 9:
       printf("\n **ERRO: A leitura dos dados não foi bem sucedida! ** \n\n");
       break;

     case 10:
       printf("\n **ERRO: Introduza 0 ou 1! ** \n\n");
       break;

     case 11:
       printf("\n **ERRO: Pediu um número de linhas demasiado grande! \n\n Por favor, tente com um valor mais pequeno! ** \n\n");
       break;

      default:
	printf("** Introduza o número de linhas que deseja ver como argumento, ex: '08_3 <numero>' ** \n\n");
	break;
      }
   }


int main (int argc, char **argv)
  {
    int n, i, j, **v, N, K, pos, C, t=1;
    FILE *f;

    /* Testa o número de argumentos */

    if (argc != 2)
      {
	help(1);
	return 1;
      }

    /* Teste de leitura do scanf (1)  */
    
    if ((sscanf(argv[1],"%d", &n)) != 1)
      {
	help(2);
	return 1;
      }

    /* Testa se o número de linhas pedido é positivo */

    if (n < 1)
      {
	help(3);
	return 1;
      }

    /* Testa se os números calculados estão dentro dos limites usuais de int */

    if (n > 34)
      {
	help(11);
	return 1;
      }

    v = (int**) malloc(n*sizeof(int*));  // Aloca espaço para o vetor de ponteiros.
    
    for(i=0; i<n; i++)
      {
	v[i] = (int*) malloc((i+1)*sizeof(int));  // Aloca espaço para cada vetor com i+1 de posições.

	v[i][0] = 1;

	for(j=1; j<=i; j++)
	   v[i][j] = (int)(((double)v[i][j-1]) * ((double)(i+1-j))/((double)j));
      }
   
    f = fopen("Pascal.bin", "w+b");

    /* Testa a correta abertura do ficheiro */

    if (f == NULL)
      {
	help(4);
	free(v); // liberta a memória alocada ao vetor caso o programa saia em erro
	fclose(f); // e fecha o canal aberto
	return 1;
      }
    
    printf("\n\n");

    for (i=0; i<n; i++)
      {
	for(j=n; j>i; j--)
	  printf("   ");	
	
	for (j=0; j<=i; j++)
	  {
	    printf("%5d ", v[i][j]);
	    
	    if (fwrite(&v[i][j], sizeof(int), 1, f) != 1)
	      {
		help(5);
		free(v);
		fclose(f);
		return 1;
	      }
	  }
	
	printf("\n");
      }

    printf("\n");

    /* Liberta a memória alocada ao vetor (já não é necessário) */
    
    for (i=0; i<n; i++)
      free(v[i]);
    
    free(v);

    while(t!=0)
      {
	printf("\nQue combinação deseja saber? (n k)  ");

	/* Teste de leitura do scanf (2) */
	
	if (scanf("%d %d", &N, &K) != 2)
	  {
	    help(6);
	    fclose(f);
	    return 1;
	  }

	/* Testa se o número pedido foi calculado */

	if (N > n || K > N || N < 0 || K < 0)
	  {
	    help(7);
	    fclose(f);
	    return 1;
	  }

	pos = (N*(N+1)/2)+K;

	//	printf("%d\n", pos);

	/* Teste de posicionamento no ficheiro */

	if (fseek(f, pos*sizeof(int), SEEK_SET) != 0)
	  {
	    help(8);
	    fclose(f);
	    return 1;
	  }

	/* Teste da leitura dos dados do ficheiro */

	if (fread(&C, sizeof(int), 1, f) != 1)
	 {
	    help(9);
	    fclose(f);
	    return 1;
	  }

	printf("\n O valor da combinação que pediu é: %d.\n\n", C);

	printf("Pretende saber outra combinação? Sim - 1; Não - 0; ");
	
	/* Teste de leitura do scanf (3) */
	
	if (scanf("%d", &t) != 1)
	  {
	    help(6);
	    fclose(f);
	    return 1;
	  }

	/* Testa se o utilizador introduziu 0 ou 1 */

	if (t != 0 && t!= 1)
	  {
	    help(10);
	    fclose(f);
	    return 1;
	  }
      }
    
    fclose(f);
    
    return 0;
  }
