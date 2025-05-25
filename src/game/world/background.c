#include <gb/gb.h>
#include "background.h"
#include "../../tiles/fills.h"

static const UINT8 solid_tiles[] = {0, 2, 4, 6};
static const UINT8 transition_tiles[] = {1, 3, 5};

void draw_gradient(UINT8 x, UINT8 y, UINT8 width, UINT8 height) {
    static const UINT8 solid_tiles[]     = {0, 2, 4, 6};
    static const UINT8 transition_tiles[] = {1, 3, 5};

    if (height < 7) return; // not enough space for all sections cleanly

    UINT8 base_solid_height = (height - 3) / 4;
    UINT8 extra_rows = (height - 3) % 4;

    UINT8 current_y = y;

    for (UINT8 section = 0; section < 4; section++) {
        UINT8 rows = base_solid_height;

        // Distribute leftover rows
        if (extra_rows > 0) {
            rows += 1;
            extra_rows--;
        }

        // ✅ Ensure we draw at least 1 row for each solid section
        if (rows == 0) rows = 1;

        // Draw solid rows
        for (UINT8 i = 0; i < rows; i++) {
            UINT8 tile = solid_tiles[section];
            for (UINT8 col = 0; col < width; col++) {
                set_bkg_tiles(x + col, current_y, 1, 1, &tile);
            }
            current_y++;
        }

        // Draw transition tile (only between solid sections)
        if (section < 3 && current_y - y < height) {
            UINT8 tile = transition_tiles[section];
            for (UINT8 col = 0; col < width; col++) {
                set_bkg_tiles(x + col, current_y, 1, 1, &tile);
            }
            current_y++;
        }
    }
}

void background_gradient_fill(void) {
    set_bkg_data(0, 7, Fills);
    draw_gradient(0, 0, 20, 18); 
    SHOW_BKG;
}
