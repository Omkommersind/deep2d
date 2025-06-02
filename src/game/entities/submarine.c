#include "submarine.h"
#include "../../tiles/submarine.h"
#include "harpoon.h"

#define SUBMARINE_ACCEL_X 1
#define SUBMARINE_ACCEL_Y 1
#define SUBMARINE_MAX_SPEED 2
#define SUBMARINE_MIN_X 8
#define SUBMARINE_MAX_X 160
#define SUBMARINE_MIN_Y 16
#define SUBMARINE_MAX_Y 144

static UINT8 prev_joy = 0;
static INT8 submarine_vx = 0;
static INT8 submarine_vy = 0;
static UINT8 submarine_x = 0;
static UINT8 submarine_y = 0;

Direction submarine_direction = DIRECTION_RIGHT;

void submarine_init(void) {
    set_sprite_data(0, 4, Submarine);
    submarine_direction = DIRECTION_RIGHT;
    submarine_vx = 0;
    submarine_vy = 0;
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

void submarine_handle_input(UINT8 joy) {
    if (!harpoon_is_active()) {
        if (joy & J_LEFT) {
            submarine_direction = DIRECTION_LEFT;
            submarine_x--;
        } else if (joy & J_RIGHT) {
            submarine_direction = DIRECTION_RIGHT;
            submarine_x++;
        }
    }

    if ((joy & J_B) && !(prev_joy & J_B)) {
        if (!harpoon_is_active()) {
            harpoon_start(submarine_direction);
        }
    }

    prev_joy = joy;
}

void submarine_update(void) {
    // Automatic sinking
    static UINT8 sink_counter = 0;
    sink_counter++;
    if (sink_counter >= 30) {
        submarine_y++;
        sink_counter = 0;
    }

    // Clamp to screen bounds
    if (submarine_x < SUBMARINE_MIN_X) submarine_x = SUBMARINE_MIN_X;
    if (submarine_x > SUBMARINE_MAX_X) submarine_x = SUBMARINE_MAX_X;
    if (submarine_y < SUBMARINE_MIN_Y) submarine_y = SUBMARINE_MIN_Y;
    if (submarine_y > SUBMARINE_MAX_Y) submarine_y = SUBMARINE_MAX_Y;

    submarine_move(submarine_x, submarine_y);
    harpoon_animate();
}

void submarine_move(UINT8 x, UINT8 y) {
    UINT8 flip = (submarine_direction == DIRECTION_LEFT) ? S_FLIPX : 0;

    if (submarine_direction == DIRECTION_RIGHT) {
        set_sprite_tile(0, 0);
        set_sprite_tile(1, 1);

        set_sprite_prop(0, flip);
        set_sprite_prop(1, flip);

        move_sprite(0, x, y);
        move_sprite(1, x + 8, y);
    } else {
        set_sprite_tile(0, 1);
        set_sprite_tile(1, 0);

        set_sprite_prop(0, flip);
        set_sprite_prop(1, flip);

        move_sprite(0, x, y);
        move_sprite(1, x + 8, y);
    }
}

void submarine_hide(void) {
    for (UINT8 i = 0; i < 4; i++) {
        move_sprite(SUBMARINE_SPRITE_START + i, 0, 160);
    }
}
