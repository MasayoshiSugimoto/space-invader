#include "entity_spaceship.h"


void entity_spaceship_fire(void) {
  log_info("Entity spaceship fire event.");
  EntityId entity_id = entity_spaceship_get_entity_id();
  if (!sprite_component_is_active(entity_id)) return;
  const struct VirtualWindow* window = sprite_component_window_get(entity_id);
  if (window == NULL) return;
  struct Vector spaceship_position = entity_system_get_coordinates(entity_id);
  struct Vector bullet_position = {
    spaceship_position.x,
    spaceship_position.y
  };
  bullet_component_fire(bullet_position);
}


EntityId entity_spaceship_get_entity_id(void) {
  return entity_system_get_by_friendly_id(FRIENDLY_ID_SPACESHIP);
}


void entity_spaceship_move_left(void) {
  log_info("Entity spaceship move left event.");
  struct Vector dv = {-1, 0};
  EntityId entity_id = entity_spaceship_get_entity_id();
  struct Vector v = entity_system_get_coordinates(entity_id);
  sprite_component_position_move(entity_id, dv);
  if (!window_manager_window_is_inside_window_completely(sprite_component_window_get(entity_id), game_screen_get())) {
    sprite_component_position_set(entity_id, v);
  }
}


void entity_spaceship_move_right(void) {
  log_info("Entity spaceship move right event.");
  struct Vector dv = {1, 0};
  EntityId entity_id = entity_spaceship_get_entity_id();
  struct Vector v = entity_system_get_coordinates(entity_id);
  sprite_component_position_move(entity_id, dv);
  if (!window_manager_window_is_inside_window_completely(sprite_component_window_get(entity_id), game_screen_get())) {
    sprite_component_position_set(entity_id, v);
  }
}