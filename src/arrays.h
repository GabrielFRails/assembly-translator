#ifndef __ARRAYS__
#define __ARRAYS__

/**
 * @brief Processa declarações de arrays locais 
 * 
 * @param line 
 * @param count 
 */
void process_array_variables(char line[256]);

/**
 * @brief Processa a leitura de um elemento do array
 * 
 * @param line 
 * @param count 
 */
void process_get_array_element(char line[256], int * addrs);

/**
 * @brief Atribui um valor a um elemento de um array
 * 
 * @param line 
 * @param count 
 */
void process_set_array_element(char line[256], int * addrs);

#endif