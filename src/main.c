#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESZ 256

FILE *fp;
void remove_newline(char *ptr);
void initial_print();
void final_print();
void end_function();
void init_function();

int main()
{

   // variáveis para array{
   char arraySource[3], arrayDestiny[3];
   int arraySourceIndex, arrayDestinyIndex, arrayElementIndex;
   //}

   // variáveis para declaração de variavel {
   char vIndex,
       vi1, vi2, vi3, vi4, vi5;
   int vetSize, va1, va2, va3, va4, va5;
   //}
   // variáveis para função {
   char v1,
       v2, v3;
   int r, s, i1, i2, i3;
   char line[LINESZ];
   int count = 0;
   //}

   // variáveis para o retorno da função {
   char r1, r2; // para pegar o tipo de retorno e o tipo de valor do retorno
   int t, ret;  // para armazenar o valor do sscanf e o valor inteiro do retorno
                //}

   initial_print();

   // variáveis para o corpo da função {
   //}
   // lê uma linha de cada vez
   while (fgets(line, LINESZ, stdin) != NULL)
   {
      count++;
      remove_newline(line);

      // verifica se a linha começa com 'def'
      if (strncmp(line, "def", 3) == 0)
      {
         printf("Linha %d: %s\n", count, line);
         printf("Definição escopo de função: {\n");
         printf("---\n");
         continue;
      }

      // Verifica se a linha lida começa com var
      if (strncmp(line, "var", 3) == 0)
      {
         r = sscanf(line, "var vi%d", &vIndex);
         if (r == 1)
         {
            printf("Linha %d: %s\n", count, line);
            if (vIndex == 1)
               vi1 = vIndex;
            else if (vIndex == 2)
               vi2 = vIndex;
            else if (vIndex == 3)
               vi3 = vIndex;
            else if (vIndex == 4)
               vi4 = vIndex;
            else if (vIndex == 5)
               vi5 = vIndex;
            printf("Declaração da variavel 'v%d'\n", vIndex);
            printf("---\n");
         }
         continue;
      }
      // Verifica se a linha lida começa com vet
      if (strncmp(line, "vet", 3) == 0)
      {

         r = sscanf(line, "vet %d size ci%d", &vIndex, &vetSize);

         if (r == 2)
         {
            printf("Linha %d: %s\n", count, line);
            if (vIndex == 1)
               va1 = vIndex;
            else if (vIndex == 2)
               va2 = vIndex;
            else if (vIndex == 3)
               va3 = vIndex;
            else if (vIndex == 4)
               va4 = vIndex;
            else if (vIndex == 5)
               va5 = vIndex;
            // Confimar com o professor se vai ter entrada negativa, se tiver, acho que seria plausivel ignorar a declaração.
            if (vetSize > 0)
               printf("Declaração de vetor 'v%d' tamanho '%d'\n", vIndex, vetSize);
            printf("---\n");
         }
         continue;
      }
      // verifica se a linha começa com get
      if (strncmp(line, "get", 3) == 0)
      {
         r = sscanf(line, "get %2s%d index ci%d to %2s%d", &arraySource, &arraySourceIndex, &arrayElementIndex, &arrayDestiny, &arrayDestinyIndex);

         if (r == 5)
         {
            printf("Pegar valor de vetor\nDe:%s%d\nPosição:%d\nDestino:%s%d\n\n", arraySource, arraySourceIndex, arrayElementIndex, arrayDestiny, arrayDestinyIndex);
         }
         continue;
      }
      if (strncmp(line, "set", 3) == 0)
      {
         r = sscanf(line, "set %2s%d index ci%d with %2s%d", &arraySource, &arraySourceIndex, &arrayElementIndex, &arrayDestiny, &arrayDestinyIndex);

         if (r == 5)
         {
            printf("Setar valor em um vetor\nEm:%s%d\nPosição:%d\nValor:%s%d\n\n", arraySource, arraySourceIndex, arrayElementIndex, arrayDestiny, arrayDestinyIndex);
         }
         continue;
      }

      // verifica se a linha começa com 'enddef'
      if (strncmp(line, "enddef", 6) == 0)
      {
         printf("}\nLinha %d: %s\n", count, line);
         printf("Fim da definição de escopo:\n");
         printf("---\n");
         continue;
      }

      // verifica se a linha começa com 'return'
      if (strncmp(line, "return", 6) == 0)
      {
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

      // Verifica se line começa com 'end' (3 letras)
      if (strncmp(line, "end", 3) == 0)
      {
         printf("Linha %d: %s\n", count, line);
         printf("Fim da função\n");
         printf("---\n");
         end_function();
         continue;
      }

      // verifica se a linha começa com 'function'
      if (strncmp(line, "function", 8) == 0)
      {
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
         continue;
      }
   }
   final_print();
   return 0;
}