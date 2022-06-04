#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
  {
    int i, len;
    char v[1024], placeholder; 
    FILE *f1, *f2;
    
    if(argc != 3)
      {
	printf("./programa <ficheiro_de_leitura> <ficheiro_de_escrita>\n\n");
	return 1;
      }
    
    f1 = fopen(argv[1], "rt");  //testar abertura do ficheiro

    f2 = fopen(argv[2], "wt");

    
    while (fgets(v, 1024, f1)!=NULL)
	{
	  len = strlen(v) - 1;
	  
	  for(i=0; i<(len/2); i++)
	    {
	      placeholder = v[i];
	      v[i] = v[len-i];
	      v[len-i] = placeholder;
	    }

	  fprintf(f2, "%s", v);
	}
     
    
    fclose(f1);
    fclose(f2);
    return 0;
    
  }
