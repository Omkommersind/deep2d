#ifndef HARPOON_H
#define HARPOON_H

#include <gb/gb.h>
#include "types.h"

#define HARPOON_SPRITE_START 2
#define HARPOON_SEGMENTS 3

typedef enum {
    HARPOON_INACTIVE,
    HARPOON_EXTENDING,
    HARPOON_PAUSING,
    HARPOON_RETRACTING
} HarpoonState;

void harpoon_start(UINT8 x, UINT8 y, Direction dir);
void harpoon_animate(void);
void harpoon_hide(void);

#endif
