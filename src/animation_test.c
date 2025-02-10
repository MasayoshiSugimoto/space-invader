#include "animation_test.h"


enum FriendlyIdAnimation {
    FRIENDLY_ID_ANIMATION_NONE,
    FRIENDLY_ID_ANIMATION_FIRST_ANIMATION
};


static const struct EntityData _entity_datas[] = {
    {
        .coordinates = {6, 4}, 
        .active = true,
        .faction_id = FACTION_ID_ALIEN,
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = false,
        .z = 1
    },
    {
        .friendly_id = FRIENDLY_ID_ANIMATION_FIRST_ANIMATION,
        .coordinates = {6, 4}, 
        .active = true,
        .faction_id = FACTION_ID_ALIEN,
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = false,
        .animation_name = ANIMATION_NAME_EXPLOSION
    },
    {
        .coordinates = {12, 4}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN, 
        .is_basic_ai_active = false,
        .animation_name = ANIMATION_NAME_EXPLOSION
    },
    {
        .coordinates = {18, 4}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN, 
        .is_basic_ai_active = false,
        .animation_name = ANIMATION_NAME_EXPLOSION
    },
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
    sprite_loader_load_sprite_set(SPRITE_LOADER_SPRITE_SET_LEVEL_1);
    
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
    game_screen_release();
}


static void _input_update(void) {

}


static enum MainSystemModeStatus _system_update(void) {
    game_update();
    EntityId entity_id = entity_system_get_by_friendly_id(FRIENDLY_ID_ANIMATION_FIRST_ANIMATION);
    if (entity_id != ENTITY_ID_INVALID && animation_is_done(entity_id)) {
        return MAIN_SYSTEM_MODE_DONE;
    }
    return MAIN_SYSTEM_MODE_RUNNING;
}


static void _render(void) {
    curs_set(CURSOR_VISIBILITY_INVISIBLE);
    game_render();
    virtual_screen_render();
}


struct MainSystemMode g_animation_test = {
    "MAIN_SYSTEM_MODE_ANIMATION_TEST",
    &_init,
    &_release,
    &_input_update,
    &_system_update,
    &_render
};
