#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "variables.h"
#include "general.h"
#include "arrays.h"

#define LINESZ 256

int main()
{
   char line[LINESZ];
   int count = 0;
   int size_pile = 0;

   initial_print();

   // lê uma linha de cada vez
   while (fgets(line, LINESZ, stdin) != NULL)
   {
      count++;
      remove_newline(line);

      // verifica se a linha começa com 'def'
      if (strncmp(line, "def", 3) == 0)
      {
         fgets(line, LINESZ, stdin);
         remove_newline(line);
         //process_local_variables_start(line, count);

         while(strncmp(line, "enddef", 6) != 0){
            process_local_int_variables(line, &size_pile);
            fgets(line, LINESZ, stdin);
            remove_newline(line);
         }
         
         printf("tamanho da pilha: %d\n", size_pile);
         size_pile = 0;
         //process_local_variables_end(line, count);
         continue;
      }

      // verifica se a linha começa com get
      if (strncmp(line, "get", 3) == 0)
      {
         process_get_array_element(line, count);
         continue;
      }
      // verifica se a linha começa com set
      if (strncmp(line, "set", 3) == 0)
      {
         process_set_array_element(line, count);
         continue;
      }

      // verifica se a linha começa com 'return'
      if (strncmp(line, "return", 6) == 0)
      {
         process_return(line, count);
      }

      // Verifica se line começa com 'end' (3 letras)
      if (strncmp(line, "end", 3) == 0)
      {
         if ((strncmp(line, "endif", 5) != 0)) {
            process_function_end(line, count);
            continue;
         }
      }

      // verifica se a linha começa com 'function'
      if (strncmp(line, "function", 8) == 0)
      {
         process_function_start(line, count);
         continue;
      }

      //verifica se linha começa com 'if'
      if (strncmp(line, "if", 2) == 0) {
         process_if(line, count);
         continue;
      }
      //verifica se a linha começa com endif
      if (strncmp(line, "endif", 5) == 0) {
         process_end_if(line, count);
         continue;
      }
   }
   return 0;
}