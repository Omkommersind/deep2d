#include "harpoon.h"
#include "tiles/submarine.h"

void harpoon_draw(UINT8 x, UINT8 y, Direction dir) {
    // Draw 3 rope segments starting right at the sub's front
    for (UINT8 i = 0; i < HARPOON_SEGMENTS; i++) {
        UINT8 sprite_id = HARPOON_SPRITE_START + i;
        set_sprite_tile(sprite_id, 2); // rope tile
        move_sprite(sprite_id, x + dir * (i * 8), y);
    }

    // Hook at the end
    set_sprite_tile(HARPOON_SPRITE_START + HARPOON_SEGMENTS, 3); // hook tile
    move_sprite(HARPOON_SPRITE_START + HARPOON_SEGMENTS,
                x + dir * (HARPOON_SEGMENTS * 8), y);
}


void harpoon_hide(void) {
    for (UINT8 i = 0; i <= HARPOON_SEGMENTS; i++) {
        move_sprite(HARPOON_SPRITE_START + i, 0, 160); // move offscreen
    }
}
