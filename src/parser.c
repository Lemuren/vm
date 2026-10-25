#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

// Peek at the next token without consuming it.
static Token peek(Token *tokens) {
    return tokens[0];

}

// Consume and return next token.
static Token next(Token **tokens) {
    Token t = peek(*tokens);
    (*tokens)++;
    return t;
}

// Like next() but throws an error if the token isn't of the expected type.
// static Instruction expect(Token *tokens, TokenType type) {
//     Instruction 
//     (void)type;
//     return tokens[0];
// 
// }

static bool isRegister(Token t) {
    return ((t.type == REG_A) ||
            (t.type == REG_B) ||
            (t.type == REG_C) ||
            (t.type == REG_D) ||
            (t.type == REG_E) ||
            (t.type == REG_F));
}

static Instruction parse_halt(Token **tokens) {
    Instruction instruction;
    instruction.type = I_HLT;
    next(tokens);
    return instruction;
}

static Instruction parse_push(Token **tokens) {
    Instruction instruction;
    instruction.type = I_PUSH;
    next(tokens);

    Token nextToken = next(tokens);
    if (nextToken.type != NUMBER && !isRegister(nextToken)) {
        printf("Expected immediate value or register to PUSH\n");
        exit(1);
    }

    if (nextToken.type == NUMBER) {
        instruction.val = atoi(nextToken.text);
        instruction.reg = R_NONE;
    } else if (nextToken.type == REG_A) {
        instruction.reg = R_REG_A;
    } else if (nextToken.type == REG_B) {
        instruction.reg = R_REG_B;
    } else if (nextToken.type == REG_C) {
        instruction.reg = R_REG_C;
    } else if (nextToken.type == REG_D) {
        instruction.reg = R_REG_D;
    } else if (nextToken.type == REG_E) {
        instruction.reg = R_REG_E;
    } else if (nextToken.type == REG_F) {
        instruction.reg = R_REG_F;
    }


    return instruction;
}

static Instruction parse_pop(Token **tokens) {
    Instruction instruction;
    instruction.type = I_POP;
    next(tokens);

    Token nextToken = peek(*tokens);
    if (isRegister(nextToken)) {
        next(tokens);
        if (nextToken.type == REG_A) {
            instruction.reg = R_REG_A;
        } else if (nextToken.type == REG_B) {
            instruction.reg = R_REG_B;
        } else if (nextToken.type == REG_C) {
            instruction.reg = R_REG_C;
        } else if (nextToken.type == REG_D) {
            instruction.reg = R_REG_D;
        } else if (nextToken.type == REG_E) {
            instruction.reg = R_REG_E;
        } else if (nextToken.type == REG_F) {
            instruction.reg = R_REG_F;
        }
    } else {
        instruction.reg = R_NONE;
    }

    return instruction;
}

static Instruction parse_peek(Token **tokens) {
    Instruction instruction;
    instruction.type = I_PEEK;
    next(tokens);

    Token nextToken = next(tokens);
    if (!isRegister(nextToken)) {
        printf("Expected register to PEEK\n");
        exit(1);
    }

    if (nextToken.type == REG_A) {
        instruction.reg = R_REG_A;
    } else if (nextToken.type == REG_B) {
        instruction.reg = R_REG_B;
    } else if (nextToken.type == REG_C) {
        instruction.reg = R_REG_C;
    } else if (nextToken.type == REG_D) {
        instruction.reg = R_REG_D;
    } else if (nextToken.type == REG_E) {
        instruction.reg = R_REG_E;
    } else if (nextToken.type == REG_F) {
        instruction.reg = R_REG_F;
    }

    return instruction;
}

static Instruction parse_set(Token **tokens) {
    Instruction instruction;
    instruction.type = I_SET;
    next(tokens);

    Token nextToken = next(tokens);
    if (!isRegister(nextToken)) {
        printf("Expected register to SET\n");
        exit(1);
    }

    if (nextToken.type == REG_A) {
        instruction.reg = R_REG_A;
    } else if (nextToken.type == REG_B) {
        instruction.reg = R_REG_B;
    } else if (nextToken.type == REG_C) {
        instruction.reg = R_REG_C;
    } else if (nextToken.type == REG_D) {
        instruction.reg = R_REG_D;
    } else if (nextToken.type == REG_E) {
        instruction.reg = R_REG_E;
    } else if (nextToken.type == REG_F) {
        instruction.reg = R_REG_F;
    }

    nextToken = next(tokens);
    if (nextToken.type != NUMBER) {
        printf("Expected immediate value to SET\n");
        exit(1);
    }

    instruction.val = atoi(nextToken.text);

    return instruction;
}

static Instruction parse_add(Token **tokens) {
    Instruction instruction;
    instruction.type = I_ADD;
    next(tokens);
    return instruction;
}

static Instruction parse_sub(Token **tokens) {
    Instruction instruction;
    instruction.type = I_SUB;
    next(tokens);
    return instruction;
}

static Instruction parse_mul(Token **tokens) {
    Instruction instruction;
    instruction.type = I_MUL;
    next(tokens);
    return instruction;
}

static Instruction parse_div(Token **tokens) {
    Instruction instruction;
    instruction.type = I_DIV;
    next(tokens);
    return instruction;
}

