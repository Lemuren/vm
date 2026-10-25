set quiet

CC := "gcc"
CFLAGS := "-Wall -Wextra -std=c23 -pedantic -Werror -I src/ -g"

_default:
    just --list

# Build.
build:
    {{CC}} {{CFLAGS}} src/*.c -o stapel
    chmod +x stapel


# Remove build artifacts.
clean:
    rm -f stapel

