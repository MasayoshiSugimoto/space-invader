#include "collision_manager_test.h"


enum FRIENDLY_ID {
    NONE,
    FRIENDLY_ID_SPACESHIP_1,
    FRIENDLY_ID_SPACESHIP_2,
    FRIENDLY_ID_SPACESHIP_3,
    FRIENDLY_ID_SPACESHIP_4,
    FRIENDLY_ID_SPACESHIP_5,
    FRIENDLY_ID_ALIEN,
    FRIENDLY_ID_MAX
};


static const int _screen_width = 25;
static const int _screen_height = 10;
static const struct Color BLACK = {0, 0, 0};
static const struct Color RED = {255, 0, 0};
static const struct Color WHITE = {255, 255, 255};
static ColorPairId _color_pair_id_white;
static ColorPairId _color_pair_id_red;
static const struct EntityData _entity_datas[] = {
    {
        .coordinates = {12, 5},
        .active = true, 
        .faction_id = FACTION_ID_PLAYER,
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_SPACESHIP, 
        .is_basic_ai_active = false,
        .friendly_id = FRIENDLY_ID_SPACESHIP_1,
    },
    {
        .coordinates = {2, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN, 
        .is_basic_ai_active = true,
        .friendly_id = FRIENDLY_ID_ALIEN,
    },
    {
        .coordinates = {0, 0}, 
        .active = true, 
        .faction_id = FACTION_ID_PLAYER, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_SPACESHIP, 
        .friendly_id = FRIENDLY_ID_SPACESHIP_2,
    },
    {
        .coordinates = {_screen_width, 0}, 
        .active = true, 
        .faction_id = FACTION_ID_PLAYER, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_SPACESHIP, 
        .friendly_id = FRIENDLY_ID_SPACESHIP_3,
    },
    {
        .coordinates = {_screen_width, _screen_height}, 
        .active = true, 
        .faction_id = FACTION_ID_PLAYER, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_SPACESHIP, 
        .friendly_id = FRIENDLY_ID_SPACESHIP_4,
    },
    {
        .coordinates = {0, _screen_height}, 
        .active = true, 
        .faction_id = FACTION_ID_PLAYER, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_SPACESHIP, 
        .friendly_id = FRIENDLY_ID_SPACESHIP_5,
    },
};



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
    {
        EntityId alien_entity_id = entity_system_get_by_friendly_id(FRIENDLY_ID_ALIEN);
        if (!window_manager_window_is_inside_window(sprite_component_window_get(alien_entity_id), game_screen_get())) {
            return MAIN_SYSTEM_MODE_DONE;
        }
        struct SpriteComponentUnit sprite_component = sprite_component_get(alien_entity_id);
        if (sprite_component.sprite_buffer != NULL) {
            if (collision_manager_is_collision(alien_entity_id)) {
                sprite_buffer_color_fill(sprite_component.sprite_buffer, _color_pair_id_red);
            } else {
                sprite_buffer_color_fill(sprite_component.sprite_buffer, _color_pair_id_white);
            }
        }
    }
    bool is_collision_ship = false;
    for (int i = FRIENDLY_ID_SPACESHIP_1; i <= FRIENDLY_ID_SPACESHIP_5; i++) {
        EntityId entity_id = entity_system_get_by_friendly_id(i);
        struct SpriteComponentUnit sprite_component = sprite_component_get(entity_id);
        if (sprite_component.sprite_buffer == NULL) continue;
        if (collision_manager_is_collision(entity_id)) {
            is_collision_ship = true;
            break;
        }
    }
    EntityId entity_id = entity_system_get_by_friendly_id(FRIENDLY_ID_SPACESHIP_1);
    struct SpriteComponentUnit sprite_component = sprite_component_get(entity_id);
    if (is_collision_ship) {
        sprite_buffer_color_fill(sprite_component.sprite_buffer, _color_pair_id_red);
    } else {
        sprite_buffer_color_fill(sprite_component.sprite_buffer, _color_pair_id_white);
    }
    return MAIN_SYSTEM_MODE_RUNNING;
}


static void _render(void) {
    curs_set(CURSOR_VISIBILITY_INVISIBLE);
    game_render();
    virtual_screen_render();
}


struct MainSystemMode g_collision_manager_test = {
    "MAIN_SYSTEM_MODE_GAME",
    &_init,
    &_release,
    &_input_update,
    &_system_update,
    &_render
};
