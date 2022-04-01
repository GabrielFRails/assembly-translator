#ifndef __GENERAL__
#define __GENERAL__

/**
 * @brief função que remove o caractere de quebra de linha
 *        '\n' de uma linha
 * 
 * @param ptr ponteiro para a string correspondente à linha
 */
void remove_newline(char *ptr);

/**
 * @brief imprime os elementos base do programa Assembly
 * 
 */
void initial_print();

void allocate_pile(int * size_pile, int * param_types, int * param_addrs);

#endif