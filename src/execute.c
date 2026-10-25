#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "execute.h"


void run(Instruction *program, size_t instructions_len, char **labels, int *labels_lookup, size_t labels_len) {
    int stack[1024];
    size_t stackSize = 0;

    size_t reg_ip = 0;
    int reg_a  = 0;
    int reg_b  = 0;
    int reg_c  = 0;
    int reg_d  = 0;
    int reg_e  = 0;
    int reg_f  = 0;

    int a, b;

    // Read, execute, loop.
    for (reg_ip = 0; reg_ip < instructions_len; reg_ip++) {
        size_t index;
        Instruction instruction = program[reg_ip];
        //printf("Running instruction: ");
        //debug_print_instruction(instruction);

        // printf("Stack: [ ");
        // for (size_t i = 0; i < stackSize; i++) {
        //     printf("%d ", stack[i]);
        // }
        // printf("]\n");

        switch (instruction.type) {
            case I_HLT:
                exit(0);
                break;
            case I_PUSH:
                switch (instruction.reg) {
                    case R_REG_A:
                        stack[stackSize++] = reg_a;
                        break;
                    case R_REG_B:
                        stack[stackSize++] = reg_b;
                        break;
                    case R_REG_C:
                        stack[stackSize++] = reg_c;
                        break;
                    case R_REG_D:
                        stack[stackSize++] = reg_d;
                        break;
                    case R_REG_E:
                        stack[stackSize++] = reg_e;
                        break;
                    case R_REG_F:
                        stack[stackSize++] = reg_f;
                        break;
                    case R_NONE:
                        stack[stackSize++] = instruction.val;
                        break;
                }
                break;
            case I_POP:
                if (stackSize == 0) {
                    fprintf(stderr, "Tried to POP empty stack!\n");
                    exit(1);
                }
                a = stack[--stackSize];
                if (instruction.reg == R_NONE) {
                    printf("%d\n", a);
                }

                switch (instruction.reg) {
                    case R_REG_A:
                        reg_a = a;
                        break;
                    case R_REG_B:
                        reg_b = a;
                        break;
                    case R_REG_C:
                        reg_c = a;
                        break;
                    case R_REG_D:
                        reg_d = a;
                        break;
                    case R_REG_E:
                        reg_e = a;
                        break;
                    case R_REG_F:
                        reg_f = a;
                        break;
                    case R_NONE:
                        break;
                }
                break;
            case I_SET:
                switch (instruction.reg) {
                    case R_REG_A:
                        reg_a = instruction.val;
                        break;
                    case R_REG_B:
                        reg_b = instruction.val;
                        break;
                    case R_REG_C:
                        reg_c = instruction.val;
                        break;
                    case R_REG_D:
                        reg_d = instruction.val;
                        break;
                    case R_REG_E:
                        reg_e = instruction.val;
                        break;
                    case R_REG_F:
                        reg_f = instruction.val;
                        break;
                    case R_NONE:
                        break;
                }
                break;
            case I_ADD:
                if (stackSize < 2) {
                    fprintf(stderr, "attempted to add with stack size < 2\n");
                    exit(1);
                }
                a = stack[--stackSize];
                b = stack[--stackSize];
                stack[stackSize++] = a + b;
                break;
            case I_SUB:
                if (stackSize < 2) {
                    fprintf(stderr, "attempted to subtract with stack size < 2\n");
                    exit(1);
                }
                a = stack[--stackSize];
                b = stack[--stackSize];
                stack[stackSize++] = a - b;
                break;
            case I_MUL:
                if (stackSize < 2) {
                    fprintf(stderr, "attempted to multiply with stack size < 2\n");
                    exit(1);
                }
                a = stack[--stackSize];
                b = stack[--stackSize];
                stack[stackSize++] = a * b;
                break;
            case I_DIV:
                if (stackSize < 2) {
                    fprintf(stderr, "attempted to divide with stack size < 2\n");
                    exit(1);
                }
                a = stack[--stackSize];
                b = stack[--stackSize];
                stack[stackSize++] = a / b;
                break;
            case I_MOD:
                if (stackSize < 2) {
                    fprintf(stderr, "attempted to modulo with stack size < 2\n");
                    exit(1);
                }
                a = stack[--stackSize];
                b = stack[--stackSize];
                //printf("a: %d\tb: %d\ta mod b: %d\n", a, b, a % b);
                stack[stackSize++] = a % b;
                break;
            case I_JMP:
                for (index = 0; index < labels_len; index++) {
                    if (strcmp(instruction.label, labels[index]) == 0) {
                        reg_ip = labels_lookup[index] - 1;
                        break;
                    }
                }
                if (index == labels_len) {
                    printf("Unknown label!\n");
                    exit(1);
                }
                break;
            case I_JE:
                for (index = 0; index < labels_len; index++) {
                    if (strcmp(instruction.label, labels[index]) == 0) {
                        if (stack[0] == stack[1]) {
                            reg_ip = labels_lookup[index] - 1;
                        }
                        break;
                    }
                }
                if (index == labels_len) {
                    printf("Unknown label!\n");
                    exit(1);
                }
                break;
            case I_JNE:
                for (index = 0; index < labels_len; index++) {
                    if (strcmp(instruction.label, labels[index]) == 0) {
                        if (stack[0] != stack[1]) {
                            reg_ip = labels_lookup[index] - 1;
                        }
                        break;
                    }
                }
                if (index == labels_len) {
                    printf("Unknown label!\n");
                    exit(1);
                }
                break;
            case I_JA:
                for (index = 0; index < labels_len; index++) {
                    if (strcmp(instruction.label, labels[index]) == 0) {
                        if (stack[stackSize-1] > stack[stackSize-2]) {
                            reg_ip = labels_lookup[index] - 1;
                        }
                        break;
                    }
                }
                if (index == labels_len) {
                    printf("Unknown label!\n");
                    exit(1);
                }
                break;
            case I_JB:
                for (index = 0; index < labels_len; index++) {
                    if (strcmp(instruction.label, labels[index]) == 0) {
                        if (stack[stackSize-1] < stack[stackSize-2]) {
                            reg_ip = labels_lookup[index] - 1;
                        }
                        break;
                    }
                }
                if (index == labels_len) {
                    printf("Unknown label!\n");
                    exit(1);
                }
                break;
            case I_PRINT:
                if (stackSize == 0) {
                    fprintf(stderr, "Tried to PRINT empty stack!\n");
                    exit(1);
                }

                for (char c = stack[stackSize-1]; (c = stack[stackSize-1]) != 0; stackSize--) {
                    if (stackSize == 0) {
                        fprintf(stderr, "Tried to PRINT empty stack!\n");
                        exit(1);
                    }
                    printf("%c", c);
                }

                // Consume dangling zero.
                stackSize--;

                break;
            case I_PEEK:
                if (stackSize == 0) {
                    fprintf(stderr, "PEEKed at empty stack\n");
                    exit(1);
                }
                switch (instruction.reg) {
                    case R_REG_A:
                        reg_a = stack[stackSize-1];
                        break;
                    case R_REG_B:
                        reg_b = stack[stackSize-1];
                        break;
                    case R_REG_C:
                        reg_c = stack[stackSize-1];
                        break;
                    case R_REG_D:
                        reg_d = stack[stackSize-1];
                        break;
                    case R_REG_E:
                        reg_e = stack[stackSize-1];
                        break;
                    case R_REG_F:
                        reg_f = stack[stackSize-1];
                        break;
                    case R_NONE:
                        break;
                }
                break;
        }
    }
}
