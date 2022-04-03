#include <stdio.h>

// Função definidas em BPL
int f1();

// Função chamada por BPL
int f100(int v) {
   printf("Valor vindo de BPL: %d\n", v);
   return 2048;
}

int main() {
   f1();
   return 0;
}