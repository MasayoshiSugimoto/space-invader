#include "entity_spaceship_test.h"


static struct RecuringFrameTimer _timer;
static const int _width = 21;
static const int _height = 20;


static const struct EntityData _entity_datas[] = {
  {
    .coordinates = {8, 16}, 
    .active = true, 
    .faction_id = FACTION_ID_PLAYER, 
    .sprite_file_name = SPRITE_LOADER_FILE_NAME_SPACESHIP, 
    .is_basic_ai_active = false
  },
};


static void _move_left(void) {
    entity_spaceship_move_left('a');
}


static void _move_right(void) {
    entity_spaceship_move_right('d');
}


static void _fire(void) {
    entity_spaceship_fire(' ');
}

static void (*_event_handlers[])(void) = {
    // Confirm that only 3 bullets can be fired at once.
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    _fire,
    // Check that the spaceship cannot go outside of the screen.
    _move_left,
    _move_left,
    _move_left,
    _move_left,
    _move_left,
    _move_left,
    _move_left,
    _move_left,
    _move_left,
    _move_left,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
    _move_right,
};
static int _event_counter;
  

static void _on_event(void* _) {
    _event_handlers[_event_counter % array_size(_event_handlers)]();
    _event_counter++;
}


static void _init(void) {
    log_info("Initializing entity spaceship test.");
    sprite_loader_load_sprite_set(SPRITE_LOADER_SPRITE_SET_LEVEL_1);
    game_screen_init(_width, _height);

    game_init();
    game_init_entities(_entity_datas, array_size(_entity_datas));

    color_reset();

    recurring_frame_timer_set(&_timer, _on_event, NULL, milliseconds_as_duration(100));
    _event_counter = 0;
}


static void _release(void) {
    log_info("Releasing entity spaceship test.");
    game_screen_release();
}


static void _input_update(void) {
    recurring_frame_timer_update(&_timer);
}


static enum MainSystemModeStatus _system_update(void) {
    if (_event_counter >= array_size(_event_handlers)) {
        return MAIN_SYSTEM_MODE_DONE;
    }
    game_update();
    return MAIN_SYSTEM_MODE_RUNNING;
}


static void _render(void) {
    window_manager_cursor_hide();
    game_render();
    virtual_screen_render();
}


struct MainSystemMode g_entity_spaceship_test = {
    "ENTITY_SPACESHIP",
    &_init,
    &_release,
    &_input_update,
    &_system_update,
    &_render
};
