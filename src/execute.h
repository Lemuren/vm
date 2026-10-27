#ifndef EXECUTE_H
#define EXECUTE_H

#include <stdbool.h>
#include "parser.h"

typedef struct {
    bool running;
    int stack[1024];
    size_t stackSize;
    size_t reg_ip;
    int reg_a;
    int reg_b;
    int reg_c;
    int reg_d;
    int reg_e;
    int reg_f;
} State;

void run(Instruction*, char**, size_t*, size_t, State*, char**);

#endif
