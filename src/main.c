#include <stdlib.h>
#include <stdio.h>

#include "tokenizer.h"


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
    size_t tokens_len = tokenize(buffer, tokens);
    debug_print_tokens(tokens, tokens_len);

    // Parse the tokens into instructions.

    return 0;


}
