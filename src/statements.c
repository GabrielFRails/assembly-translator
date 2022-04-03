#include <stdio.h>
#include "statements.h"

void process_simple_attr(char line[256], int * addrs){

    FILE * fp = fopen("file.S", "a+");
    char destType, signal = '0', param1Type, param2Type;
    int destIndex, param1Index, param2Index;

    sscanf(line, "%ci%d = %ci%d %c %ci%d", &destType, &destIndex, &param1Type, &param1Index, &signal, &param2Type, &param2Index);

    fprintf(fp, "\n\t# %s\n", line);

    if(signal == '0'){
        switch(param1Type){
            case 'v':
                fprintf(fp, "\tmovl %d(%%rbp), %%eax\n", addrs[param1Index-1]);
                fprintf(fp, "\tmovl %%eax, ");
                break;
            case 'p':
                switch(param1Index){
                    case 1:
                        fprintf(fp, "\tmovl %%edi, ");
                        break;
                    case 2:
                        fprintf(fp, "\tmovl %%esi, ");
                        break;
                    case 3:
                        fprintf(fp, "\tmovl %%edx, ");
                        break;
                }
                break;
            case 'c':
                fprintf(fp, "\tmovl $%d, ", param1Index);
                break;
        }
        fprintf(fp, "%d(%%rbp)\n", addrs[destIndex-1]);
    }
    else if(signal == '/'){
        switch(param1Type){
            case 'v':
                fprintf(fp, "\tmovl %d(%%rbp), %%eax\n", addrs[param1Index-1]);
                break;
            case 'p':
                switch(param1Index){
                case 1:
                    fprintf(fp, "\tmovl %%edi, %%eax\n");
                    break;
                case 2:
                    fprintf(fp, "\tmovl %%esi, %%eax\n");
                    break;
                case 3:
                    fprintf(fp, "\tmovl %%edx, %%eax\n");
                    break;
            }
                break;
            case 'c':
                fprintf(fp, "\tmovl $%d, %%eax\n", param1Index);
                break;
        }
        // extendendo o eax para edx
        fprintf(fp, "\tcltd\n");
        switch(param2Type){
            case 'v':
                fprintf(fp, "\tidivl %d(%%rbp)\n", addrs[param2Index-1]);
                break;
            case 'p':
                switch(param2Index){
                    case 1:
                        fprintf(fp, "\tidivl %%edi\n");
                        break;
                    case 2:
                        fprintf(fp, "\tidivl %%esi\n");
                        break;
                    case 3:
                        fprintf(fp, "\tidivl %%edx\n");
                        break;
                }
                break;
            case 'c':
                fprintf(fp, "\tmovl $%d, %%ecx\n", param2Index);
                fprintf(fp, "\tidivl %%ecx\n");
                break;
        }
        fprintf(fp, "\tmovl %%eax, %d(%%rbp)\n", addrs[destIndex-1]);
    }
    else{
        switch(param1Type){
                case 'v':
                    fprintf(fp, "\tmovl %d(%%rbp), %%eax\n", addrs[param1Index-1]);
                    break;
                case 'p':
                    switch(param1Index){
                    case 1:
                        fprintf(fp, "\tmovl %%edi, %%eax\n");
                        break;
                    case 2:
                        fprintf(fp, "\tmovl %%esi, %%eax\n");
                        break;
                    case 3:
                        fprintf(fp, "\tmovl %%edx, %%eax\n");
                        break;
                }
                    break;
                case 'c':
                    fprintf(fp, "\tmovl $%d, %%eax\n", param1Index);
                    break;
            }
        switch(signal){
            case '+':
                switch(param2Type){
                    case 'v':
                        fprintf(fp, "\taddl %d(%%rbp), %%eax", addrs[param2Index-1]);
                        break;
                    case 'p':
                        switch(param2Index){
                            case 1:
                                fprintf(fp, "\taddl %%edi, %%eax\n");
                                break;
                            case 2:
                                fprintf(fp, "\taddl %%esi, %%eax\n");
                                break;
                            case 3:
                                fprintf(fp, "\taddl %%edx, %%eax\n");
                                break;
                        }
                        break;
                    case 'c':
                        fprintf(fp, "\taddl $%d, %%eax\n", param2Index);
                        break;
                }
                break;
            case '-':
                switch(param2Type){
                    case 'v':
                        fprintf(fp, "\tsubl %d(%%rbp), %%eax\n", addrs[param2Index-1]);
                        break;
                    case 'p':
                        switch(param2Index){
                            case 1:
                                fprintf(fp, "\tsubl %%edi, %%eax\n");
                                break;
                            case 2:
                                fprintf(fp, "\tsubl %%esi, %%eax\n");
                                break;
                            case 3:
                                fprintf(fp, "\tsubl %%edx, %%eax\n");
                                break;
                        }
                        break;
                    case 'c':
                        fprintf(fp, "\tsubl $%d, %%eax\n", param2Index);
                        break;
                }
                break;
            case '*':
                switch(param2Type){
                    case 'v':
                        fprintf(fp, "\timull %d(%%rbp), %%eax\n", addrs[param2Index-1]);
                        break;
                    case 'p':
                        switch(param2Index){
                            case 1:
                                fprintf(fp, "\timull %%edi, %%eax\n");
                                break;
                            case 2:
                                fprintf(fp, "\timull %%esi, %%eax\n");
                                break;
                            case 3:
                                fprintf(fp, "\timull %%edx, %%eax\n");
                                break;
                        }
                        break;
                    case 'c':
                        fprintf(fp, "\timull $%d, %%eax\n", param2Index);
                        break;
                }
                break;
        }
        fprintf(fp, "\tmovl %%eax, %d(%%rbp)\n", addrs[destIndex-1]);
    }

    fclose(fp);
}

