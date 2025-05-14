#include "main_system_sequence.h"


static struct MainSystemMode* _main_systems_test[] = {
    // &g_animation_test,
    &g_entity_spaceship_test,
    // &g_collision_manager_test,
    // &g_start_screen_main_system_mode
};
static struct SLICE__MainSystemMode_ptr _slice_main_systems_test = {
    _main_systems_test,
    array_size(_main_systems_test)
};
static struct MainSystemMode* g_main_system_sequence_list[] = {
    &g_start_screen_main_system_mode,
    &g_game_main_system_mode,
    &g_game_over_screen_main_system_mode,
};
static struct SLICE__MainSystemMode_ptr _slice_main_system_sequence = {
    g_main_system_sequence_list,
    array_size(g_main_system_sequence_list)
};
static struct SLICE__MainSystemMode_ptr* _slice_main_system = &_slice_main_systems_test;
static uint16_t _main_systems_index = 0;
static bool _increment = false;


static struct MainSystemMode* _main_system_get_active(void) {
    return *SLICE__MainSystemMode_ptr__get(_slice_main_system, _main_systems_index);
}


static void _init(void) {
    log_info("Initializing main system sequence.");
    (*SLICE__MainSystemMode_ptr__get(_slice_main_system, 0))->init();
}


static void _release(void) {
    log_info("Releasing main system sequence.");
    if (_main_systems_index < _slice_main_system->length) {
        _main_system_get_active()->release();
    }
}


static void _input_update(void) {
    // We swap the systems here because this function is called first and is in the appropriate timing.
    if (_increment) {
        _main_system_get_active()->release();
        event_on_system_release();
        _main_systems_index++;
        if (_main_systems_index >= _slice_main_system->length) {
            _increment = false;
            return;
        }
        event_on_system_start();
        _main_system_get_active()->init();
        _increment = false;
    }
    _main_system_get_active()->input_update();
}


static enum MainSystemModeStatus _system_update(void) {
    space_update();
    if (_main_systems_index >= _slice_main_system->length) {
        return MAIN_SYSTEM_MODE_DONE;
    }
    if (_main_system_get_active()->system_update() == MAIN_SYSTEM_MODE_DONE) {
        _increment = true;
    }
    return MAIN_SYSTEM_MODE_RUNNING;
}


static void _render(void) {
    _main_system_get_active()->render();
}


struct MainSystemMode g_main_system_sequence = {
    "MAIN_SYSTEM_SEQUENCE",
    &_init,
    &_release,
    &_input_update,
    &_system_update,
    &_render
};