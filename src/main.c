#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>

void main(void) {
    // Set default grayscale-like palette (does nothing on GBC without tiles but is safe)
    BGP_REG = 0xE4;

    // Simple "Hello" message
    printf("Hello, deep2d!");

    // Game loop
    while (1) {
        wait_vbl_done();
    }
}
