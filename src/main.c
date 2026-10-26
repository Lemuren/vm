#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "tokenizer.h"
#include "parser.h"
#include "execute.h"
#include "render.h"


int main(int argc, char **argv) {
    // TODO: Proper argument parsing.
    bool plain = false;

    // Open input program file.
    if (argc < 2) {
        fprintf(stderr, "usage: stackmachine PROGRAM [--plain]\n");
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "could not open '%s'\n", argv[1]);
        exit(1);
    }

    if (argc == 3) {
        if (strcmp(argv[2], "--plain") == 0) {
            plain = true;
        } else {
            fprintf(stderr, "usage: stackmachine PROGRAM [--plain]\n");
        }
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
    tokenize(buffer, tokens);

    // Parse the tokens into instructions.
    Instruction instructions[1024];
    char **labels = calloc(1024, sizeof(char *));
    for (int i = 0; i < 1024; i++) {
        labels[i] = calloc(64, sizeof(char));
    }
    size_t labels_lookup[1024];
    size_t labels_len = 0;
    size_t instructions_len = parse(tokens, instructions, labels, labels_lookup, &labels_len);

    // Initialize renderer.
    if (!plain) initRender();

    // Set up state and start running the program.
    State state = {
        .running    = true,
        .stack      = { 0 },
        .stackSize  = 0,
        .reg_ip     = 0,
        .reg_a     = 0,
        .reg_b     = 0,
        .reg_c     = 0,
        .reg_d     = 0,
        .reg_e     = 0,
        .reg_f     = 0
    };
    char *outputBuffer = calloc(1024, sizeof(char));
    char *origBuffer = outputBuffer;

    while (state.running) {
        if (!plain) {
            update_screen(state, instructions, instructions_len,
                        labels, labels_lookup, labels_len, origBuffer);
        }
        run(instructions, labels,
            labels_lookup, labels_len, &state, plain ? NULL : &outputBuffer);
    }
    if (!plain) {
        update_screen(state, instructions, instructions_len,
                        labels, labels_lookup, labels_len, origBuffer);
        deinitRender();
    }

    return 0;
}
