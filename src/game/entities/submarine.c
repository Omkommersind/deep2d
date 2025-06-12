#include "submarine.h"
#include "../../tiles/submarine.h"
#include "harpoon.h"

#define ACCEL_X 1
#define ACCEL_Y 1

#define MAX_SPEED 2

#define MIN_X 8
#define MAX_X 160
#define MIN_Y 16
#define MAX_Y 144

#define MAX_VY 2

#define FLOAT_STRENGTH -3
#define GRAVITY_TICK 4

static UINT8 prev_joy = 0;
static INT8 vx = 0;
static INT8 vy = 0;
static UINT8 x = 0;
static UINT8 y = 0;
static UINT8 sink_delay = 0;
static UINT8 sink_counter = 0;
static Direction dir = DIRECTION_RIGHT;

static void render(void);

Direction submarine_get_direction(void) {
    return dir;
}

UINT8 submarine_get_x(void) {
    return x;
}

UINT8 submarine_get_y(void) {
    return y;
}

void submarine_init(void) {
    set_sprite_data(0, 4, Submarine);
    vx = 0;
    vy = 0;
}

void submarine_draw(UINT8 start_x, UINT8 start_y) {
    x = start_x;
    y = start_y;

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
            vx = -MAX_SPEED;
        } else if (joy & J_RIGHT) {
            vx = MAX_SPEED;
        } else {
            vx = 0;
        }
    }

    // Apply upward force only when pressing A (reset each frame)
    if (joy & J_A) {
        vy = -1;  // gentle lift
    } else {
        vy = 0;
    }

    if ((joy & J_B) && !(prev_joy & J_B)) {
        if (!harpoon_is_active()) {
            harpoon_start(submarine_get_direction());
        }
    }

    prev_joy = joy;
}


void submarine_update(void) {
    x += vx;
    y += vy;

    // Slow sinking like original
    sink_counter++;
    if (sink_counter >= 30) {
        y++;
        sink_counter = 0;
    }

    // Gravity when not pressing A
    if (!(prev_joy & J_A)) {
        sink_delay++;
        if (sink_delay >= 3) {
            if (vy < MAX_SPEED) {
                vy++;  // sink slower
            }
            sink_delay = 0;
        }
    } else {
        sink_delay = 0; // reset delay
    }

    if (vy > MAX_SPEED) vy = MAX_SPEED;
    if (vy < -MAX_SPEED) vy = -MAX_SPEED;

    if (x < MIN_X) x = MIN_X;
    if (x > MAX_X) x = MAX_X;
    if (y < MIN_Y) y = MIN_Y;
    if (y > MAX_Y) y = MAX_Y;

    render();
    harpoon_animate();
}


static void render(void) {
    Direction dir = submarine_get_direction();
    UINT8 flip = (dir == DIRECTION_LEFT) ? S_FLIPX : 0;

    if (dir == DIRECTION_RIGHT) {
        set_sprite_tile(0, 0);
        set_sprite_tile(1, 1);
    } else {
        set_sprite_tile(0, 1);
        set_sprite_tile(1, 0);
    }

    set_sprite_prop(0, flip);
    set_sprite_prop(1, flip);

    move_sprite(0, x, y);
    move_sprite(1, x + 8, y);
}

void submarine_hide(void) {
    for (UINT8 i = 0; i < 4; i++) {
        move_sprite(SUBMARINE_SPRITE_START + i, 0, 160);
    }
}
