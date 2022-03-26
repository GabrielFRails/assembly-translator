#include <stdio.h>
#include "arrays.h"

void process_array_variables(char line[256], int count)
{
  int vetSize, variableIndex, r, va1, va2, va3, va4, va5;
  r = sscanf(line, "vet %d size ci%d", &variableIndex, &vetSize);

  if (r == 2)
  {
    printf("Linha %d: %s\n", count, line);
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

void process_get_array_element(char line[256], int count)
{
  char arraySource[3], arrayDestiny[3];
  int arraySourceIndex, arrayDestinyIndex, arrayElementIndex, r;
  r = sscanf(line, "get %2s%d index ci%d to %2s%d", &arraySource, &arraySourceIndex, &arrayElementIndex, &arrayDestiny, &arrayDestinyIndex);

  if (r == 5)
  {
    printf("Pegar valor de vetor\nDe:%s%d\nPosição:%d\nDestino:%s%d\n\n", arraySource, arraySourceIndex, arrayElementIndex, arrayDestiny, arrayDestinyIndex);
  }
}

void process_set_array_element(char line[256], int count)
{
  char arraySource[3], arrayDestiny[3];
  int arraySourceIndex, arrayDestinyIndex, arrayElementIndex, r;
  r = sscanf(line, "set %2s%d index ci%d with %2s%d", &arraySource, &arraySourceIndex, &arrayElementIndex, &arrayDestiny, &arrayDestinyIndex);

  if (r == 5)
  {
    printf("Setar valor em um vetor\nEm:%s%d\nPosição:%d\nValor:%s%d\n\n", arraySource, arraySourceIndex, arrayElementIndex, arrayDestiny, arrayDestinyIndex);
  }
}