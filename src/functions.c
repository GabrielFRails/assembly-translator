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
  char registrador[4] = "";

  fp = fopen("file.S", "a+");
  t = sscanf(line, "return %c%c%d", &r1, &r2, &ret);
  switch (r1)
  {
  case 112: // p na tabela ascii
    if (r2 == 'i') {
      switch (ret)
      {
        case 1:
          strcpy(registrador, "edi");
          break;
        case 2:
          strcpy(registrador, "esi");
          break;
        case 3:
          strcpy(registrador, "edx");
          break;
        case 4:
          strcpy(registrador, "ecx");
          break;
        case 5:
          strcpy(registrador, "r8d");
          break;
        default:
          strcpy(registrador, "xxx");
          break;
      }
      fprintf(fp, "%s%s%s", "\tmovl %", registrador, ", %eax\n");
    } else if (r2 == 'a') {
      printf("retorno de param array\n");
    }
    break;
  case 118: // v na tabela ascii
    printf("retorno de variável do escopo da função: ");
    break;
  case 99: // c na tabela ascii
    printf("retorno de constante: ");
    fprintf(fp, "%s%d%s", "\tmovl $", ret, ", %eax\n");
    break;
  default:
    printf("retorno inválido\n");
    break;
  }

  fclose(fp);
}

void process_if(char line[256], int count) {
  FILE *fp;
  int comp; //int para armazenar a comparação
  int t; //variável de controle dentro da função
  int r;
  char v1, v2,
  fp = fopen("file.S", "a+");

  t = sscanf(line, "if %c%c%d", &v1, &v2, &r);

  if (v1 == 'p') {
    //condição com parâmetro
  } else if (v1 = 'v') {
    //condição com variável local
  } else if (v1 = 'c') {
    //condição com constante insteira
    
  }
}

void init_if(int value) {
  FILE *f;
  char str1 = "\tcmpl ";
  char str2 = "begin_if:";

  f = fopen("file.S", "a+");
  fprintf(f, "%s%d%s%s", str1, value, ", $0\n", "\tjne end_if");
  fprintf(f, "%s", "end_if");
}

void init_function()
{
   FILE *f;
   char str1[] = "\tpushq %rbp\n";
   char str2[] = "\tmovq %rsp, rbp\n\n";

   f = fopen("file.S", "a+");
   fprintf(f, "%s", str1);
   fprintf(f, "%s", str2);
   fclose(f);
}

void end_function()
{
   FILE *f;
   char str1[] = "\tleave\n";
   char str2[] = "\tret\n";

   f = fopen("file.S", "a+");
   fprintf(f, "%s", str1);
   fprintf(f, "%s", str2);
   fclose(f);
}
