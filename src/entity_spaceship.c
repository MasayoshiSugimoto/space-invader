#include "entity_spaceship.h"


void entity_spaceship_fire(struct Game* game) {
  EntityId entity_id = game->spaceship_id;
  struct EntitySystem* entity_system = game->entity_system;
  struct SpriteComponent* sprite_component = &entity_system->sprite_component;

  struct Vector spaceship_position = entity_system_get_coordinates(entity_system, entity_id);
  const struct Sprite* sprite = sprite_get_sprite(sprite_component->sprite_id[entity_id]);
  struct Vector bullet_position = {
    spaceship_position.x + sprite->width / 2,
    spaceship_position.y
  };

  entity_system_set_coordinates(entity_system, 8, bullet_position);
  sprite_component_set_active(entity_system, 8, true);
}
