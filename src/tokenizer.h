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
    COLON,
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
    MOD,
    JMP,
    JE,
    JNE,
    JA,
    JB,
    PRINT,
    END_OF_FILE,
    NEWLINE,
    UNKNOWN
} TokenType;

// TODO: Fixed-sized text field is not ideal.
typedef struct {
    TokenType type;
    char text[64];
} Token;

size_t tokenize(char*, Token*);
void debug_print_tokens(Token*, size_t);
void debug_print_token(Token);

#endif
