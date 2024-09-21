#include "virtual_screen_test.h"


static const struct Color BLACK = {0, 0, 0};
static const struct Color RED = {255, 0, 0};
static const struct Color GREEN = {0, 255, 0};
static const struct Color BLUE = {0, 0, 255};
static const struct Color MAGENTA = {255, 0, 255};
static const struct Color WHITE = {255, 255, 255};


void virtual_screen_test() {
    log_info("TEST: virtual_screen_test");
    struct Terminal terminal;
    terminal_init(&terminal);

    color_init();

    color_color_palette_activate(0);
    ColorId black_id = color_color_palette_add(BLACK);
    ColorId white_id = color_color_palette_add(WHITE);
    ColorId red_id = color_color_palette_add(RED);
    ColorId green_id = color_color_palette_add(GREEN);
    ColorId blue_id = color_color_palette_add(BLUE);
    ColorId magenta_id = color_color_palette_add(MAGENTA);

    color_color_pair_add(black_id, white_id);  // 1
    color_color_pair_add(black_id, red_id);  // 2
    color_color_pair_add(black_id, green_id);  // 3
    color_color_pair_add(black_id, blue_id);  // 4
    color_color_pair_add(black_id, magenta_id);  // 5
    color_color_pair_add(white_id, black_id);  // 6
    color_color_pair_add(white_id, red_id);  // 7
    color_color_pair_add(white_id, green_id);  // 8
    color_color_pair_add(white_id, blue_id);  // 9
    color_color_pair_add(white_id, magenta_id);  // 10
    color_color_pair_push();

    int color_pair_id_max = 10;
    const char* characters = "abcdefghijklmnopqrstuvwxyz";

    virtual_screen_init();
    virtual_screen_setup();
    erase();
    virtual_screen_set_string(0, 0, "TEST VIRTUAL SCREEN");
    virtual_screen_set_string(0, 1, "===================");
    virtual_screen_set_string(0, 3, "Fill the screen which characters. One color per character.");

    int width = virtual_screen_get_width();
    int height = virtual_screen_get_height();
    int y_offset = width * 5;  // reserve 3 lines for explanation text.
    for (int x = y_offset; x < width * height; x++) {
        int i = x % strlen(characters);
        virtual_screen_set_char_and_color(x % width, x / width, characters[i], (i % color_pair_id_max) + 8);
    }
    virtual_screen_render();
    refresh();
    sleep(5/*seconds*/);
    endwin();
}