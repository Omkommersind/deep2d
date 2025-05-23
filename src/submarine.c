#include "submarine.h"
#include "tiles/submarine.h"
#include "harpoon.h"

#define SUBMARINE_TILE_COUNT 4
#define SUBMARINE_SPRITE_START 0

static UINT8 prev_joy = 0;
static UINT8 submarine_x = 0;
static UINT8 submarine_y = 0;
Direction submarine_direction = DIRECTION_RIGHT;

void submarine_init(void) {
    set_sprite_data(0, 4, Submarine);
    submarine_direction = DIRECTION_RIGHT;
}

Direction submarine_get_direction(void) {
    return submarine_direction;
}

UINT8 submarine_get_x(void) {
    return submarine_x;
}

UINT8 submarine_get_y(void) {
    return submarine_y;
}


void submarine_draw(UINT8 x, UINT8 y) {
    submarine_x = x;
    submarine_y = y;
    submarine_direction = DIRECTION_RIGHT;

    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);

    move_sprite(0, x, y);
    move_sprite(1, x + 8, y);

    move_sprite(2, 0, 160);
    move_sprite(3, 0, 160);
    move_sprite(4, 0, 160);
    move_sprite(5, 0, 160);
}

void submarine_update(UINT8 joy) {
    if (joy & J_LEFT) {
        submarine_direction = DIRECTION_LEFT;
    } else if (joy & J_RIGHT) {
        submarine_direction = DIRECTION_RIGHT;
    }

    // Fire harpoon once per button press
    if ((joy & J_B) && !(prev_joy & J_B)) {
        if (!harpoon_is_active()) {
            UINT8 front_x = (submarine_direction == DIRECTION_RIGHT)
                        ? submarine_x + 16
                        : submarine_x - 8;
            harpoon_start(front_x, submarine_y, submarine_direction);
        }
    }

    // Animate harpoon each frame if active
    harpoon_animate();

    prev_joy = joy;
}

void submarine_move(UINT8 x, UINT8 y) {
    // Move only body
    move_sprite(SUBMARINE_SPRITE_START + 0, x, y);
    move_sprite(SUBMARINE_SPRITE_START + 1, x + 8, y);
}

void submarine_hide(void) {
    for (UINT8 i = 0; i < 4; i++) {
        move_sprite(SUBMARINE_SPRITE_START + i, 0, 160);
    }
}