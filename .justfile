set quiet

CC := "gcc"
CFLAGS := "-Wall -Wextra -std=c11 -pedantic -Werror -I src/ -g"
NCURSES := "-lncurses"

_default:
    just --list

# Build.
build:
    {{CC}} {{CFLAGS}} src/*.c -o stapel {{NCURSES}}
    chmod +x stapel

# Test.
test: build
    ./runtests.sh

# Remove build artifacts.
clean:
    rm -f stapel

