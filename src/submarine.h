#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <gb/gb.h>

void submarine_init(void);
void submarine_draw(UINT8 x, UINT8 y);
void submarine_move(UINT8 x, UINT8 y);
void submarine_hide(void);

#endif
