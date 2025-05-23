#include "harpoon.h"
#include "tiles/submarine.h"

static UINT8 harpoon_x;
static UINT8 harpoon_y;
static Direction harpoon_dir;

static UINT8 harpoon_frame = 0;
static UINT8 harpoon_flip = 0;
static UINT8 harpoon_active = 0;
static UINT8 harpoon_anim_delay = 0;
#define HARPOON_DELAY_FRAMES 6

void harpoon_start(UINT8 x, UINT8 y, Direction dir) {
    harpoon_x = x;
    harpoon_y = y;
    harpoon_dir = dir;
    harpoon_frame = 0;
    harpoon_flip = 0;
    harpoon_anim_delay = 0;
    harpoon_active = 1;
}

void harpoon_animate(void) {
    if (!harpoon_active || harpoon_frame >= 4) return;

    if (harpoon_anim_delay < HARPOON_DELAY_FRAMES) {
        harpoon_anim_delay++;
        return;
    }

    harpoon_anim_delay = 0; // reset delay after animating

    UINT8 flip_flag = harpoon_flip ? S_FLIPY : 0;

    for (UINT8 i = 0; i < harpoon_frame; i++) {
        UINT8 sprite_id = HARPOON_SPRITE_START + i;
        set_sprite_tile(sprite_id, 2);
        set_sprite_prop(sprite_id, flip_flag);
        move_sprite(sprite_id, harpoon_x + harpoon_dir * (i * 8), harpoon_y);
    }

    UINT8 hook_index = HARPOON_SPRITE_START + harpoon_frame;
    set_sprite_tile(hook_index, 3);
    set_sprite_prop(hook_index, flip_flag);
    move_sprite(hook_index, harpoon_x + harpoon_dir * (harpoon_frame * 8), harpoon_y);

    harpoon_frame++;
    harpoon_flip ^= 1;

    if (harpoon_frame >= 4) {
        harpoon_active = 0;
    }
}


void harpoon_hide(void) {
    for (UINT8 i = 0; i <= HARPOON_SEGMENTS; i++) {
        move_sprite(HARPOON_SPRITE_START + i, 0, 160); // move offscreen
    }
}
