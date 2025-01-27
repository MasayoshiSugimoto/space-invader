#include "game_screen.h"


static struct VirtualWindow _window;
static struct SpriteBuffer _buffer;


void game_screen_init(int width, int height) {
    log_info("Initializing game screen...");
    window_manager_window_init(&_window);
    _window.buffer = &_buffer;
    _window.has_border = true;
    sprite_buffer_init(&_buffer);
    sprite_buffer_allocate(&_buffer, width, height);
    sprite_buffer_clear(&_buffer);
    window_manager_window_center_screen_x(&_window);
    window_manager_window_center_screen_y(&_window);
}


void game_screen_release(void) {
    log_info("Releasing game screen...");
    sprite_buffer_free(&_buffer);
}


void game_screen_clear(void) {
    sprite_buffer_clear(&_buffer);
}


const struct VirtualWindow* game_screen_get(void) {
    return &_window;
}


void game_screen_render(void) {
    window_manager_window_draw(&_window);
}