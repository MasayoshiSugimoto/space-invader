#include "entity_spaceship.h"


#define ENTITY_SPACESHIP_BULLET_COUNT 3


static EntityId _bullets[ENTITY_SPACESHIP_BULLET_COUNT];


void entity_spaceship_init(void) {
  log_info("Entity spaceship initialization.");
  for (int i = 0; i < ENTITY_SPACESHIP_BULLET_COUNT; i++) {
    EntityId entity_id = entity_system_create_entity();
    _bullets[i] = entity_id;
    sprite_component_setup(entity_id, sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_SPACESHIP_BULLET));
  }
}


void entity_spaceship_fire(KeyboardKey key) {
  log_info("Entity spaceship fire event.");
  EntityId entity_id = entity_spaceship_get_entity_id();
  struct EntitySystem* entity_system = entity_system_get();
  if (!sprite_component_is_active(entity_id)) return;
  const struct VirtualWindow2* window = sprite_component_window_get(entity_id);
  if (window == NULL) return;
  struct Vector spaceship_position = entity_system_get_coordinates(entity_system, entity_id);
  struct Vector bullet_position = {
    spaceship_position.x + window->buffer->width / 2,
    spaceship_position.y
  };
  bullet_component_fire(bullet_position);
}


EntityId entity_spaceship_get_entity_id(void) {
  // TODO: Find a better solution
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    const struct VirtualWindow2* window = sprite_component_window_get(entity_id);
    if (window == NULL) continue;
    if (!sprite_component_is_active(entity_id)) continue;
    if (strcmp(window->buffer->file_name, SPRITE_LOADER_FILE_NAME_SPACESHIP) == 0) {
      return entity_id;
    }
  }
  return ENTITY_MAX;
}


void entity_spaceship_move_left(KeyboardKey key) {
  log_info("Entity spaceship move left event.");
  struct Vector dv = {-1, 0};
  EntityId entity_id = entity_spaceship_get_entity_id();
  struct Vector v = entity_system_get_coordinates(entity_system_get(), entity_id);
  sprite_component_position_move(entity_id, dv);
  if (!window_manager_window_is_inside_window_completely_2(sprite_component_window_get(entity_id), game_screen_get())) {
    sprite_component_position_set(entity_id, v);
  }
}


void entity_spaceship_move_right(KeyboardKey key) {
  log_info("Entity spaceship move right event.");
  struct Vector dv = {1, 0};
  EntityId entity_id = entity_spaceship_get_entity_id();
  struct Vector v = entity_system_get_coordinates(entity_system_get(), entity_id);
  sprite_component_position_move(entity_id, dv);
  if (!window_manager_window_is_inside_window_completely_2(sprite_component_window_get(entity_id), game_screen_get())) {
    sprite_component_position_set(entity_id, v);
  }
}