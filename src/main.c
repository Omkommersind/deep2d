#include <gb/gb.h>
#include "game/entities/submarine.h"
#include "game/entities/harpoon.h"
#include "game/world/background.h"

void main(void) {
    DISPLAY_ON;
    SHOW_SPRITES;

    //background_gradient_fill();

    submarine_init();
    submarine_draw(40, 72);
    harpoon_hide();

    while (1) {
        UINT8 joy = joypad();
        submarine_update(joy);

        wait_vbl_done();
    }
}
