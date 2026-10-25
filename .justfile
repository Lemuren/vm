CC := "gcc"
CFLAGS := "-Wall -Wextra -std=c23 -pedantic -Werror -I src/"

_default:
    @just --list

# Build.
build:
    {{CC}} {{CFLAGS}} -g src/*.c -o stapel
    chmod +x stapel

# Run tests.
test:
    {{CC}} {{CFLAGS}} -I test/ src/tokenizer.c test/test_tokenizer.c -o test_tokenizer
    chmod +x test_tokenizer
    ./test_tokenizer

# Remove build artifacts.
clean:
    rm -f stapel test_tokenizer

