#include "main_system_game.h"


const struct EntityData _entity_datas[] = {
    {
        .coordinates = {37, 16}, 
        .active = true, 
        .faction_id = FACTION_ID_PLAYER, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_SPACESHIP
    },
    {
        .coordinates = {10, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN
    },
    {
        .coordinates = {17, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN
    },
    {
        .coordinates = {24, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN
    },
    {
        .coordinates = {31, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN
    },
    {
        .coordinates = {38, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN
    },
    {
        .coordinates = {45, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN
    },
    {
        .coordinates = {52, 1}, 
        .active = true, 
        .faction_id = FACTION_ID_ALIEN, 
        .sprite_file_name = SPRITE_LOADER_FILE_NAME_ALIEN
    },
};


static void _init(void) {
    
}


static void _release(void) {
    log_info("Releasing main game system.");
    
}


void _space_ship_fire(KeyboardKey key) {
    
}


void _space_ship_move_left(KeyboardKey key) {
    
}


void _space_ship_move_right(KeyboardKey key) {
    
}


// static struct InputMapping _input_mapping[] = {
//   {KEY_LEFT, _space_ship_move_left},
//   {KEY_RIGHT, _space_ship_move_right},
//   {' ', _space_ship_fire},
//   {'a', _space_ship_move_left},
//   {'d', _space_ship_move_right},
// };


static void _input_update(void) {
   
}


static enum MainSystemModeStatus _system_update(void) {
    
    return MAIN_SYSTEM_MODE_RUNNING;
}


static void _render(void) {
    
}


struct MainSystemMode g_game_main_system_mode = {
    "MAIN_SYSTEM_MODE_GAME",
    _init,
    _release,
    _input_update,
    _system_update,
    _render
};
