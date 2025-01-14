#include "entity_system.h"


static struct EntitySystem {
  EntityId next_entity;
  bool active[ENTITY_MAX];
  struct Vector coordinates[ENTITY_MAX];
} _entity_system;


EntityId next_id(EntityId id) {
  return (id + 1) % ENTITY_MAX;
}


EntityId as_id(EntityId id) {
  return id % ENTITY_MAX;
}


void entity_system_init(void) {
  log_info("Initializing entity system.");
  _entity_system.next_entity = 0;
  for (int i = 0; i < ENTITY_MAX; i++) {
    _entity_system.active[i] = false;
    _entity_system.coordinates[i] = VZERO;
  }
}


EntityId entity_system_create_entity(void) {
  for (int i = 0; i < ENTITY_MAX; i++) {
    EntityId entity_id = as_id(_entity_system.next_entity + i);
    if (!_entity_system.active[entity_id]) {
      _entity_system.next_entity = next_id(entity_id);
      _entity_system.active[entity_id] = true;
      _entity_system.coordinates[entity_id] = VZERO;
      return entity_id;
    }
  }
  log_fatal("Cannot create entity: no open slot left.");
  return 0;
}


void entity_system_delete_entity(EntityId entity_id) {
  assert_entity_id(entity_id);
  _entity_system.active[entity_id] = false;
}


struct Vector entity_system_get_coordinates(EntityId entity_id) {
  assert_entity_id(entity_id);
  return _entity_system.coordinates[entity_id];
}


void entity_system_set_coordinates(EntityId entity_id, struct Vector coordinates) {
  assert_entity_id(entity_id);
  _entity_system.coordinates[entity_id] = coordinates;
}


void entity_system_add_coordinates(EntityId entity_id, struct Vector delta) {
  assert_entity_id(entity_id);
  _entity_system.coordinates[entity_id] = vector_add(_entity_system.coordinates[entity_id], delta);
}


void entity_system_disable(EntityId entity_id) {
  assert_entity_id(entity_id);
  _entity_system.active[entity_id] = false;
}


bool entity_system_is_active(EntityId entity_id) {
  assert_entity_id(entity_id);
  return _entity_system.active[entity_id];
}