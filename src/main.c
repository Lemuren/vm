#include <stdlib.h>
#include <stdio.h>

#include "tokenizer.h"
#include "parser.h"
#include "execute.h"


int main(int argc, char **argv) {
    // Open input program file.
    if (argc != 2) {
        fprintf(stderr, "usage: stackmachine PROGRAM\n");
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "could not open '%s'\n", argv[1]);
        exit(1);
    }

    // Read entire file into a string.
    // For the sizes we deal with this is fine.
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    rewind(f);
    char *buffer = malloc(length + 1);
    fread(buffer, 1, length, f);
    buffer[length] = '\0';
    fclose(f);

    // Tokenize input.
    Token tokens[1024];
    //size_t tokens_len = tokenize(buffer, tokens);
    tokenize(buffer, tokens);
    // debug_print_tokens(tokens, tokens_len);

    // printf("\n==============\n\n");

    // Parse the tokens into instructions.
    Instruction instructions[1024];
    char **labels = calloc(1024, sizeof(char *));
    for (int i = 0; i < 1024; i++) {
        labels[i] = calloc(64, sizeof(char));
    }
    int labels_lookup[1024];
    size_t labels_len = 0;
    size_t instructions_len = parse(tokens, instructions, labels, labels_lookup, &labels_len);
    //debug_print_instructions(instructions, instructions_len);

    //printf("\n==============\n\n");

    // printf("Labels:\n");
    // for (size_t i = 0; i < labels_len; i++) {
    //     printf("\t%s: %d\n", labels[i], labels_lookup[i]);
    // }

    // printf("\n==============\n\n");

    run(instructions, instructions_len, labels, labels_lookup, labels_len);



    return 0;


}
