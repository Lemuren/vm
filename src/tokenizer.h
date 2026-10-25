#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum {
    REG_A,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_F,
    SEMICOLON,
    COMMA,
    IDENTIFIER,
    NUMBER,
    HLT,
    PUSH,
    POP,
    PEEK,
    SET,
    ADD,
    SUB,
    MUL,
    DIV,
    JMP,
    JE,
    JNE,
    JA,
    JB,
    END_OF_FILE,
    NEWLINE
} TokenType;

// TODO: Fixed-sized text field is not ideal.
typedef struct {
    TokenType type;
    char text[64];
} Token;

#endif
