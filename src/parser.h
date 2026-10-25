#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include "tokenizer.h"

typedef enum InstructionType {
    I_HLT,
    I_PUSH,
    I_POP,
    I_PEEK,
    I_SET,
    I_ADD,
    I_SUB,
    I_MUL,
    I_DIV,
    I_JMP,
    I_JE,
    I_JNE,
    I_JA,
    I_JB
} InstructionType;

typedef enum Register {
    R_REG_A, R_REG_B, R_REG_C, R_REG_D, R_REG_E, R_REG_F
} Register;

typedef struct {
    InstructionType type;
    Register reg;
    char label[64];
    int val;
} Instruction;

size_t parse(Token*, Instruction*, char**,
             int*, size_t*);
void debug_print_instructions(Instruction*, size_t);
void debug_print_instruction(Instruction);


#endif
