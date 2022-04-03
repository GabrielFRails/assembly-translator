#include <stdio.h>

// Funções definidas em BPL
int f1();
int f2(int);
int f3(int*, int);

int main() {
   int vet[] = {100, 200, 300};
   int x;
   
   x = f1();
   printf("f1 = %d\n", x);

   x = f2(1);
   printf("f2 = %d\n", x);

   x = f3(vet, 1);
   printf("f3 = %d\n", x);

   return 0;
}