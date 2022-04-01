#ifndef __STATEMENTS__
#define __STATEMENTS__

void process_simple_attr(char line[256], int * addrs);

void process_attr_with_function_call(char line[256], int * addrsParams, int * addrVars, int * paramTypes);

#endif