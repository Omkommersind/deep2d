#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <gb/gb.h>
#include "../../types.h"

void submarine_init(void);
void submarine_draw(UINT8 x, UINT8 y);
void submarine_move(UINT8 x, UINT8 y);
void submarine_hide(void);
void submarine_update(void);
void submarine_handle_input(UINT8 joy);

Direction submarine_get_direction(void);
UINT8 submarine_get_x(void);
UINT8 submarine_get_y(void);

#define SUBMARINE_TILE_COUNT 4
#define SUBMARINE_SPRITE_START 0

#endif
