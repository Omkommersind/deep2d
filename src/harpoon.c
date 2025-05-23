#include "harpoon.h"
#include "tiles/submarine.h"

void harpoon_draw(UINT8 x, UINT8 y, Direction dir) {
    for (UINT8 i = 0; i < HARPOON_SEGMENTS; i++) {
        set_sprite_tile(HARPOON_SPRITE_START + i, 2); // rope
        move_sprite(
            HARPOON_SPRITE_START + i,
            x + dir * (i * 8),
            y
        );
    }

    // Hook
    set_sprite_tile(HARPOON_SPRITE_START + HARPOON_SEGMENTS, 3);
    move_sprite(
        HARPOON_SPRITE_START + HARPOON_SEGMENTS,
        x + dir * (HARPOON_SEGMENTS * 8),
        y
    );
}


void harpoon_hide(void) {
    for (UINT8 i = 0; i <= HARPOON_SEGMENTS; i++) {
        move_sprite(HARPOON_SPRITE_START + i, 0, 160); // move offscreen
    }
}
