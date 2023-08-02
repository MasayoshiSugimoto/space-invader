#include "entity_spaceship.h"


void entity_spaceship_fire(struct Game* game) {
  EntityId entity_id = game->spaceship_id;
  struct EntitySystem* entity_system = game->entity_system;

  struct Vector spaceship_position = entity_system_get_coordinates(entity_system, entity_id);
  enum SpriteId sprite_id = sprite_component_get_sprite_id(entity_id);
  const struct Sprite* sprite = sprite_get_sprite(sprite_id);
  struct Vector bullet_position = {
    spaceship_position.x + sprite->width / 2,
    spaceship_position.y
  };

  entity_system_set_coordinates(entity_system, 8, bullet_position);
  sprite_component_set_active(8, true);
}
