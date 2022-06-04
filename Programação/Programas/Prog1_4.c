#include <stdio.h>
#include <stdlib.h>

char *str_chr(char *string, int c)
  {
    int i;
    
    for(i=0; string[i] != 0; i++)
      {
	if(string[i] == c)
	  return &string[i];
      }
    return NULL;
  }

/* size_t str_spn (const char *string, const char *skipset)
  {
    int i, j = 0;
    
    for(i=0; skipset[i] != 0; i++)
      {
	if (string[j] == skipset[i])
	  {
	    j++;
	    i=-1;
	  }
      }

    return j;
  } */

size_t str_spn (const char *string, const char *skipset)
  {
    int i=0, j = 0;

    while (string[i] != 0)
	{
  	  for (j = 0; skipset[j] != 0; j++)
	    {
	      if (string[i] == skipset[i])
		{ 
		 i++;
		}
            }
        }

   return i;

  }


char *str_cpy (char *str_to, const char *str_from)
  {
    int i = 0;
    while (str_from[i] != 0)
      {
	str_to[i] = str_from[i];
	i++;
      }
    str_to[i] = 0;

    return str_to;
  }

int main(int argc, char **argv)
  {
    int i;
    char c, *s;
    
    if(argc != 4)
      {
	printf("\n **Erro: Introduza duas strings e um caracter como argumentos!**\n\n");
	return 1;
      }

    c = argv[3][0];

    printf("\nO resultado do strchr é: %p\n\n", str_chr(argv[1], c));

    printf("O resultado do strspn é: %ld\n\n", str_spn(argv[1], argv[2]));

    for(i=0; argv[1][i]!=0; i++);
    
    s = (char*) malloc((i+2)*sizeof(char));
    
    printf("O resultado do strcpy é: %s\n\n", str_cpy(s, argv[1]));

    free (s);

    return 0;
    
  }


    
