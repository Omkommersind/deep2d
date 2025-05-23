#include "submarine.h"
#include "tiles/submarine.h"  // tile data

#define SUBMARINE_TILE_COUNT 4

// Base sprite index to use for submarine
#define SUBMARINE_SPRITE_START 0

void submarine_init(void) {
    set_sprite_data(SUBMARINE_SPRITE_START, SUBMARINE_TILE_COUNT, Submarine);
}

void submarine_draw(UINT8 x, UINT8 y) {
    // Assign tiles to sprite indices
    set_sprite_tile(SUBMARINE_SPRITE_START, 0);
    set_sprite_tile(SUBMARINE_SPRITE_START + 1, 1);
    set_sprite_tile(SUBMARINE_SPRITE_START + 2, 2);
    set_sprite_tile(SUBMARINE_SPRITE_START + 3, 3);

    // Position sprites side by side (8 pixels apart)
    move_sprite(SUBMARINE_SPRITE_START, x, y);
    move_sprite(SUBMARINE_SPRITE_START + 1, x + 8, y);
    move_sprite(SUBMARINE_SPRITE_START + 2, x + 16, y);
    move_sprite(SUBMARINE_SPRITE_START + 3, x + 24, y);
}

void submarine_move(UINT8 x, UINT8 y) {
    // Just reposition the submarine sprites
    for (UINT8 i = 0; i < SUBMARINE_TILE_COUNT; i++) {
        move_sprite(SUBMARINE_SPRITE_START + i, x + (i * 8), y);
    }
}

void submarine_hide(void) {
    for (UINT8 i = 0; i < SUBMARINE_TILE_COUNT; i++) {
        move_sprite(SUBMARINE_SPRITE_START + i, 0, 160);  // move offscreen
    }
}
