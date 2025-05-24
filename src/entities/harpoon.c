#include "harpoon.h"
#include "../tiles/submarine.h"

static UINT8 harpoon_x;
static UINT8 harpoon_y;
static Direction harpoon_dir;

static UINT8 harpoon_flip = 0;
static UINT8 harpoon_anim_delay = 0;
static UINT8 harpoon_rope_len = 0;
static HarpoonState harpoon_state = HARPOON_INACTIVE;

UBYTE harpoon_is_active(void) {
    return harpoon_state != HARPOON_INACTIVE;
}

void harpoon_start(UINT8 x, UINT8 y, Direction dir) {
    harpoon_x = x;
    harpoon_y = y;
    harpoon_dir = dir;
    harpoon_rope_len = 0;
    harpoon_flip = 0;
    harpoon_anim_delay = 0;
    harpoon_state = HARPOON_EXTENDING;
}

void harpoon_animate(void) {
    if (harpoon_state == HARPOON_INACTIVE) return;

    UINT8 required_delay = (harpoon_state == HARPOON_RETRACTING)
                        ? HARPOON_RETRACT_DELAY
                        : HARPOON_EXTEND_DELAY;

    if (harpoon_anim_delay < required_delay) {
        harpoon_anim_delay++;
        return;
    }

    harpoon_anim_delay = 0;
    harpoon_flip ^= 1;
    UINT8 flip_flag = 0;
    if (harpoon_flip) flip_flag |= S_FLIPY;
    if (harpoon_dir == DIRECTION_LEFT) flip_flag |= S_FLIPX;

    if (harpoon_state == HARPOON_EXTENDING) {
        // Draw all rope so far
        for (UINT8 i = 0; i < harpoon_rope_len; i++) {
            UINT8 sprite_id = HARPOON_SPRITE_START + i;
            set_sprite_tile(sprite_id, 2);
            set_sprite_prop(sprite_id, flip_flag);
            move_sprite(sprite_id, harpoon_x + harpoon_dir * (i * 8), harpoon_y);
        }

        // Draw hook at the end
        UINT8 hook_id = HARPOON_SPRITE_START + harpoon_rope_len;
        set_sprite_tile(hook_id, 3);
        set_sprite_prop(hook_id, flip_flag);
        move_sprite(hook_id, harpoon_x + harpoon_dir * (harpoon_rope_len * 8), harpoon_y);

        harpoon_rope_len++;

        if (harpoon_rope_len > HARPOON_SEGMENTS) {
            harpoon_rope_len = HARPOON_SEGMENTS;
            harpoon_anim_delay = 0;
            harpoon_state = HARPOON_PAUSING;
        }
    }
    else if (harpoon_state == HARPOON_PAUSING) {
        static UINT8 pause_count = 0;
        pause_count++;
        if (pause_count >= HARPOON_PAUSE_FRAMES) {
            pause_count = 0;
            harpoon_state = HARPOON_RETRACTING;
        }
    }
    else if (harpoon_state == HARPOON_RETRACTING) {
        // First retract rope, then hook
        if (harpoon_rope_len > 0) {
            harpoon_rope_len--;

            // Hide last rope segment
            move_sprite(HARPOON_SPRITE_START + harpoon_rope_len, 0, 160);

            // Move hook to the new end
            UINT8 hook_id = HARPOON_SPRITE_START + HARPOON_SEGMENTS;
            move_sprite(hook_id, harpoon_x + harpoon_dir * (harpoon_rope_len * 8), harpoon_y);
        } else {
            // Now hide hook
            move_sprite(HARPOON_SPRITE_START + HARPOON_SEGMENTS, 0, 160);
            harpoon_state = HARPOON_INACTIVE;
        }
    }
}


void harpoon_hide(void) {
    for (UINT8 i = 0; i <= HARPOON_SEGMENTS; i++) {
        move_sprite(HARPOON_SPRITE_START + i, 0, 160); // move offscreen
    }
}
