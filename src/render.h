#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>
#include "execute.h"

void initRender();
void deinitRender();
void update_screen(State, Instruction*, size_t, char**, size_t*, size_t, char*);


#endif
