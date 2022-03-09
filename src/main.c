#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESZ 256

FILE *fp;
void remove_newline(char *ptr);
void initial_print();
void final_print();
void end_function();
void init_function();
void process_variables_int(char line[256], int count);
void process_variables_array(char line[256], int count);
void process_get_array(char line[256], int count);
void process_set_array(char line[256], int count);
void process_start_variables(char line[256], int count);
void process_end_variables(char line[256], int count);
void process_start_function(char line[256], int count);
void process_end_function(char line[256], int count);
void process_return(char line[256], int count);
int main()
{
   char line[LINESZ];
   int count = 0;

   initial_print();

   // lê uma linha de cada vez
   while (fgets(line, LINESZ, stdin) != NULL)
   {
      count++;
      remove_newline(line);

      // verifica se a linha começa com 'def'
      if (strncmp(line, "def", 3) == 0)
      {
         process_start_variables(line, count);
         continue;
      }

      // Verifica se a linha lida começa com var
      if (strncmp(line, "var", 3) == 0)
      {
         process_variables_int(line, count);
         continue;
      }
      // Verifica se a linha lida começa com vet
      if (strncmp(line, "vet", 3) == 0)
      {
         process_variables_array(line, count);
         continue;
      }
      // verifica se a linha começa com get
      if (strncmp(line, "get", 3) == 0)
      {
         process_get_array(line, count);
         continue;
      }
      // verifica se a linha começa com set
      if (strncmp(line, "set", 3) == 0)
      {
         process_set_array(line, count);
         continue;
      }

      // verifica se a linha começa com 'enddef'
      if (strncmp(line, "enddef", 6) == 0)
      {
         process_end_variables(line, count);
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
         process_end_function(line, count);
         continue;
      }

      // verifica se a linha começa com 'function'
      if (strncmp(line, "function", 8) == 0)
      {
         process_start_function(line, count);
         continue;
      }
   }
   final_print();
   return 0;
}