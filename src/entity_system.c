#include "entity_system.h"
#include "sprite_component.h"


EntityId next_id(EntityId id) {
  return (id + 1) % ENTITY_MAX;
}


EntityId as_id(EntityId id) {
  return id % ENTITY_MAX;
}


struct EntitySystem* entity_system_create() {
  return malloc(sizeof(struct EntitySystem));
}

void entity_system_init(struct EntitySystem* entity_system) {
  entity_system->next_entity = 0;
  for (int i = 0; i < ENTITY_MAX; i++) {
    entity_system->active[i] = false;
    entity_system->coordinates[i] = VZERO;
  }
}


EntityId entity_system_create_entity(struct EntitySystem* entity_system) {
  for (int i = 0; i < ENTITY_MAX; i++) {
    EntityId entity_id = as_id(entity_system->next_entity + i);
    if (!entity_system->active[entity_id]) {
      entity_system->next_entity = next_id(entity_id);
      entity_system->active[entity_id] = true;
      entity_system->coordinates[entity_id] = VZERO;
      sprite_component_setup(entity_id, SPRITE_ID_NONE);
      return entity_id;
    }
  }
  log_fatal("Cannot create entity: no open slot left.");
  return 0;
}


void entity_system_delete_entity(
    struct EntitySystem* entity_system,
    EntityId entity_id
) {
  assert_entity_id(entity_id);
  entity_system->active[entity_id] = false;
}


struct Vector entity_system_get_coordinates(
    const struct EntitySystem* entity_system,
    EntityId entity_id
) {
  assert_entity_id(entity_id);
  return entity_system->coordinates[entity_id];
}


void entity_system_set_coordinates(
    struct EntitySystem* entity_system,
    EntityId entity_id,
    struct Vector coordinates
) {
  assert_entity_id(entity_id);
  entity_system->coordinates[entity_id] = coordinates;
}


void entity_system_add_coordinates(
    struct EntitySystem* entity_system,
    EntityId entity_id,
    struct Vector delta
) {
  assert_entity_id(entity_id);
  entity_system->coordinates[entity_id] = vector_add(entity_system->coordinates[entity_id], delta);
}


void entity_system_disable(struct EntitySystem* entity_system, EntityId entity_id) {
  assert_entity_id(entity_id);
  entity_system->active[entity_id] = false;
}
