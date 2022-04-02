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

void allocate_pile(int * size_pile, int * param_types, int * param_addrs){

   FILE * fp = fopen("file.S", "a+");
   int total_size = *size_pile;
   int aux;

   for(int i=0; i<3; i++){
      if (param_types[i] != 0){
         if (total_size % 8 ==0) total_size += 8;
         else total_size += 12;
         switch(i){
            case 0:
               fprintf(fp, "\t# %%rdi -> %d(%%rbp)\n", -total_size);
               param_addrs[i] = -total_size;
               break;
            case 1:
               fprintf(fp, "\t# %%rsi -> %d(%%rbp)\n", -total_size);
               param_addrs[i] = -total_size;
               break;
            case 2:
               fprintf(fp, "\t# %%rdx -> %d(%%rbp)\n", -total_size);
               param_addrs[i] = -total_size;
               break;   
         }
      }
      
   }

   if(total_size % 16 != 0){
      aux = total_size / 16;
      aux++;
      total_size = aux * 16;
   }

   fprintf(fp, "\tsubq $%d, %%rsp\n", total_size);

   fclose(fp);
}