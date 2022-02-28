#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESZ 256

void remove_newline(char *ptr);

int main() {
// variáveis para função {
   char v1, v2, v3;
   int r, s, i1, i2, i3;
   char line[LINESZ];
   int count = 0;
//}

// variáveis para o retorno da função {
   char r1, r2; // para pegar o tipo de retorno e o tipo de valor do retorno
   int t, ret; // para armazenar o valor do sscanf e o valor inteiro do retorno
//}

// variáveis para o corpo da função {
//}
   // lê uma linha de cada vez
   while(fgets(line, LINESZ, stdin) != NULL) {
      count++;
      remove_newline(line);

      // verifica se a linha começa com 'def'
      if (strncmp(line, "def", 3) == 0) {
         printf("Linha %d: %s\n", count, line);
         printf("Definição escopo de função: {\n");
         printf("---\n");	      
         continue;
      }

      // verifica se a linha começa com 'enddef'
      if (strncmp(line, "enddef", 6) == 0) {
         printf("}\nLinha %d: %s\n", count, line);
         printf("Fim da definição de escopo:\n");
         printf("---\n");	      
         continue;
      }

      // verifica se a linha começa com 'return'
      if (strncmp(line, "return", 6) == 0) {
         t = sscanf(line, "return %c%c%d", &r1, &r2, &ret);
         switch (r1) {
            case 112: //p na tabela ascii
               printf("retorno de parâmetro: ");
               break;
            case 118: //v na tabela ascii
               printf("retorno de variável do escopo da função: ");
               break;
            case 99: // c na tabela ascii
               printf("retorno de constante: ");
               break;
            default:
               printf("retorno inválido\n");
               break;
         }
         
         if (r2 == 105 && r1 == 99) { // i n a tabela ascii && c na tabela ascii
            printf("inteiro, valor: %d\n", ret);
         } else if (r2 == 105 && r1 != 99) {
            printf("inteiro, %c%c%d\n", r1, r2, ret);
         } else if (r2 == 97) { // a na tabela ascii
            printf("array de inteiro, %c%c%d\n", r1, r2, ret);
         }
         
      }

      // Verifica se line começa com 'end' (3 letras)
      if (strncmp(line, "end", 3) == 0) {
         printf("Linha %d: %s\n", count, line);
         printf("Fim da função\n");
         printf("---\n");	      
         continue;
      }

      // verifica se a linha começa com 'function'
      if (strncmp(line, "function", 8) == 0) {
         printf("Declaração de uma função:\n");
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