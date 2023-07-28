#include "entity_system.h"


#define ENTITY_MAX 100


#define assert_entity_id(entity_id) { \
  if (entity_id >= ENTITY_MAX) log_fatal_f("Invalid entity id: %ld", entity_id); \
}


struct SpriteComponent {
  bool active[ENTITY_MAX];
  enum SpriteId sprite_id[ENTITY_MAX];
};


struct EntitySystem {
  EntityId next_entity;
  bool active[ENTITY_MAX];
  struct Vector coordinates[ENTITY_MAX];
  struct SpriteComponent sprite_component;
};


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
  for (int i = 0; i < ENTITY_MAX; i++) {
    entity_system->active[i] = false;
    entity_system->coordinates[i] = VZERO;

    entity_system->sprite_component.active[i] = false;
    entity_system->sprite_component.sprite_id[i] = SPRITE_ID_MAX;
  }
}


EntityId entity_system_create_entity(struct EntitySystem* entity_system) {
  for (int i = 0; i < ENTITY_MAX; i++) {
    EntityId entity_id = as_id(entity_system->next_entity + i);
    if (!entity_system->active[entity_id]) {
      entity_system->next_entity = next_id(entity_id);
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
    struct EntitySystem* entity_system,
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


void sprite_component_setup(
    struct EntitySystem* entity_system,
    EntityId entity_id,
    enum SpriteId sprite_id
) {
  assert_entity_id(entity_id);
  struct SpriteComponent* sprite_component = &entity_system->sprite_component;
  sprite_component->active[entity_id] = true;
  sprite_component->sprite_id[entity_id] = sprite_id;
}


enum SpriteId sprite_component_get_sprite_id(struct EntitySystem* entity_system, EntityId entity_id) {
  assert_entity_id(entity_id);
  struct SpriteComponent* sprite_component = &entity_system->sprite_component;
  if (!sprite_component->active[entity_id]) return SPRITE_ID_MAX;
  return sprite_component->sprite_id[entity_id];
}
