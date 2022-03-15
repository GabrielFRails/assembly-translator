#ifndef __VARIABLES__
#define __VARIABLES__

/**
 * @brief processa as declarações de variáveis locais em funções
 * 
 * @param line linha a ser processada
 * @param count número da linha
 */
void process_local_int_variables(char line[256], int count);

/**
 * @brief processa o início da área de declaração de
 *        variáveis locais em uma função
 * 
 * @param line 
 * @param count 
 */
void process_local_variables_start(char line[256], int count);

/**
 * @brief processa o fim da área de declaração de
 *        variáveis locais em uma função
 * 
 * @param line 
 * @param count 
 */
void process_local_variables_end(char line[256], int count);


#endif