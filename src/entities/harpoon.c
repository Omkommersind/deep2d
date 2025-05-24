#include "harpoon.h"
#include "submarine.h"
#include "../tiles/submarine.h"

static Direction harpoon_dir;

static UINT8 harpoon_flip = 0;
static UINT8 harpoon_anim_delay = 0;
static UINT8 harpoon_rope_len = 0;
static HarpoonState harpoon_state = HARPOON_INACTIVE;

UBYTE harpoon_is_active(void) {
    return harpoon_state != HARPOON_INACTIVE;
}

void harpoon_start(Direction dir) {
    harpoon_dir = dir;
    harpoon_rope_len = 0;
    harpoon_flip = 0;
    harpoon_anim_delay = 0;
    harpoon_state = HARPOON_EXTENDING;
}

void harpoon_animate(void) {
    if (harpoon_state == HARPOON_INACTIVE) return;

    // ✅ Always recalculate position relative to sub
    UINT8 base_x = (harpoon_dir == DIRECTION_RIGHT)
                 ? submarine_get_x() + 16
                 : submarine_get_x() - 8;
    UINT8 base_y = submarine_get_y();

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

    // ✅ Handle each state
    if (harpoon_state == HARPOON_EXTENDING) {
        for (UINT8 i = 0; i < harpoon_rope_len; i++) {
            set_sprite_tile(HARPOON_SPRITE_START + i, 2);
            set_sprite_prop(HARPOON_SPRITE_START + i, flip_flag);
            move_sprite(HARPOON_SPRITE_START + i, base_x + harpoon_dir * (i * 8), base_y);
        }

        UINT8 hook_id = HARPOON_SPRITE_START + harpoon_rope_len;
        set_sprite_tile(hook_id, 3);
        set_sprite_prop(hook_id, flip_flag);
        move_sprite(hook_id, base_x + harpoon_dir * (harpoon_rope_len * 8), base_y);

        harpoon_rope_len++;
        if (harpoon_rope_len > HARPOON_SEGMENTS) {
            harpoon_rope_len = HARPOON_SEGMENTS;
            harpoon_state = HARPOON_PAUSING;
            harpoon_anim_delay = 0;
        }
    }
    else if (harpoon_state == HARPOON_PAUSING) {
        static UINT8 pause_count = 0;
        pause_count++;
        // ✅ Draw rope + hook again to follow sub
        for (UINT8 i = 0; i < harpoon_rope_len; i++) {
            move_sprite(HARPOON_SPRITE_START + i, base_x + harpoon_dir * (i * 8), base_y);
        }
        move_sprite(HARPOON_SPRITE_START + HARPOON_SEGMENTS,
                    base_x + harpoon_dir * (harpoon_rope_len * 8), base_y);

        if (pause_count >= HARPOON_PAUSE_FRAMES) {
            pause_count = 0;
            harpoon_state = HARPOON_RETRACTING;
        }
    }
    else if (harpoon_state == HARPOON_RETRACTING) {
        if (harpoon_rope_len > 0) {
            harpoon_rope_len--;

            move_sprite(HARPOON_SPRITE_START + harpoon_rope_len, 0, 160);

            move_sprite(HARPOON_SPRITE_START + HARPOON_SEGMENTS,
                        base_x + harpoon_dir * (harpoon_rope_len * 8), base_y);
        } else {
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
