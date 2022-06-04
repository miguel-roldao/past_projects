/* Headers */

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#if def_win32
// stat

#else
// lstat

#endif


int main (int argc, char **argv)
 {
   DIR *d;
   struct dirent *dent;
   struct stat buf;
   struct tm *time1;
   char str[32], str2[32], str_dir[256]; // alocar?

   if (argc == 1)
     {
       d = opendir(".");

       while ((dent = readdir(d)) != NULL)
	 {
	   printf("%s", dent->d_name);
	   printf("\n");
	   stat(dent->d_name, &buf);
	 }

     }

   if (argc == 2)
     {

       d = opendir(".");

       /* -l */

       if (strcmp(argv[1], "-l") == 0)
	 {
	   time1 = localtime(&buf.st_mtime);
	   strftime(str, 32, "%b %d %H:%M", time1);

	   while ((dent = readdir(d)) != NULL)
	     {
	       printf("%s %lu %s", dent->d_name, buf.st_size, str);
	       stat(dent->d_name, &buf);
	       // printf("%s", str);
	       printf("\n");
	     }
	   
	 }

       /* Directoria */

       else
	 {
	   strcpy(str_dir, argv[1]);
	   d = opendir(str_dir);

	   strcat(str_dir, "/"); // CASO WINDOWS LINUX + LSTAT

	   if (d == NULL)
	     {
	       printf("** ERRO: Diretoria inexistente! ** \n\n");
	       return -1;
	     }

	   strcpy(str2, strcat(argv[1], "/"));

	   while ((dent = readdir(d)) != NULL)
	     {
	       strcat(str_dir, dent->d_name); 
	       printf("%s", str_dir);
	       stat(dent->d_name, &buf);
	       strcpy(str_dir, str2);
	       printf("\n");
	     }
	   
	 }

       if (argc == 3)
	 {
	   // então há uma diretoria e LS

	 }

	 
     }
       

   closedir(d);
   
 }

// SEPARADOR DIFERENTE EM WINDOWS \ EM VEZ DE /

/*

4
.   Fa ̧ca  uma  implementa ̧c ̃ao  elementar  da  fun ̧c ̃ao  ’ls’  de  unix  (ou  ’dir’  do
MS/DOS  ou  janela  de  comandos  do  Microsoft  Windows),  que  mostra  os
ficheiros contidos numa directoria:
ls [ -l ] [
directoria
]
em que os [
...
] indicam que se pode omitir essa informa ̧c ̃ao, “
directoria
” re-
presenta a pasta de que se pretende listar o conte ́udo e “-l” significa que se
dever ́a acrescentar a essa informa ̧c ̃ao o n ́umero de bytes do ficheiro e a data
em que foi alterado pela  ́ultima vez.
O resultado final dever ́a ser uma lista em que cada linha apresenta um ficheiro
diferente e, no caso da op ̧c ̃ao “-l”, o seu aspecto deve ser o seguinte:
273635 Nov 16 09:34 ficheiro.ext
Para tal dever ́a usar as fun ̧c ̃oes:
•
opendir
(’dirent.h’):  Abre  uma  directoria  para  leitura.   Vagamente
equivalente a ’fopen’ para ficheiros.
•
readdir
(’dirent.h’):   cada  vez  que   ́e  chamada  retorna  um  ponteiro
(struct dirent *) para a informa ̧c ̃ao do membro da directoria em causa.
•
stat
(para windows) e
lstat
(para unix) (’sys/stat.h’): d ̃ao a informa ̧c ̃ao
referente a um dado ficheiro (struct stat).
•
closedir
(’dirent.h’):  fecha uma directoria aberta com ’opendir’.
•
localtime
(’time.h’):   recebe  como  argumento  um  ponteiro  para  o
tempo ’
time
t
’ e retorna um ponteiro para a estrutura ’
struct tm
’.
•
strftime
(’time.h’):  idˆentica  a
sprintf
para  escrever  o  tempo  numa
string.
Nota1:
Para mais detalhes sobre as fun ̧c ̃oes ver manuais da biblioteca de C.
Nota2:
o  programa  dever ́a  poder  ser  compilado  em  unix  ou  em  windows
fornecendo os resultados correctos */
