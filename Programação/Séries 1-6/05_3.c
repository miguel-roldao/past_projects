#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
  {
    int i;
    char v[1000]; 
    FILE *f1, *f2;
    
    if(argc != 4)
      {
	printf("./programa <M2m/m2M> <file_de_leitura> <file_de_escrita>\n\n");
	return 1;
      }
    
    f1 = fopen(argv[2], "rt");  //testar abertura do ficheiro

    f2 = fopen(argv[3], "wt");

    if (strcmp(argv[1], "M2m")==0)
      {
	while (fgets(v, 1000, f1)!=NULL)
	  {	    	
	    for(i=0; v[i] != 0; i++)
	      {
		if (v[i] > 64 && v[i] < 91)
		  v[i] = v[i] + 32;
	      }

	    fprintf(f2, "%s", v);
	  }
      }
    
    if(strcmp(argv[1], "m2M")==0)
      {
	while (fgets(v, 1000, f1)!=NULL)
	{
	  for(i=0; v[i]!=0; i++)
	    {
	      if (v[i] > 96 && v[i] < 122)
		v[i] = v[i] - 32;
	    }

	  fprintf(f2, "%s", v);
	}
      }
    
    fclose(f1);
    fclose(f2);
    return 0;
    
  }
