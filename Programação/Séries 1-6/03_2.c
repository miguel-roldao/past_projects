#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help (int h)  // Reage conforme o erro que ocorreu e diz ao utilizador o que deve fazer.
 {
   if ( h == 1 )   // argc != 4
     printf("\n  Não introduziu o número de argumentos certos.\n\n  Por favor introduza uma string seguida de dois caracteres.\n\n   *Exemplo: 'hello h j'*\n\n");

   if ( h == 2 )   // sscanf dos caracteres mal sucedida
     printf("\n  A leitura dos argumentos não foi bem sucedida. Certifique-se que introduziu os argumentos como exigido.\n\n   *Exemplo: 'hello h j'*\n\n");

   if ( h == 3 )   // o primeiro caracter não existe na string
     printf("  Escolha, de preferência, como primeiro caracter, um dos presentes na string inicial.\n\n");
 }

int nx (char *str, char c)  // função que conta o número de vezes que o caracter aparece
 {
   int i, t;

   t=0;
   
   for (i=0; str[i] != 0; i++)
     {
       if (str[i] == c)
	 t++;
     }

   return t;
 }

int pos (char *str, char c)  // função que retorna a primeira posição do caracter na string
 {
   int i;

   for (i=0; str[i] != 0; i++)
     {
       if (str[i] == c)
	   return i;
     }

   i = -1; // se o caracter não existir, o retorno é -1.
   return i;
 }

void trade (char *str, char c1, char c2)  // função que troca os caracteres
 {
   int i;

   for (i=0; str[i] != 0; i++)
     {
       if (str[i] == c1)
	   str[i] = c2;
     }
 }

int main(int argc, char **argv)
  {
    char *strcopy, c1, c2;
    int a, b, teste1, teste2; 
      
    if (argc != 4)
      {
	help(1);
	return 1;  // erro 1! (ver função help)
      }

    if (strlen(argv[2]) != 1 || strlen(argv[3]) != 1)  // testa que o 2º e o 3º argumento são caracteres únicos
      {
	help(2);
	return 2;
      }
    
    //sscanf(argv[1], "%s", str);
    c1 = argv[2][0]; 
    c2 = argv[3][0];          // teste2 = sscanf(argv[3], "%c", &c2);

    if (teste1 != 1 || teste2 != 1)
      {
	help(2);
	return 2;  // erro 2! (ver função help) 
      }
    
    printf("\n  A string que introduziu foi: '%s'.\n\n", argv[1]);
    a = nx(argv[1], c1);
    b = pos(argv[1], c1);

    if ( b == -1)  // erro 3! (ver função help)
      {
	printf("  O caracter '%c' não aparece na string.\n\n", c1);
	help(3);
	return 3;
      }
    
    else
      {
	if ( a == 1)
	  printf("  O caracter '%c' aparece 1 vez na string.\n\n", c1);
	else 
          printf("  O caracter '%c' aparece %d vezes na string.\n\n", c1, a);
	printf("  O caracter '%c' aparece pela primeira vez na posição %d da string.  ->  (É o %dº caracter.)\n\n", c1, b, b+1);
	printf("  A string original é '%s'.\n\n  Efetuamos de seguida a troca de todos os caracteres '%c' por '%c':\n\n", argv[1], c1, c2);
      }
    
    int size = (strlen(argv[1])+1)*sizeof(char);  // sizeof(char) = 1 (pode ser omitido)
    
    strcopy = (char*) malloc(size);  // aloca espaço para a string cópia
    
    strcpy(strcopy, argv[1]);
    
    trade(strcopy, c1, c2); 

    printf("  A string após a troca é:  '%s'.\n\n", strcopy);

    free(strcopy);
    
    return 0;
  }
    
  
