#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "variables.h"
#include "general.h"
#include "arrays.h"
#include "statements.h"

#define LINESZ 256

int main()
{
   char line[LINESZ];
   int size_pile = 0;
   int vl_addrs[5] = {0}, param_addrs[3] = {0}, param_types[3] = {0};

   initial_print();

   // lê uma linha de cada vez
   while (fgets(line, LINESZ, stdin) != NULL)
   {
      remove_newline(line);

      // verifica se a linha começa com 'def' e processa a declaração de variáveis locais
      if (strncmp(line, "def", 3) == 0)
      {
         fgets(line, LINESZ, stdin);
         remove_newline(line);

         size_pile = 0;
         for(int i=0; i<5; i++){
            vl_addrs[i] = 0;
         }
         while(strncmp(line, "enddef", 6) != 0){
            process_local_int_variables(line, &size_pile, vl_addrs);
            fgets(line, LINESZ, stdin);
            remove_newline(line);
         }
         
         allocate_pile(&size_pile, param_types, param_addrs);

         continue;
      }
      
      // verifica se a linha começa com get
      if (strncmp(line, "get", 3) == 0)
      {
         process_get_array_element(line, vl_addrs);
         continue;
      }
      // verifica se a linha começa com set
      if (strncmp(line, "set", 3) == 0)
      {
         process_set_array_element(line, vl_addrs);
         continue;
      }

      // verifica se a linha começa com 'return'
      if (strncmp(line, "return", 6) == 0)
      {
         process_return(line, vl_addrs);
      }

      // Verifica se line começa com 'end' (3 letras)
      if (strncmp(line, "end", 3) == 0)
      {
         if ((strncmp(line, "endif", 5) != 0)) {
            process_function_end();
            continue;
         }
      }

      // verifica se a linha começa com 'function'
      if (strncmp(line, "function", 8) == 0)
      {
         for(int i=0; i<3; i++){
            param_addrs[i] = 0;
            param_types[i] = 0;
         }
         process_function_start(line, param_types);
         continue;
      }

      //verifica se linha começa com 'if'
      if (strncmp(line, "if", 2) == 0) 
      {
         process_if(line, vl_addrs);
         continue;
      }
      //verifica se a linha começa com endif
      if (strncmp(line, "endif", 5) == 0) 
      {
         process_end_if();
         continue;
      }

      // verifica se a linha tem atribuição simples ou com chamada de função
      if (strstr(line, "=") != NULL){
         if( strstr(line, "call") != NULL){
            process_attr_with_function_call(line, param_addrs, vl_addrs, param_types);
         }
         else{
            process_simple_attr(line, vl_addrs);
         }
         continue;
      }
   }
   return 0;
}