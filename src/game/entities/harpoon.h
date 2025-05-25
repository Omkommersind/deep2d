#ifndef HARPOON_H
#define HARPOON_H

#include <gb/gb.h>
#include "../../types.h"

#define HARPOON_SPRITE_START 2
#define HARPOON_DELAY_FRAMES 6
#define HARPOON_SEGMENTS 4
#define HARPOON_PAUSE_FRAMES 6
#define HARPOON_EXTEND_DELAY 6
#define HARPOON_RETRACT_DELAY 12

typedef enum {
    HARPOON_INACTIVE,
    HARPOON_EXTENDING,
    HARPOON_PAUSING,
    HARPOON_RETRACTING
} HarpoonState;

void harpoon_start(Direction dir);
void harpoon_animate(void);
void harpoon_hide(void);
static void harpoon_follow_submarine_y(void);

UBYTE harpoon_is_active(void);

#endif
