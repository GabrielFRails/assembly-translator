#include <stdio.h>
#include "arrays.h"

void process_array_variables(char line[256])
{
  int vetSize, variableIndex, r, va1, va2, va3, va4, va5;
  r = sscanf(line, "vet %d size ci%d", &variableIndex, &vetSize);

  if (r == 2)
  {
    if (variableIndex == 1)
      va1 = variableIndex;
    else if (variableIndex == 2)
      va2 = variableIndex;
    else if (variableIndex == 3)
      va3 = variableIndex;
    else if (variableIndex == 4)
      va4 = variableIndex;
    else if (variableIndex == 5)
      va5 = variableIndex;
    // Confimar com o professor se vai ter entrada negativa, se tiver, acho que seria plausivel ignorar a declaração.
    if (vetSize > 0)
      printf("Declaração de vetor 'v%d' tamanho '%d'\n", variableIndex, vetSize);
    printf("---\n");
  }
}

void process_get_array_element(char line[256], int * addrs)
{
  FILE * fp = fopen("file.S", "a+");
  char sourceType, destType;
  int sourceIndex, position, destIndex;

  sscanf(line, "get %ca%d index ci%d to %ci%d", &sourceType, &sourceIndex, &position, &destType, &destIndex);

  fprintf(fp, "\n\t# %s\n", line);
  switch(sourceType){
    case 'p':
      switch(sourceIndex){
        case 1:
          fprintf(fp, "\tmovq %%rdi, %%rax\n");
          break;
        case 2:
          fprintf(fp, "\tmovq %%rsi, %%rax\n");
          break;
        case 3:
          fprintf(fp, "\tmovq %%rdx, %%rax\n");
          break;
      }
      fprintf(fp, "\taddq $%d, %%rax\n", 4*position);
      fprintf(fp, "\tmovl (%%rax), %%eax\n");
      break;
    case 'v':
      fprintf(fp, "\tleaq %d(%%rbp), %%rax\n", addrs[sourceIndex - 1] + 4 * position);
      fprintf(fp, "\tmovl (%%rax), %%eax\n");
      break;
  }

  switch(destType){
    case 'v':
      fprintf(fp, "\tmovl %%eax, %d(%%rbp)\n", addrs[destIndex-1]);
      break;
    case 'p':
      switch(destIndex){
        case 1:
          fprintf(fp, "\tmovl %%eax, %%edi\n");
          break;
        case 2:
          fprintf(fp, "\tmovl %%eax, %%esi\n");
          break;
        case 3:
          fprintf(fp, "\tmovl %%eax, %%edx\n");
          break;
      }
  }

  fclose(fp);
}

void process_set_array_element(char line[256], int * addrs)
{
  FILE * fp = fopen("file.S", "a+");
  char sourceType, destType;
  int sourceIndex, position, destIndex;

  sscanf(line, "set %ca%d index ci%d with %ci%d", &destType, &destIndex, &position, &sourceType, &sourceIndex);

  fprintf(fp, "\n\t# %s\n", line);

  switch(destType){
    case 'p':
      switch(destIndex){
        case 1:
          fprintf(fp, "\tmovq %%rdi, %%rax\n");
          break;
        case 2:
          fprintf(fp, "\tmovq %%rsi, %%rax\n");
          break;
        case 3:
          fprintf(fp, "\tmovq %%rdx, %%rax\n");
          break;
      }
      fprintf(fp, "\taddq $%d, %%rax\n", position*4);
      break;
    case 'v':
      break;
  }

  switch(sourceType){
    case 'p':
      switch(sourceIndex){
        case 1:
          fprintf(fp, "\tmovl %%edi, ");
          break;
        case 2:
          fprintf(fp, "\tmovl %%esi, ");
          break;
        case 3:
          fprintf(fp, "\tmovl %%edx, ");
          break;
      }
      break;
    case 'v':
      fprintf(fp, "\tmovl %d(%%rbp), %%ecx\n", addrs[sourceIndex - 1]);
      fprintf(fp, "\tmovl %%ecx, ");
      break;
    case 'c':
      fprintf(fp, "\tmovl $%d, ", sourceIndex);
  }

  switch(destType){
    case 'p':
      fprintf(fp, "(%%eax)\n");
      break;
    case 'v':
      fprintf(fp, "%d(%%rbp)\n", addrs[destIndex - 1] + 4 * position);
      break;
  }

  fclose(fp);
}