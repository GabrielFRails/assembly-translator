#include <stdio.h>
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

void init_function()
{
   FILE *f;
   char str1[] = "   pushq %rbp\n";
   char str2[] = "   movq %rsp, rbp\n\n";

   f = fopen("file.S", "a+");
   fprintf(f, "%s", str1);
   fprintf(f, "%s", str2);
   fclose(f);
}

void end_function()
{
   FILE *f;
   char str1[] = "   leave\n";
   char str2[] = "   ret\n";

   f = fopen("file.S", "a+");
   fprintf(f, "%s", str1);
   fprintf(f, "%s", str2);
   fclose(f);
}

void declare_variable(int value)
{
}
void declare_array(int *array)
{
}