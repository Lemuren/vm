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

    // Tokenize input.
    // Token *tokens[] = tokenize(f);

    return 0;


}
