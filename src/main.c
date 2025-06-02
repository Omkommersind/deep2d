#include <gb/gb.h>
#include "game/entities/submarine.h"
#include "game/entities/harpoon.h"
#include "game/world/background.h"

void main(void) {
    DISPLAY_ON;
    SHOW_SPRITES;
    SHOW_BKG;

    submarine_init();
    submarine_draw(40, 80);

    while (1) {
        UINT8 joy = joypad();
        submarine_handle_input(joy);
        submarine_update();
        wait_vbl_done();
    }
}