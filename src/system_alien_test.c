#include "system_alien_test.h"


static const struct EntityData _entity_datas[] = {
    {
        .coordinates = {10, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = false,
        .z = 1,
        .animation_name = ANIMATION_NAME_ALIEN,
        .animation_is_loop = true,
        .animation_auto_start = true,
    },
    {
        .coordinates = {17, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = false,
        .z = 1,
        .animation_name = ANIMATION_NAME_ALIEN,
        .animation_is_loop = true,
        .animation_auto_start = true,
    },
    {
        .coordinates = {24, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = false,
        .z = 1,
        .animation_name = ANIMATION_NAME_ALIEN,
        .animation_is_loop = true,
        .animation_auto_start = true,
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
    faction_component_disable(entity_id);
    if (bullet_component_is_active(entity_id)) {
        bullet_component_disable(entity_id);
    } else {
        animation_is_loop_set(entity_id, false);
        animation_set(entity_id, ANIMATION_NAME_EXPLOSION);
        animation_start(entity_id);
        sprite_component_z_set(entity_id, 0);
        enemy_ai_basic_disable(entity_id);
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
		game_is_game_over_update_set(false);
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
    if (game_game_over_result_get() != GAME_OVER_NONE && color_fade_is_done()) {
        log_info("GAME OVER");
        return MAIN_SYSTEM_MODE_DONE;
    }
    return MAIN_SYSTEM_MODE_RUNNING;
}


static void _render(void) {
    window_manager_cursor_hide();
    game_render();
    virtual_screen_render();
}


struct MainSystemMode g_system_alien_test = {
    "MAIN_SYSTEM_MODE_GAME",
    _init,
    _release,
    _input_update,
    _system_update,
    _render
};
