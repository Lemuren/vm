#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "execute.h"


void run(Instruction *program, char **labels,
         size_t *labels_lookup, size_t labels_len, State *s,
         char **outputBuffer) {
    // Read instruction and increment the instruction pointer.
    Instruction instruction = program[s->reg_ip++];

    // HLT instruction.
    if (instruction.type == I_HLT) {
        s->running = false;
        return;
    }

    // PUSH instruction.
    if (instruction.type == I_PUSH) {
        switch (instruction.reg) {
            case R_REG_A:
                s->stack[s->stackSize++] = s->reg_a;
                break;
            case R_REG_B:
                s->stack[s->stackSize++] = s->reg_b;
                break;
            case R_REG_C:
                s->stack[s->stackSize++] = s->reg_c;
                break;
            case R_REG_D:
                s->stack[s->stackSize++] = s->reg_d;
                break;
            case R_REG_E:
                s->stack[s->stackSize++] = s->reg_e;
                break;
            case R_REG_F:
                s->stack[s->stackSize++] = s->reg_f;
                break;
            case R_NONE:
                s->stack[s->stackSize++] = instruction.val;
                break;
        }
        return;
    }

    // POP instruction.
    if (instruction.type == I_POP) {
        if (s->stackSize == 0) {
            fprintf(stderr, "Tried to POP empty stack!\n");
            exit(1);
        }

        switch (instruction.reg) {
            case R_REG_A:
                s->reg_a = s->stack[--(s->stackSize)];
                break;
            case R_REG_B:
                s->reg_b = s->stack[--(s->stackSize)];
                break;
            case R_REG_C:
                s->reg_c = s->stack[--(s->stackSize)];
                break;
            case R_REG_D:
                s->reg_d = s->stack[--(s->stackSize)];
                break;
            case R_REG_E:
                s->reg_e = s->stack[--(s->stackSize)];
                break;
            case R_REG_F:
                s->reg_f = s->stack[--(s->stackSize)];
                break;
            case R_NONE:
                if (outputBuffer) {
                    int len = 0;
                    sprintf(*outputBuffer, "%d\n%n", s->stack[--(s->stackSize)], &len);
                    *outputBuffer += len;
                } else {
                    printf("%d\n", s->stack[--(s->stackSize)]);
                }
                break;
        }
        return;
    }

    // PEEK instruction.
    if (instruction.type == I_PEEK) {
        if (s->stackSize == 0) {
            fprintf(stderr, "PEEKed at empty stack\n");
            exit(1);
        }
        switch (instruction.reg) {
            case R_REG_A:
                s->reg_a = s->stack[s->stackSize-1];
                break;
            case R_REG_B:
                s->reg_b = s->stack[s->stackSize-1];
                break;
            case R_REG_C:
                s->reg_c = s->stack[s->stackSize-1];
                break;
            case R_REG_D:
                s->reg_d = s->stack[s->stackSize-1];
                break;
            case R_REG_E:
                s->reg_e = s->stack[s->stackSize-1];
                break;
            case R_REG_F:
                s->reg_f = s->stack[s->stackSize-1];
                break;
            case R_NONE:
                // We should never be able to get here.
                break;
        }
        return;
    }

    // SET instruction.
    if (instruction.type == I_SET) {
        switch (instruction.reg) {
            case R_REG_A:
                s->reg_a = instruction.val;
                break;
            case R_REG_B:
                s->reg_b = instruction.val;
                break;
            case R_REG_C:
                s->reg_c = instruction.val;
                break;
            case R_REG_D:
                s->reg_d = instruction.val;
                break;
            case R_REG_E:
                s->reg_e = instruction.val;
                break;
            case R_REG_F:
                s->reg_f = instruction.val;
                break;
            case R_NONE:
                // We should never be able to get here.
                break;
        }
        return;
    }

    // ADD instruction.
    if (instruction.type == I_ADD) {
        if (s->stackSize < 2) {
            fprintf(stderr, "attempted to add with stack size < 2\n");
            exit(1);
        }
        int a = s->stack[--(s->stackSize)];
        int b = s->stack[--(s->stackSize)];
        s->stack[s->stackSize++] = a + b;
        return;
    }

    // SUB instruction.
    if (instruction.type == I_SUB) {
        if (s->stackSize < 2) {
            fprintf(stderr, "attempted to subtract with stack size < 2\n");
            exit(1);
        }
        int a = s->stack[--(s->stackSize)];
        int b = s->stack[--(s->stackSize)];
        s->stack[s->stackSize++] = a - b;
        return;
    }

    // MUL instruction.
    if (instruction.type == I_MUL) {
        if (s->stackSize < 2) {
            fprintf(stderr, "attempted to multiply with stack size < 2\n");
            exit(1);
        }
        int a = s->stack[--(s->stackSize)];
        int b = s->stack[--(s->stackSize)];
        s->stack[s->stackSize++] = a * b;
        return;
    }

    // DIV instruction.
    if (instruction.type == I_DIV) {
        if (s->stackSize < 2) {
            fprintf(stderr, "attempted to divide with stack size < 2\n");
            exit(1);
        }
        int a = s->stack[--(s->stackSize)];
        int b = s->stack[--(s->stackSize)];
        s->stack[s->stackSize++] = a / b;
        return;
    }

    // MOD instruction.
    if (instruction.type == I_MOD) {
        if (s->stackSize < 2) {
            fprintf(stderr, "attempted to modulo with stack size < 2\n");
            exit(1);
        }
        int a = s->stack[--(s->stackSize)];
        int b = s->stack[--(s->stackSize)];
        s->stack[s->stackSize++] = a % b;
        return;
    }

    // JMP instruction.
    if (instruction.type == I_JMP) {
        for (size_t i = 0; i < labels_len; i++) {
            if (strcmp(instruction.label, labels[i]) == 0) {
                s->reg_ip = labels_lookup[i];
                return;
            }
        }

        fprintf(stderr, "Unknown label!\n");
        exit(1);
        return;
    }

    // JE instruction.
    if (instruction.type == I_JE) {
        if (s->stackSize < 2) {
            fprintf(stderr, "Doing JE with stack < 2\n");
            exit(1);
        }
        for (size_t i = 0; i < labels_len; i++) {
            if (strcmp(instruction.label, labels[i]) == 0) {
                if (s->stack[s->stackSize-1] == s->stack[s->stackSize-2]) {
                    s->reg_ip = labels_lookup[i];
                }
                return;
            }
        }

        printf("Unknown label!\n");
        exit(1);
        return;
    }

    // JNE instruction.
    if (instruction.type == I_JNE) {
        if (s->stackSize < 2) {
            fprintf(stderr, "Doing JNE with stack < 2\n");
            exit(1);
        }
        for (size_t i = 0; i < labels_len; i++) {
            if (strcmp(instruction.label, labels[i]) == 0) {
                if (s->stack[s->stackSize-1] != s->stack[s->stackSize-2]) {
                    s->reg_ip = labels_lookup[i];
                }
                return;
            }
        }

        printf("Unknown label!\n");
        exit(1);
        return;
    }

    // JA instruction.
    if (instruction.type == I_JA) {
        if (s->stackSize < 2) {
            fprintf(stderr, "Doing JA with stack < 2\n");
            exit(1);
        }
        for (size_t i = 0; i < labels_len; i++) {
            if (strcmp(instruction.label, labels[i]) == 0) {
                if (s->stack[s->stackSize-1] > s->stack[s->stackSize-2]) {
                    s->reg_ip = labels_lookup[i];
                }
                return;
            }
        }

        printf("Unknown label!\n");
        exit(1);
        return;
    }

    // JB instruction.
    if (instruction.type == I_JB) {
        if (s->stackSize < 2) {
            fprintf(stderr, "Doing JB with stack < 2\n");
            exit(1);
        }
        for (size_t i = 0; i < labels_len; i++) {
            if (strcmp(instruction.label, labels[i]) == 0) {
                if (s->stack[s->stackSize-1] < s->stack[s->stackSize-2]) {
                    s->reg_ip = labels_lookup[i];
                }
                return;
            }
        }

        printf("Unknown label!\n");
        exit(1);
        return;
    }

    // PRINT instruction.
    if (instruction.type == I_PRINT) {
        if (s->stackSize == 0) {
            fprintf(stderr, "Tried to PRINT empty stack!\n");
            exit(1);
        }

        for (char c = s->stack[s->stackSize-1]; (c = s->stack[s->stackSize-1]) != 0; s->stackSize--) {
            if (s->stackSize == 0) {
                fprintf(stderr, "Tried to PRINT empty stack!\n");
                exit(1);
            }
            if (outputBuffer) {
                sprintf((*outputBuffer)++, "%c", c);
            } else {
                printf("%c", c);
            }
        }

        // Consume dangling zero.
        s->stackSize--;
        return;
    }

    if (instruction.type == I_SCAN) {
        char buffer[128] = { 0 };
        fgets(buffer, sizeof buffer, stdin);

        // Attempt to interpret it as a number.
        if ((atoi(buffer) != 0) || (strcmp(buffer, "0") == 0)) {
            s->stack[s->stackSize++] = atoi(buffer);
        // Otherwise, we store it as a string.
        } else {
            int len = strlen(buffer);
            s->stack[s->stackSize++] = '\0';
            for (int i = len - 1; i >= 0; i--) {
                s->stack[s->stackSize++] = buffer[i];
            }
        }

        return;
    }
}
