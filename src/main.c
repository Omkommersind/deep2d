#include <gb/gb.h>
#include "submarine.h"

void main(void) {
    DISPLAY_ON;
    SHOW_SPRITES;

    submarine_init();
    submarine_draw(40, 72);

    while (1) {
        wait_vbl_done();
        // You can move submarine here if you want
    }
}