static Instruction parse_jmp(Token **tokens) {
    Instruction instruction;
    instruction.type = I_JMP;
    next(tokens);

    Token nextToken = next(tokens);
    if (nextToken.type != IDENTIFIER) {
        printf("Expected label to jump to\n");
        exit(1);
    }

    strcpy(instruction.label, nextToken.text);

    return instruction;
}

static Instruction parse_je(Token **tokens) {
    Instruction instruction;
    instruction.type = I_JE;
    next(tokens);

    Token nextToken = next(tokens);
    if (nextToken.type != IDENTIFIER) {
        printf("Expected label to jump to\n");
        exit(1);
    }

    strcpy(instruction.label, nextToken.text);

    return instruction;
}

static Instruction parse_jne(Token **tokens) {
    Instruction instruction;
    instruction.type = I_JNE;
    next(tokens);

    Token nextToken = next(tokens);
    if (nextToken.type != IDENTIFIER) {
        printf("Expected label to jump to\n");
        exit(1);
    }

    strcpy(instruction.label, nextToken.text);

    return instruction;
}

static Instruction parse_ja(Token **tokens) {
    Instruction instruction;
    instruction.type = I_JA;
    next(tokens);

    Token nextToken = next(tokens);
    if (nextToken.type != IDENTIFIER) {
        printf("Expected label to jump to\n");
        exit(1);
    }

    strcpy(instruction.label, nextToken.text);

    return instruction;
}

static Instruction parse_jb(Token **tokens) {
    Instruction instruction;
    instruction.type = I_JB;
    next(tokens);

    Token nextToken = next(tokens);
    if (nextToken.type != IDENTIFIER) {
        printf("Expected label to jump to\n");
        exit(1);
    }

    strcpy(instruction.label, nextToken.text);

    return instruction;
}

static Instruction parse_print(Token **tokens) {
    Instruction instruction;
    instruction.type = I_PRINT;
    next(tokens);
    return instruction;
}

static void parse_label(Token **tokens, char **labels,
                        int *labels_lookup, size_t *labels_len,
                        int instruction_index) {
    strcpy(labels[*labels_len], (*tokens)->text);
    labels_lookup[(*labels_len)++] = instruction_index;
    next(tokens);

    Token t = next(tokens);
    if (t.type != COLON) {
        printf("Expected colon to end label\n");
        exit(1);
    }
}


// Parse an array of tokens into an array of instructions.
size_t parse(Token *tokens, Instruction *instructions, char **labels,
             int *labels_lookup, size_t *labels_len) {
    size_t instruction_index = 0;
    size_t instructions_len = 0;
    Token t;
    Instruction instruction;
    for (t = peek(tokens); t.type != END_OF_FILE; t = peek(tokens)) {
        //printf("Looking at token: ");
        //debug_print_token(t);
        switch (t.type) {
            case HLT:
                instruction = parse_halt(&tokens);
                break;
            case PUSH:
                instruction = parse_push(&tokens);
                break;
            case POP:
                instruction = parse_pop(&tokens);
                break;
            case PEEK:
                instruction = parse_peek(&tokens);
                break;
            case SET:
                instruction = parse_set(&tokens);
                break;
            case ADD:
                instruction = parse_add(&tokens);
                break;
            case SUB:
                instruction = parse_sub(&tokens);
                break;
            case MUL:
                instruction = parse_mul(&tokens);
                break;
            case DIV:
                instruction = parse_div(&tokens);
                break;
            case JMP:
                instruction = parse_jmp(&tokens);
                break;
            case JE:
                instruction = parse_je(&tokens);
                break;
            case JNE:
                instruction = parse_jne(&tokens);
                break;
            case JA:
                instruction = parse_ja(&tokens);
                break;
            case JB:
                instruction = parse_jb(&tokens);
                break;
            case PRINT:
                instruction = parse_print(&tokens);
                break;
            case IDENTIFIER:
                parse_label(&tokens, labels, labels_lookup, labels_len, instruction_index);
                continue;
            default:
                printf("Unexpected token type: %d\n", t.type);
                debug_print_token(*tokens);
                exit(1);
                break;
        }

        instructions[instructions_len++] = instruction;
        instruction_index++;
    }

    return instructions_len;

}

void debug_print_instructions(Instruction *instructions, size_t len) {
    for (size_t i = 0; i < len; i++) {
        debug_print_instruction(instructions[i]);
    }
}

void debug_print_instruction(Instruction instruction) {
        switch (instruction.type) {
            case I_HLT:
                printf("{ HLT, ");
                break;
            case I_PUSH:
                printf("{ PUSH, ");
                break;
            case I_POP:
                printf("{ POP, ");
                break;
            case I_PEEK:
                printf("{ PEEK, ");
                break;
            case I_SET:
                printf("{ SET, ");
                break;
            case I_ADD:
                printf("{ ADD, ");
                break;
            case I_SUB:
                printf("{ SUB, ");
                break;
            case I_MUL:
                printf("{ MUL, ");
                break;
            case I_DIV:
                printf("{ DIV, ");
                break;
            case I_JMP:
                printf("{ JMP, ");
                break;
            case I_JE:
                printf("{ JE, ");
                break;
            case I_JNE:
                printf("{ JNE, ");
                break;
            case I_JA:
                printf("{ JA, ");
                break;
            case I_JB:
                printf("{ JB, ");
                break;
            default:
                printf("Unknown instruction to print!\n");
                exit(1);
                break;
    }

    printf("reg: %d, label: %s, val: %d }\n",
           instruction.reg, instruction.label, instruction.val);
}
