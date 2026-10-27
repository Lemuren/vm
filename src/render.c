#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "render.h"
#include "execute.h"

// Screen width and height.
#define MINX 60
#define MINY 15
static int scrx = 0;
static int scry = 0;

// We have three subwindows: the program, the registers/state, and the stack.
static WINDOW *programwin;
static WINDOW *statuswin;
static WINDOW *stackwin;
static WINDOW *stdoutwin;

void initRender() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    getmaxyx(stdscr, scry, scrx);
    if ((scrx < MINX) || (scry < MINY)) {
        fprintf(stderr, "Your window size is too small!\n");
        deinitRender();
        exit(1);
    }

    programwin = newwin(scry - 7, scrx - 20, 0, 0);
    stdoutwin = newwin(7, scrx - 20, scry - 7, 0);
    statuswin = newwin(10, 20, 0, scrx - 20);
    stackwin = newwin(scry - 10, 20, 10, scrx - 20);
}

void deinitRender() {
    printf("X: %d\tY: %d\n", scrx, scry);
    endwin();
}

static void formatInstruction(Instruction instruction, char *out) {
    if (instruction.type == I_HLT) {
        sprintf(out, "HLT");
    }

    if (instruction.type == I_PUSH) {
        switch (instruction.reg) {
            case R_REG_A:
                sprintf(out, "PUSH A");
                break;
            case R_REG_B:
                sprintf(out, "PUSH B");
                break;
            case R_REG_C:
                sprintf(out, "PUSH C");
                break;
            case R_REG_D:
                sprintf(out, "PUSH D");
                break;
            case R_REG_E:
                sprintf(out, "PUSH E");
                break;
            case R_REG_F:
                sprintf(out, "PUSH F");
                break;
            case R_NONE:
                sprintf(out, "PUSH %d", instruction.val);
                break;
        }
    }

    if (instruction.type == I_POP) {
        switch (instruction.reg) {
            case R_REG_A:
                sprintf(out, "POP A");
                break;
            case R_REG_B:
                sprintf(out, "POP B");
                break;
            case R_REG_C:
                sprintf(out, "POP C");
                break;
            case R_REG_D:
                sprintf(out, "POP D");
                break;
            case R_REG_E:
                sprintf(out, "POP E");
                break;
            case R_REG_F:
                sprintf(out, "POP F");
                break;
            case R_NONE:
                sprintf(out, "POP");
                break;
        }
    }

    if (instruction.type == I_PEEK) {
        switch (instruction.reg) {
            case R_REG_A:
                sprintf(out, "PEEK A");
                break;
            case R_REG_B:
                sprintf(out, "PEEK B");
                break;
            case R_REG_C:
                sprintf(out, "PEEK C");
                break;
            case R_REG_D:
                sprintf(out, "PEEK D");
                break;
            case R_REG_E:
                sprintf(out, "PEEK E");
                break;
            case R_REG_F:
                sprintf(out, "PEEK F");
                break;
            case R_NONE:
                // We shouldn't be able to get here.
                break;
        }
    }

    if (instruction.type == I_SET) {
        switch (instruction.reg) {
            case R_REG_A:
                sprintf(out, "SET A %d", instruction.val);
                break;
            case R_REG_B:
                sprintf(out, "SET B %d", instruction.val);
                break;
            case R_REG_C:
                sprintf(out, "SET C %d", instruction.val);
                break;
            case R_REG_D:
                sprintf(out, "SET D %d", instruction.val);
                break;
            case R_REG_E:
                sprintf(out, "SET E %d", instruction.val);
                break;
            case R_REG_F:
                sprintf(out, "SET F %d", instruction.val);
                break;
            case R_NONE:
                // We shouldn't be able to get here.
                break;
        }
    }

    if (instruction.type == I_ADD) {
        sprintf(out, "ADD");
    }

    if (instruction.type == I_SUB) {
        sprintf(out, "SUB");
    }

    if (instruction.type == I_MUL) {
        sprintf(out, "MUL");
    }

    if (instruction.type == I_DIV) {
        sprintf(out, "DIV");
    }

    if (instruction.type == I_MOD) {
        sprintf(out, "MOD");
    }

    if (instruction.type == I_JMP) {
        sprintf(out, "JMP %s", instruction.label);
    }

    if (instruction.type == I_JE) {
        sprintf(out, "JE %s", instruction.label);
    }

    if (instruction.type == I_JNE) {
        sprintf(out, "JNE %s", instruction.label);
    }

    if (instruction.type == I_JA) {
        sprintf(out, "JA %s", instruction.label);
    }

    if (instruction.type == I_JB) {
        sprintf(out, "JB %s", instruction.label);
    }

    if (instruction.type == I_PRINT) {
        sprintf(out, "PRINT");
    }

    if (instruction.type == I_SCAN) {
        sprintf(out, "SCAN");
    }
}

