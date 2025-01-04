#include "entity_spaceship.h"


void entity_spaceship_fire(void) {
  EntityId entity_id = entity_spaceship_get_entity_id();
  struct EntitySystem* entity_system = entity_system_get();

  struct Vector spaceship_position = entity_system_get_coordinates(entity_system, entity_id);
  enum SpriteId sprite_id = sprite_component_get_sprite_id(entity_id);
  const struct Sprite* sprite = sprite_get_sprite(sprite_id);
  struct Vector bullet_position = {
    spaceship_position.x + sprite->width / 2,
    spaceship_position.y
  };

  bullet_component_fire(entity_system, bullet_position);
}


EntityId entity_spaceship_get_entity_id(void) {
  // TODO: Find a better solution
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    const struct VirtualWindow2* window = sprite_component_window_get(entity_id);
    if (window == NULL) continue;
    if (strcmp(window->buffer->file_name, SPRITE_LOADER_FILE_NAME_SPACESHIP) == 0) {
      return entity_id;
    }
  }
  return ENTITY_MAX;
}