void process_attr_with_function_call(char line[256], int * addrsParams, int * addrVars, int * paramTypes)
{
    FILE *fp = fopen("file.S", "a+");
    char destType, param1Type, param2Type, param3Type, param1DataType, param2DataType, param3DataType;
    int t, destIndex, functionIndex, indexParam1, indexParam2, indexParam3;

    // %c%c%d => p/v/c | i/a | index ou valor da constante inteira
    t = sscanf(line, "%ci%d = call f%d %c%c%d %c%c%d %c%c%d", &destType, &destIndex, &functionIndex, &param1Type, &param1DataType, &indexParam1, &param2Type, &param2DataType, &indexParam2, &param3Type, &param3DataType, &indexParam3);
    
    if(paramTypes[0]) fprintf(fp, "\n\t# salvando parametros\n");

    for(int i = 0; paramTypes[i]; i++){
        switch(i){
            case 0:
                fprintf(fp, "\tmovq %%rdi, %d(%%rbp)\n", addrsParams[i]);
                break;
            case 1:
                fprintf(fp, "\tmovq %%rsi, %d(%%rbp)\n", addrsParams[i]);
                break;
            case 2:
                fprintf(fp, "\tmovq %%rdx, %d(%%rbp)\n", addrsParams[i]);
        }
    }

    
    fprintf(fp, "\n\t# %s\n", line);
    
    if( t >= 6)
    {
        switch(param1Type) {
            case 'v':
                switch(param1DataType){
                    case 'i':
                        fprintf(fp, "\tmovl %d(%%rbp), %%edi\n", addrVars[indexParam1-1]);
                        break;
                    case 'a':
                        fprintf(fp, "\tleaq %d(%%rbp), %%rdi\n", addrVars[indexParam1-1]);
                        break;
                }
                break;
            case 'p':
                switch(param1DataType){
                    case 'i':
                        if (indexParam1 == 2) 
                        {
                            fprintf(fp, "\tmovq %d(%%rbp), %%rax\n", addrsParams[1]);
                            fprintf(fp, "\tmovl %%eax, %%edi\n");
                        } else if (indexParam1 == 3) {
                            fprintf(fp, "\tmovq %d(%%rbp), %%rax\n", addrsParams[2]);
                            fprintf(fp, "\tmovl %%eax, %%edi\n");
                        }
                        break;
                    case 'a':
                        if (indexParam1 == 2) 
                        {
                            fprintf(fp, "\tleaq %d(%%rbp), %%rdi\n", addrsParams[1]);
                        } else if (indexParam1 == 3) {
                            fprintf(fp, "\tleaq %d(%%rbp), %%rdi\n", addrsParams[2]);
                        }
                        break;
                }
                break;
            case 'c':
                fprintf(fp, "\tmovl $%d, %%edi\n", indexParam1);
                break;
        }   
    }   
    if (t >= 9) 
    {
        switch(param2Type) {
            case 'v':
                switch(param2DataType){
                    case 'i':
                        fprintf(fp, "\tmovl %d(%%rbp), %%esi\n", addrVars[indexParam2-1]);
                        break;
                    case 'a':
                        fprintf(fp, "\tleaq %d(%%rbp), %%rsi\n", addrVars[indexParam2-1]);
                        break;
                }
                break;
            case 'p':
                switch(param2DataType){
                    case 'i':
                        if (indexParam2 == 1) 
                        {
                            fprintf(fp, "\tmovq %d(%%rbp), %%rax\n", addrsParams[0]);
                            fprintf(fp, "\tmovl %%eax, %%esi\n");
                        } else if (indexParam2 == 3) {
                            fprintf(fp, "\tmovq %d(%%rbp), %%rax\n", addrsParams[2]);
                            fprintf(fp, "\tmovl %%eax, %%esi\n");
                        }
                        break;
                    case 'a':
                        if (indexParam2 == 1) 
                        {
                            fprintf(fp, "\tleaq %d(%%rbp), %%rsi\n", addrsParams[0]);
                        } else if (indexParam2 == 3) {
                            fprintf(fp, "\tleaq %d(%%rbp), %%rsi\n", addrsParams[2]);
                        }
                        break;
                }
                break;
            case 'c':
                fprintf(fp, "\tmovl $%d, %%edi\n", indexParam1);
                break;
        }
    }
    
    if (t == 12) 
    {
        switch(param3Type) {
            case 'v':
                switch(param3DataType){
                    case 'i':
                        fprintf(fp, "\tmovl %d(%%rbp), %%edx\n", addrVars[indexParam2-1]);
                        break;
                    case 'a':
                        fprintf(fp, "\tleaq %d(%%rbp), %%edx\n", addrVars[indexParam2-1]);
                        break;
                }
                break;
            case 'p':
                switch(param3DataType){
                    case 'i':
                        if (indexParam3 == 1) 
                        {
                            fprintf(fp, "\tmovq %d(%%rbp), %%rax\n", addrsParams[0]);
                            fprintf(fp, "\tmovl %%eax, %%edx\n");
                        } else if (indexParam3 == 2) {
                            fprintf(fp, "\tmovq %d(%%rbp), %%rax\n", addrsParams[1]);
                            fprintf(fp, "\tmovl %%eax, %%edx\n");
                        }
                        break;
                    case 'a':
                        if (indexParam3 == 1) 
                        {
                            fprintf(fp, "\tleaq %d(%%rbp), %%edx\n", addrsParams[0]);
                        } else if (indexParam3 == 2) {
                            fprintf(fp, "\tleaq %d(%%rbp), %%edx\n", addrsParams[1]);
                        }
                        break;
                }
                break;
            case 'c':
                fprintf(fp, "\tmovl $%d, %%edi\n", indexParam1);
                break;
        }
    }

    fprintf(fp, "\tcall f%d\n", functionIndex);
    // movendo o resultado da função para o destino especificado
    fprintf(fp, "\tmovl %%eax, %d(%%rbp)\n", addrVars[destIndex-1]);

    if(paramTypes[0]) fprintf(fp, "\n\t# recuperando parametros\n");
    
    for(int i = 0; paramTypes[i]; i++){
        switch(i){
            case 0:
                fprintf(fp, "\tmovq %d(%%rbp), %%rdi\n", addrsParams[i]);
                break;
            case 1:
                fprintf(fp, "\tmovq %d(%%rbp), %%rsi\n", addrsParams[i]);
                break;
            case 2:
                fprintf(fp, "\tmovq %d(%%rbp), %%rdx\n", addrsParams[i]);
        }
    }

    fclose(fp);
}