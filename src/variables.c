#include <stdio.h>
#include <string.h>
#include "variables.h"

void process_local_int_variables(char line[256], int * size_pile, int * addrs)
{
  char type[4], letter;
  int index, size_vet, aux;

  FILE * fp = fopen("file.S", "a+");
  sscanf(line, "%s v%c%d size ci%d", type, &letter, &index, &size_vet);
  
  if(strcmp(type, "var") == 0){
    (*size_pile) += 4;
    fprintf(fp, "\t# vi%d -> %d(%%rbp)\n", index, -(*size_pile));
  }
  else if(strcmp(type, "vet") == 0){
    (*size_pile) += 4 * size_vet;
    aux = -(*size_pile);
    for(int i = 0; i < size_vet; i++, aux += 4){
      fprintf(fp, "\t# va%d[%d] -> %d(%%rbp)\n", index, i, aux);
    }
  }
  addrs[index-1] = -(*size_pile);

  fclose(fp);
}


void declare_variable(int value)
{
}

void declare_array(int *array)
{
}