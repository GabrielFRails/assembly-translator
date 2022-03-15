#include <stdio.h>
#include "variables.h"

void process_local_int_variables(char line[256], int count)
{
  char variableIndex,
      vi1, vi2, vi3, vi4, vi5;
  int r;
  r = sscanf(line, "var vi%d", &variableIndex);
  if (r == 1)
  {
    printf("Linha %d: %s\n", count, line);
    if (variableIndex == 1)
      vi1 = variableIndex;
    else if (variableIndex == 2)
      vi2 = variableIndex;
    else if (variableIndex == 3)
      vi3 = variableIndex;
    else if (variableIndex == 4)
      vi4 = variableIndex;
    else if (variableIndex == 5)
      vi5 = variableIndex;
    printf("Declaração da variavel 'v%d'\n", variableIndex);
    printf("---\n");
  }
}

void process_local_variables_start(char line[256], int count)
{
  printf("Linha %d: %s\n", count, line);
  printf("Definição escopo de função: {\n");
  printf("---\n");
}

void process_local_variables_end(char line[256], int count)
{
  printf("}\nLinha %d: %s\n", count, line);
  printf("Fim da definição de escopo:\n");
  printf("---\n");
}


void declare_variable(int value)
{
}

void declare_array(int *array)
{
}