#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <gb/gb.h>
#include "types.h"

void submarine_init(void);
void submarine_draw(UINT8 x, UINT8 y);
void submarine_move(UINT8 x, UINT8 y);
void submarine_hide(void);
void submarine_update(UINT8 joy);

Direction submarine_get_direction(void);
UINT8 submarine_get_x(void);
UINT8 submarine_get_y(void);

#endif
