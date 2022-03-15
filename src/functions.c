#include <stdio.h>
#include <string.h>
#include "functions.h"

void process_function_start(char line[256], int count)
{
  FILE *fp;
  int r, s, i1, i2, i3;
  char v1, v2, v3;
  printf("Declaração de uma função:\n");
  printf("Linha %d: %s\n", count, line);
  printf("---\n");
  r = sscanf(line, "function f%d p%c%d p%c%d p%c%d", &s, &v1, &i1, &v2, &i2, &v3, &i3);

  fp = fopen("file.S", "a+");
  fprintf(fp, "f%d:\n", s);
  fclose(fp);
  init_function();

  switch (r)
  {
  case 7:
    printf("Parâmetros da função f%d: %c%d, %c%d, %c%d\n", s, v1, i1, v2, i2, v3, i3);
    printf("---\n");
    break;
  }
}

void process_function_end(char line[256], int count)
{
  end_function();
  printf("Linha %d: %s\n", count, line);
  printf("Fim da função\n");
  printf("---\n");
}

void process_return(char line[256], int count)
{
  int ret; // para armazenar o  valor inteiro do retorno
           //}
  FILE *fp;
  char r1, r2; // para pegar o tipo de retorno e o tipo de valor do retorno
  char v1,
      v2, v3;
  int r, s, i1, i2, i3, t;

  fp = fopen("file.S", "a+");
  t = sscanf(line, "return %c%c%d", &r1, &r2, &ret);
  switch (r1)
  {
  case 112: // p na tabela ascii
    printf("retorno de parâmetro: ");
    break;
  case 118: // v na tabela ascii
    printf("retorno de variável do escopo da função: ");
    break;
  case 99: // c na tabela ascii
    printf("retorno de constante: ");
    break;
  default:
    printf("retorno inválido\n");
    break;
  }

  if (r2 == 105 && r1 == 99)
  { // i n a tabela ascii && c na tabela ascii
    printf("inteiro, valor: %d\n", ret);
  }
  else if (r2 == 105 && r1 != 99)
  {
    printf("inteiro, %c%c%d\n", r1, r2, ret);
  }
  else if (r2 == 97)
  { // a na tabela ascii
    printf("array de inteiro, %c%c%d\n", r1, r2, ret);
  }
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