static void update_statuswin(State state) {
    box(statuswin, 0, 0);
    mvwprintw(statuswin, 1, 1, "           ");
    mvwprintw(statuswin, 2, 1, "           ");
    mvwprintw(statuswin, 3, 1, "           ");
    mvwprintw(statuswin, 4, 1, "           ");
    mvwprintw(statuswin, 5, 1, "           ");
    mvwprintw(statuswin, 6, 1, "           ");
    mvwprintw(statuswin, 7, 1, "           ");

    mvwprintw(statuswin, 1, 1, " IP: %ld ", state.reg_ip);
    mvwprintw(statuswin, 2, 1, " A:  %d ", state.reg_a);
    mvwprintw(statuswin, 3, 1, " B:  %d ", state.reg_b);
    mvwprintw(statuswin, 4, 1, " C:  %d ", state.reg_c);
    mvwprintw(statuswin, 5, 1, " D:  %d ", state.reg_d);
    mvwprintw(statuswin, 6, 1, " E:  %d ", state.reg_e);
    mvwprintw(statuswin, 7, 1, " F:  %d ", state.reg_f);
    if (state.running) {
        mvwprintw(statuswin, 8, 1, " RUNNING");
    } else {
        mvwprintw(statuswin, 8, 1, " HALTED ");
    }
}

static void update_stdoutwin(char *outputBuffer) {
    // Get window size, taking border into account.
    int height;
    int width;
    getmaxyx(stdoutwin, height, width);
    height -= 2;
    width  -= 2;
    (void)width;
    box(stdoutwin, 0, 0);

    // Clear stdout window.
    for (int i = 1; i <= height; i++) {
        mvwprintw(stdoutwin, i, 1, "                           ");
    }

    // Print last 5 lines of the output.
    char *start = outputBuffer + strlen(outputBuffer);
    int lines = 0;
    while (start > outputBuffer && lines < 6) {
        start--;
        if (*start == '\n') lines++;
    }
    if (lines == 6 && *start == '\n') start++;

    int line = 1;
    wmove(stdoutwin, line, 1);
    while ((line < 6) && (*start != '\0')) {
        if (*start == '\n') {
            wmove(stdoutwin, ++line, 1);
        } else {
            waddch(stdoutwin, *start);
        }

        start++;
    }
}

static void update_programwin(State state, Instruction *instructions,
                              size_t instructions_len, char **labels,
                              size_t *labels_lookup, size_t labels_len) {
    box(programwin, 0, 0);

    // Get window size, taking border into account.
    int height;
    int width;
    getmaxyx(programwin, height, width);
    height -= 2;
    width  -= 2;
    (void)width;

    // We'll print as many instructions as fits,
    // displaying 2 previous ones before the current one.
    size_t start = state.reg_ip < 2 ? 0 : state.reg_ip - 2;
    size_t end = start + (size_t)height > instructions_len ? instructions_len : start + (size_t)height;

    for (size_t y = 1; y <= (size_t)height; y++) {
        mvwprintw(programwin, y, 1, "                                     ");
    }
    for (size_t y = 1, ip = start; ip < end; y++, ip++) {
        // If there's a label associated with the current instruction, print it.
        for (size_t i = 0; i < labels_len; i++) {
            if (labels_lookup[i] == ip) {
                mvwprintw(programwin, y, 1, "%16s:", labels[i]);
            }
        }

        // Print the instruction.
        char s[64] = { 0 };
        formatInstruction(instructions[ip], s);
        if (ip == state.reg_ip) wattron(programwin, A_REVERSE);
        mvwprintw(programwin, y, 20, "  %-20s", s);
        wattroff(programwin, A_REVERSE);
    }


}

static void update_stackwin(State state) {
    box(stackwin, 0, 0);

    // Get window size, taking border into account.
    int height;
    int width;
    getmaxyx(stackwin, height, width);
    height -= 2;
    width  -= 2;
    (void)width;

    size_t start = (int)state.stackSize - height < 0 ?
                                                   0 :
                                                   state.stackSize - (size_t)height;

    // Print stack.
    for (size_t i = 1; i <= (size_t)height; i++) {
        mvwprintw(stackwin, i, 1, "                  ");
    }
    for (size_t i = 0; start + i < state.stackSize ; i++) {
        if (start + i == state.stackSize - 1) wattron(stackwin, A_REVERSE);
        mvwprintw(stackwin, height - i, 1, " %-16d ", state.stack[start + i]);
        wattroff(stackwin, A_REVERSE);
    }
}

void update_screen(State state, Instruction *instructions,
                   size_t instructions_len, char **labels, size_t *labels_lookup,
                   size_t labels_len, char *outputBuffer) {
    update_statuswin(state);
    update_stackwin(state);
    update_stdoutwin(outputBuffer);
    update_programwin(state, instructions, instructions_len,
                      labels, labels_lookup, labels_len);

    wrefresh(programwin);
    wrefresh(statuswin);
    wrefresh(stackwin);
    wrefresh(stdoutwin);

    wgetch(programwin);
}
