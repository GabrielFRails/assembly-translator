#ifndef __FUNCTIONS__
#define __FUNCTIONS__

/**
 * @brief processa a declaração de início de uma função
 * 
 * @param line 
 * @param count 
 */
void process_function_start(char line[256], int count);

/**
 * @brief processa a declaração de fim de uma função
 * 
 * @param line 
 * @param count 
 */
void process_function_end(char line[256], int count);

/**
 * @brief processa o valor de retorno de uma função
 * 
 * @param line 
 * @param count 
 */
void process_return(char line[256], int count);

/**
 * @brief realiza o registro de ativação de uma função
 * 
 */
void init_function();

/**
 * @brief remove o registro de ativação de uma função
 *        e retoma o controle para a função chamadora
 * 
 */
void end_function();

/**
 * @brief comelça o processamento para a trudução do if
 * 
 */
void process_if(char line[256], int count);

/**
 * @brief inicia o print do if
 * 
 */
void init_if(int value);

/**
 * @brief processa o fim de um if
 * 
 */
void process_end_if();

#endif