#include <gb/gb.h>
#include "entities/submarine.h"
#include "entities/harpoon.h"

void main(void) {
    DISPLAY_ON;
    SHOW_SPRITES;

    submarine_init();
    submarine_draw(40, 72);
    harpoon_hide();

    while (1) {
        UINT8 joy = joypad();
        submarine_update(joy);

        wait_vbl_done();
    }
}
