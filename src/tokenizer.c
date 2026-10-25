#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer.h"

// Tokenizes an input string.
size_t tokenize(char *s, Token *tokens) {
    size_t tokens_len = 0;

    char *stoken;
    TokenType type = 0;
    char *text;
    while ((stoken = strtok(s, " \t\n"))) {
        // Set s to NULL for reentry into strok.
        s = NULL;

        // If we see semicolon, discard input until newline.
        if (stoken[0] == ';') {
            strtok(s, "\n");
            continue;
        }

        // Parse text into a token.
        if (strcmp(stoken, "A") == 0) {
            type = REG_A;
            text = "A";
        } else if (strcmp(stoken, "B") == 0) {
            type = REG_B;
            text = "B";
        } else if (strcmp(stoken, "C") == 0) {
            type = REG_C;
            text = "C";
        } else if (strcmp(stoken, "D") == 0) {
            type = REG_D;
            text = "D";
        } else if (strcmp(stoken, "E") == 0) {
            type = REG_E;
            text = "E";
        } else if (strcmp(stoken, "F") == 0) {
            type = REG_F;
            text = "F";
        } else if (strcmp(stoken, ";") == 0) {
            type = SEMICOLON;
            text = ";";
        } else if (strcmp(stoken, ":") == 0) {
            type = COLON;
            text = ":";
        } else if (strcmp(stoken, "HLT") == 0) {
            type = HLT;
            text = "HLT";
        } else if (strcmp(stoken, "PUSH") == 0) {
            type = PUSH;
            text = "PUSH";
        } else if (strcmp(stoken, "POP") == 0) {
            type = POP;
            text = "POP";
        } else if (strcmp(stoken, "PEEK") == 0) {
            type = PEEK;
            text = "PEEK";
        } else if (strcmp(stoken, "SET") == 0) {
            type = SET;
            text = "SET";
        } else if (strcmp(stoken, "ADD") == 0) {
            type = ADD;
            text = "ADD";
        } else if (strcmp(stoken, "SUB") == 0) {
            type = SUB;
            text = "SUB";
        } else if (strcmp(stoken, "MUL") == 0) {
            type = MUL;
            text = "MUL";
        } else if (strcmp(stoken, "JMP") == 0) {
            type = JMP;
            text = "JMP";
        } else if (strcmp(stoken, "JE") == 0) {
            type = JE;
            text = "JE";
        } else if (strcmp(stoken, "JNE") == 0) {
            type = JNE;
            text = "JNE";
        } else if (strcmp(stoken, "JA") == 0) {
            type = JA;
            text = "JA";
        } else if (strcmp(stoken, "JB") == 0) {
            type = JB;
            text = "JB";
        } else if (strcmp(stoken, "\n") == 0) {
            type = NEWLINE;
            text = "";
        } else if ((atoi(stoken) != 0) || (strcmp(stoken, "0") == 0)) {
            type = NUMBER;
            text = stoken;
        // Identifiers are a bit of special case.
        } else {
            if (stoken[strlen(stoken) - 1] == ':') {
                Token t;
                t.type = IDENTIFIER;
                strncpy(t.text, stoken, strlen(stoken) - 1);
                t.text[strlen(stoken) - 1] = '\0';
                tokens[tokens_len++] = t;

                Token p;
                p.type = COLON;
                strcpy(p.text, ":");
                tokens[tokens_len++] = p;
            } else {
                Token t;
                t.type = IDENTIFIER;
                strcpy(t.text, stoken);
                tokens[tokens_len++] = t;
            }

            continue;
        }

        // Create token and append it.
        Token t;
        t.type = type;
        strcpy(t.text, text);
        tokens[tokens_len++] = t;
    }

    // Set ending END_OF_FILE token.
    Token *t = malloc(sizeof(*t));
    t->type = END_OF_FILE;
    strcpy(t->text, "");
    tokens[tokens_len++] = *t;

    return tokens_len;
}


// DEBUG FUNCTIONS
// Print an array of tokens.
void debug_print_tokens(Token *tokens, size_t len) {
    for (size_t i = 0; i < len; i++) {
        debug_print_token(tokens[i]);
    }
}

void debug_print_token(Token token) {
    switch (token.type) {
        case REG_A:
            printf("{ REG_A, ");
            break;
        case REG_B:
            printf("{ REG_B, ");
            break;
        case REG_C:
            printf("{ REG_C, ");
            break;
        case REG_D:
            printf("{ REG_D, ");
            break;
        case REG_E:
            printf("{ REG_E, ");
            break;
        case REG_F:
            printf("{ REG_F, ");
            break;
        case SEMICOLON:
            printf("{ SEMICOLON, ");
            break;
        case COLON:
            printf("{ COLON, ");
            break;
        case IDENTIFIER:
            printf("{ IDENTIFIER, ");
            break;
        case NUMBER:
            printf("{ NUMBER, ");
            break;
        case HLT:
            printf("{ HLT, ");
            break;
        case PUSH:
            printf("{ PUSH, ");
            break;
        case POP:
            printf("{ POP, ");
            break;
        case PEEK:
            printf("{ PEEK, ");
            break;
        case SET:
            printf("{ SET, ");
            break;
        case ADD:
            printf("{ ADD, ");
            break;
        case SUB:
            printf("{ SUB, ");
            break;
        case MUL:
            printf("{ MUL, ");
            break;
        case DIV:
            printf("{ DIV, ");
            break;
        case JMP:
            printf("{ JMP, ");
            break;
        case JE:
            printf("{ JE, ");
            break;
        case JNE:
            printf("{ JNE, ");
            break;
        case JA:
            printf("{ JA, ");
            break;
        case JB:
            printf("{ JB, ");
            break;
        case END_OF_FILE:
            printf("{ EOF, ");
            break;
        case NEWLINE:
            printf("{ NEWLINE, ");
            break;
        case UNKNOWN:
            printf("{ ???, ");
            break;
        default:
            printf("{ !?!, ");
            break;
    }

    printf("%s }\n", token.text);
}
