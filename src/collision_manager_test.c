#include "collision_manager_test.h"


static const struct EntityData _entity_datas[] = {
  {{10, 3}, SPRITE_ID_SPACESHIP, true, FACTION_ID_PLAYER, SPRITE_LOADER_FILE_NAME_SPACESHIP},
  {{0, 0}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN, SPRITE_LOADER_FILE_NAME_ALIEN},
};
static int _screen_width = 25;
static int _screen_height = 10;
static const struct Color BLACK = {0, 0, 0};
static const struct Color RED = {255, 0, 0};
static const struct Color WHITE = {255, 255, 255};
static ColorPairId _color_pair_id_white;
static ColorPairId _color_pair_id_red;


static void _init(void) {
    log_info("Initializing collision manager test.");
    game_init();
    game_init_entities(_entity_datas, array_size(_entity_datas));
    game_screen_init(_screen_width, _screen_height);
    enemy_ai_basic_margin_from_border_set(0);

    // Set color palette
    int color_palette_id = 1;
    color_reset();
    color_color_palette_activate(color_palette_id);
    ColorId black_id = color_color_palette_add(BLACK);
    ColorId white_id = color_color_palette_add(WHITE);
    ColorId red_id = color_color_palette_add(RED);
    color_color_palette_push(color_palette_id);
    _color_pair_id_white = color_color_pair_add(black_id, white_id);
    _color_pair_id_red = color_color_pair_add(black_id, red_id);
    color_color_pair_push();

    // Set sprite default color
    sprite_buffer_color_fill(sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_SPACESHIP), _color_pair_id_white);
    sprite_buffer_color_fill(sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_ALIEN), _color_pair_id_white);
}


static void _release(void) {
    log_info("Releasing collision manager test.");
}


static void _input_update(void) {

}


static enum MainSystemModeStatus _system_update(void) {
    game_update();
    for (int entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
        struct SpriteComponentUnit sprite_component = sprite_component_get(entity_id);
        if (sprite_component.sprite_buffer == NULL) continue;
        if (
            strcmp(sprite_component.sprite_buffer->file_name, SPRITE_LOADER_FILE_NAME_SPACESHIP) != 0
            && strcmp(sprite_component.sprite_buffer->file_name, SPRITE_LOADER_FILE_NAME_ALIEN) != 0
        ) continue;
        if (collision_manager_is_collision(entity_id)) {
            sprite_buffer_color_fill(sprite_component.sprite_buffer, _color_pair_id_red);
        } else {
            sprite_buffer_color_fill(sprite_component.sprite_buffer, _color_pair_id_white);
        }
        // Exit when the alien is out of the screen.
        if (
            strcmp(sprite_component.sprite_buffer->file_name, SPRITE_LOADER_FILE_NAME_ALIEN) == 0
            && !window_manager_window_is_inside_window_2(sprite_component_window_get(entity_id), game_screen_get())
        ) {
            return MAIN_SYSTEM_MODE_DONE;
        }
    }
    return MAIN_SYSTEM_MODE_RUNNING;
}


static void _render(void) {
    curs_set(CURSOR_VISIBILITY_INVISIBLE);
    game_render();
}


struct MainSystemMode g_collision_manager_test = {
    "MAIN_SYSTEM_MODE_GAME",
    &_init,
    &_release,
    &_input_update,
    &_system_update,
    &_render
};
