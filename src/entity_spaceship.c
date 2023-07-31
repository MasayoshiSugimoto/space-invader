#include "entity_spaceship.h"


EntityId entity_spaceship_create(struct EntitySystem* entity_system) {
  EntityId id = entity_system_create_entity(entity_system);
  sprite_component_setup(entity_system, id, SPRITE_ID_ALIEN);
  return id;
}
