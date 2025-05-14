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
        .z = 1,
    },
    {
        .friendly_id = FRIENDLY_ID_ANIMATION_FIRST_ANIMATION,
        .coordinates = {6, 4}, 
        .active = true,
        .faction_id = FACTION_ID_ALIEN,
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN,
        .is_basic_ai_active = false,
        .animation_name = ANIMATION_NAME_EXPLOSION,
        .animation_auto_start = true,
    },
    {
        .coordinates = {12, 4}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN, 
        .is_basic_ai_active = false,
        .animation_name = ANIMATION_NAME_EXPLOSION,
        .animation_auto_start = true,
    },
    {
        .coordinates = {18, 4}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN, 
        .is_basic_ai_active = false,
        .animation_name = ANIMATION_NAME_EXPLOSION,
        .animation_auto_start = true,
    },
};
static int _screen_width = 25;
static int _screen_height = 10;


static void _init(void) {
    log_info("Initializing animation test.");
    sprite_loader_load_sprite_set(SPRITE_LOADER_SPRITE_SET_LEVEL_1);
    
    game_init();
    game_init_entities(_entity_datas, array_size(_entity_datas));
    game_screen_init(_screen_width, _screen_height);
    game_is_game_over_update_set(false);
    enemy_ai_basic_margin_from_border_set(0);
}


static void _release(void) {
    log_info("Releasing animation test.");
    game_screen_release();
}


static void _input_update(void) {

}


static enum MainSystemModeStatus _system_update(void) {
    game_update();
    EntityId entity_id = entity_system_get_by_friendly_id(FRIENDLY_ID_ANIMATION_FIRST_ANIMATION);
    if (entity_id != ENTITY_ID_INVALID && animation_is_done(entity_id)) {
        log_info("Animation system shutdown...");
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
