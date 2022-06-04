#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_len (char *s1)
  {
    int i=0;
 
    while(s1[i] != 0)
      i++;

    return i;
  }

char *str_cpy (char *s1, char *s2)
  {
    int i;

    s1 = (char *) malloc ((str_len(s2) + 1)*sizeof(char));

    for (i=0; s2[i] != 0; i++)
   	s1[i] = s2[i];
    
    return s1;
  }

char *str_cat (char *s1, char *s2)
  {
    int i, j;

    i=0;

    while (s1[i] != 0)
	i++;

    for (j = 0; s2[j] != 0; i++, j++)
	s1[i] = s2[j];
    
    return s1;
  }

char *str_gato (char *s1, char *s2)
  {
    
    str_cpy(&s1[str_len(s1)], s2); // Copia o

    return s1;

  }

int main (int argc, char **argv)
  {
    char *cpy, *cat;
    int len1, len2; 

    /* cpy = NULL;
       cat = NULL;*/
    
    if (argc != 3)
      {
	printf ("\n *Erro* Introduza duas strings como argumentos.\n"); 
	return 1;
      }
    
    printf("\n  A primeira string que introduziu foi: '%s'.\n\n", argv[1]);
    printf("\n  A segunda string que introduziu foi: '%s'.\n\n", argv[2]);

    len1 = str_len(argv[1]);
    len2 = str_len(argv[2]);

    if (len1 == 1)
      printf("\n A primeira string que inseriu tem 1 caracter.\n\n");

    else  
      printf("\n  A primeira string que inseriu tem %d caracteres.\n\n", len1);

    if (len2 == 0)
      printf("\n A primeira string que inseriu tem 1 caracter.\n\n");

    else
      printf("\n  A segunda string que inseriu tem %d caracteres.\n\n", len2);

    //  cpy = (char *) malloc ((len1 + 1)*sizeof(char));

    str_cpy(cpy, argv[1]);
 
    printf("\n  A cópia da primeira string é '%s'.\n\n", cpy);

    printf("\n  A cópia da primeira string é '%s'.\n\n", strcpy(cpy, argv[1]));

    cat = (char *) malloc ((len1 + len2 + 1)*sizeof(char));

    cat = str_cat(cpy, argv[2]);

    printf("\n  A concatenação das duas strings é: '%s'.\n\n", cat);

    printf("\n  A concatenação tem %d caracteres.\n\n", str_len(cat));

    cat =  str_gato(argv[1], argv[2]);
    
    printf("\n  A concatenação das duas strings é: '%s'. \n\n", cat);

    printf("\n  A concatenação tem %d caracteres.\n\n", str_len(cat));

    cpy = NULL;
    cat = NULL;
    
    free(cpy);
    free(cat); // :)
    
    return 0;
  }
