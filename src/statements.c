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
        //divisão
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

void process_attr_with_function_call(char line[256], int * addrs);