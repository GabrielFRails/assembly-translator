#include <stdio.h>
#include <string.h>
#include "functions.h"

int which_if = 0;

void process_function_start(char line[256], int * param_types)
{
  FILE *fp;
  int r, s, i1 = 0, i2 = 0, i3 = 0;
  char v1, v2, v3;
  sscanf(line, "function f%d p%c%d p%c%d p%c%d", &s, &v1, &i1, &v2, &i2, &v3, &i3);

  //inteiro type 1
  //array type 2
  //nulo type 0

  if(i1 != 0){
    if(v1 == 'i') param_types[0] = 1;
    else param_types[0] = 2;

    if(i2 != 0){
      if(v2 == 'i') param_types[1] = 1;
      else param_types[1] = 2;

      if(i3 != 0){
        if(v3 == 'i') param_types[2] = 1;
        else param_types[2] = 2;
      }
    }
  }

  fp = fopen("file.S", "a+");
  fprintf(fp, ".globl f%d\n", s);
  fprintf(fp, "f%d:\n", s);
  fclose(fp);
  init_function();

}

void process_return(char line[256], int * addrs)
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

  fprintf(fp, "\n\t# %s\n", line);
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
    fprintf(fp, "\tmovl %d(%%rbp), %%eax\n", addrs[ret-1]);
    break;
  case 99: // c na tabela ascii
    fprintf(fp, "%s%d%s", "\tmovl $", ret, ", %eax\n");
    break;
  default:
    printf("retorno inválido\n");
    break;
  }

  fclose(fp);
}

void process_if(char line[256], int * vl_addrs) {
  which_if++;
  int comp; //int para armazenar a comparação
  int t; //variável de controle dentro da função
  int r;
  char v1, v2;

  t = sscanf(line, "if %c%c%d", &v1, &v2, &r);
  if (v1 == 'p') {
    init_if_parametro(r);
  } else if (v1 == 'v') {
    init_if_var_local(vl_addrs, r);
  } else if (v1 == 'c') {
    init_if_constante(r);
  }
}

void init_if_parametro(int param) {
  FILE *f;

  char str1[] = "\tcmpl %";

  char registrador[4] = "";
  switch (param) //veririca qual parâmetro foi passado para podermos saber qual registrador usar na comparação
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
  f = fopen("file.S", "a+");
  fprintf(f, "\t# if no. %d\n", which_if);
  fprintf(f, "%s%s%s%s%d\n", str1, registrador, ", $0\n", "\tje end_if", which_if);
  fclose(f);
}

void init_if_constante(int value) {
  FILE *f;

  char str1[] = "\tcmpl ";

  f = fopen("file.S", "a+");
  fprintf(f, "\t# if no. %d\n", which_if);
  fprintf(f, "%s%d%s%s%d\n", str1, value, ", $0\n", "\tje end_if", which_if);
  fclose(f);
}

void init_if_var_local(int * vl_addrs, int var_index) {
  FILE *f = fopen("file.S", "a+");

  char str1[] = "\tcmpl ";

  fprintf(f, "\t# if no. %d\n", which_if);
  fprintf(f, "%s%d(%%rbp) %s%s%d\n", str1, vl_addrs[var_index-1], ", $0\n", "\tje end_if", which_if);
  
  fclose(f);
}

void process_end_if() {
  FILE *f = fopen("file.S", "a+");
  char str1[10] = "\nend_if";
  char str2[10];

  sprintf(str2, "%d:\n\n", which_if);
  strcat(str1, str2);

  fprintf(f, "%s", str1);
  fclose(f);
}

void init_function()
{
  FILE *f;
  char str1[] = "\tpushq %rbp\n";
  char str2[] = "\tmovq %rsp, %rbp\n\n";

  f = fopen("file.S", "a+");
  fprintf(f, "%s", str1);
  fprintf(f, "%s", str2);
  fclose(f);
}

void process_function_end()
{
  FILE *f;
  char str1[] = "\tleave\n";
  char str2[] = "\tret\n\n";
  f = fopen("file.S", "a+");
  fprintf(f, "%s", str1);
  fprintf(f, "%s", str2);
  fclose(f);

  which_if = 0;
}
