#include "main_system_game.h"


const struct EntityData _entity_datas[] = {
    {
        .coordinates = {37, 18}, 
        .active = true, 
        .faction_id = FACTION_ID_PLAYER, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_SPACESHIP
    },
    {
        .coordinates = {10, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = true,
    },
    {
        .coordinates = {17, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = true,
    },
    {
        .coordinates = {24, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = true,
    },
    {
        .coordinates = {31, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = true,
    },
    {
        .coordinates = {38, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = true,
    },
    {
        .coordinates = {45, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = true,
    },
    {
        .coordinates = {52, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = true,
    },
};


static void _move_left(KeyboardKey key) {
    entity_spaceship_move_left();
}


static void _move_right(KeyboardKey key) {
    entity_spaceship_move_right();
}


static void _fire(KeyboardKey key) {
    entity_spaceship_fire();
}


static void _on_collision(EntityId entity_id) {
    log_info_f("Entity collided: entity_id=%zu", entity_id);
    collision_manager_deactivate(entity_id);
    if (bullet_component_is_active(entity_id)) {
        bullet_component_disable(entity_id);
    } else {
        animation_set(entity_id, ANIMATION_NAME_EXPLOSION);
    }
}


static void _init(void) {
    log_info("Initializing main game system.");
    sprite_loader_load_sprite_set(SPRITE_LOADER_SPRITE_SET_LEVEL_1);
    game_screen_init(SCREEN_WIDTH, SCREEN_HEIGHT);

    game_init();
    game_init_entities(_entity_datas, array_size(_entity_datas));
    for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
        collision_manager_set_collision_handler(entity_id, _on_collision);
    }

    color_reset();
}


static void _release(void) {
    log_info("Releasing main game system.");
    game_screen_release();
}


static struct InputMapping _input_mapping[] = {
  {KEY_LEFT, _move_left},
  {KEY_RIGHT, _move_right},
  {' ', _fire},
  {'a', _move_left},
  {'d', _move_right},
};


static void _input_update(void) {
   input_process(_input_mapping, array_size(_input_mapping), input_get());
}


static enum MainSystemModeStatus _system_update(void) {
    game_update();
    return MAIN_SYSTEM_MODE_RUNNING;
}


static void _render(void) {
    window_manager_cursor_hide();
    game_render();
    virtual_screen_render();
}


struct MainSystemMode g_game_main_system_mode = {
    "MAIN_SYSTEM_MODE_GAME",
    _init,
    _release,
    _input_update,
    _system_update,
    _render
};
