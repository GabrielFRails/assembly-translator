#include <stdio.h>
#include "general.h"

void remove_newline(char *ptr)
{
   while (*ptr)
   {
      if (*ptr == '\n')
      {
         *ptr = 0;
      }
      else
      {
         ptr++;
      }
   }
}

void initial_print()
{
   FILE *f;
   char str1[] = ".section .rodata\n\n.data\n\n.text\n\n";

   f = fopen("file.S", "w");
   fprintf(f, "%s", str1);
   fclose(f);
}