#include "main_system_game.h"


struct RenderingUnit {
  const struct Sprite* sprite;
  EntityId entity_id;
  struct VirtualWindow* window;
  int x;
  int y;
};


static struct VirtualWindow* _game_screen;
static struct RenderingUnit _rendering_units[ENTITY_MAX];
static int _rendering_unit_count;
const struct EntityData _entity_datas[] = {
  {{37, 16}, SPRITE_ID_SPACESHIP, true, FACTION_ID_PLAYER, SPRITE_LOADER_FILE_NAME_SPACESHIP},
  {{10, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN, SPRITE_LOADER_FILE_NAME_ALIEN},
  {{17, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN, SPRITE_LOADER_FILE_NAME_ALIEN},
  {{24, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN, SPRITE_LOADER_FILE_NAME_ALIEN},
  {{31, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN, SPRITE_LOADER_FILE_NAME_ALIEN},
  {{38, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN, SPRITE_LOADER_FILE_NAME_ALIEN},
  {{45, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN, SPRITE_LOADER_FILE_NAME_ALIEN},
  {{52, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN, SPRITE_LOADER_FILE_NAME_ALIEN},
};


static void _init_local(void) {
    memset(&_rendering_units, 0, sizeof(_rendering_units));
    _rendering_unit_count = 0;
    window_manager_init();
    _game_screen = window_manager_window_new(SCREEN_WIDTH, SCREEN_HEIGHT);
    _game_screen->has_border = true;
}


static void _init(void) {
    _init_local();
    game_init();
    game_init_entities(_entity_datas, array_size(_entity_datas));
    // _entities_to_window(_game.entity_system);
}


void _space_ship_fire(KeyboardKey key) {
    entity_spaceship_fire();
}


void _space_ship_move_left(KeyboardKey key) {
    struct Vector v = {-1, 0};
    entity_system_add_coordinates(
        entity_system_get(),
        entity_spaceship_get_entity_id(),
        v
    );
}


void _space_ship_move_right(KeyboardKey key) {
    struct Vector v = {1, 0};
    entity_system_add_coordinates(
        entity_system_get(),
        entity_spaceship_get_entity_id(),
        v
    );
}


static struct InputMapping _input_mapping[] = {
  {KEY_LEFT, _space_ship_move_left},
  {KEY_RIGHT, _space_ship_move_right},
  {' ', _space_ship_fire},
  {'a', _space_ship_move_left},
  {'d', _space_ship_move_right},
};


static void _input_update(void) {
    KeyboardKey key = input_get();
    input_process(_input_mapping, array_size(_input_mapping), key);
}


static enum MainSystemModeStatus _system_update(void) {
    game_update();

    return MAIN_SYSTEM_MODE_RUNNING;
}


static void _render(void) {
    window_manager_window_center_screen_x(_game_screen);
    window_manager_window_center_screen_y(_game_screen);
    window_manager_window_draw(_game_screen);

    struct Vector top_left = {_game_screen->offset_x, _game_screen->offset_y};
    struct EntitySystem* entity_system = entity_system_get();
    for (int i = 0; i < ENTITY_MAX; i++) {
        struct SpriteComponentUnit sprite_unit = sprite_component_get(i);

        if (sprite_unit.sprite_id == SPRITE_ID_NONE || !sprite_unit.active) continue;
        const struct Sprite* sprite = sprite_get_sprite(sprite_unit.sprite_id);
        struct RenderingUnit* rendering_unit = &_rendering_units[i];
        if (rendering_unit->window == NULL) {
            rendering_unit->window = window_manager_window_new(WINDOW_MANAGER_WIDTH_MAX, WINDOW_MANAGER_HEIGHT_MAX);
        }
        struct VirtualWindow* window = rendering_unit->window;
        if (rendering_unit->sprite != sprite) {
            window_manager_window_set_sprite(window, sprite);
        }
        rendering_unit->entity_id = i;
        rendering_unit->sprite = sprite;
        struct Vector v = vector_add(entity_system->coordinates[rendering_unit->entity_id], top_left);
        window->offset_x = v.x;
        window->offset_y = v.y;
        window_manager_window_draw(window);
    }
    curs_set(CURSOR_VISIBILITY_INVISIBLE);
    virtual_screen_render();
}


struct MainSystemMode g_game_main_system_mode = {
    "MAIN_SYSTEM_MODE_GAME",
    &_init,
    &_input_update,
    &_system_update,
    &_render
};
