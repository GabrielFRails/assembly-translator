#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESZ 256

void remove_newline(char *ptr);

int main() {

   char v1, v2, v3;
   int r, s, i1, i2, i3;
   int inicio, fim, passo;
   char line[LINESZ];
   int count = 0;

   // lê uma linha de cada vez
   while(fgets(line, LINESZ, stdin) != NULL) {
      count++;
      remove_newline(line);

      if (strncmp(line, "def", 3) == 0) {
         printf("Linha %d: %s\n", count, line);
         printf("Definição escopo:\n");
         printf("---\n");	      
         continue;
      }

      if (strncmp(line, "enddef", 6) == 0) {
         printf("Linha %d: %s\n", count, line);
         printf("Fim da definição de escopo:\n");
         printf("---\n");	      
         continue;
      }

      // Verifica se line começa com 'end' (3 letras)
      if (strncmp(line, "end", 3) == 0) {
         printf("Linha %d: %s\n", count, line);
         printf("Fim da função\n");
         printf("---\n");	      
         continue;
      }


      if (strncmp(line, "function", 8) == 0) {
         printf("Definição de função:\n");
         printf("Linha %d: %s\n", count, line);
         printf("---\n");	 

         r = sscanf(line, "function f%d p%c%d p%c%d p%c%d", &s, &v1, &i1, &v2, &i2, &v3, &i3);
         switch (r) {
            case 7:
               printf("Parâmetros da função f%d: %c%d, %c%d, %c%d\n", s, v1, i1, v2, i2, v3, i3);
               printf("---\n");
               break;
         }
         continue;
      }

   }

   printf("Fim do arquivo\n\n");
   return 0;
}