#include "entity_system.h"


static struct EntitySystem {
  EntityId next_entity;
  struct Vector coordinates[ENTITY_MAX];
  uint16_t friendly_ids[ENTITY_MAX];
  ArrayBit active_flags[ENTITY_MAX];
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
    _entity_system.coordinates[i] = VZERO;
    _entity_system.friendly_ids[i] = 0;
    array_bit_reset(&_entity_system.active_flags[i]);
  }
}


EntityId entity_system_create_entity(void) {
  for (int i = 0; i < ENTITY_MAX; i++) {
    EntityId entity_id = as_id(_entity_system.next_entity + i);
    _entity_system.next_entity = next_id(entity_id);
    array_bit_reset(&_entity_system.active_flags[entity_id]);
    entity_system_enable(entity_id);
    _entity_system.coordinates[entity_id] = VZERO;
    _entity_system.friendly_ids[i] = 0;
    return entity_id;
  }
  log_fatal("Cannot create entity: no open slot left.");
  return 0;
}


void entity_system_delete_entity(EntityId entity_id) {
  assert_entity_id(entity_id);
  array_bit_reset(&_entity_system.active_flags[entity_id]);
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
  entity_system_component_deactivate(entity_id, COMPONENT_ID_MASTER);
}


void entity_system_enable(EntityId entity_id) {
  entity_system_component_activate(entity_id, COMPONENT_ID_MASTER);
}


bool entity_system_is_active(EntityId entity_id) {
  assert_entity_id(entity_id);
  return array_bit_is_enabled(&_entity_system.active_flags[entity_id], COMPONENT_ID_MASTER);
}


void entity_system_set_friendly_id(EntityId entity_id, uint16_t friendly_id) {
  assert_entity_id(entity_id);
  _entity_system.friendly_ids[entity_id] = friendly_id;
}


uint16_t entity_system_get_friendly_id(EntityId entity_id) {
  assert_entity_id(entity_id);
  return _entity_system.friendly_ids[entity_id];
}


EntityId entity_system_get_by_friendly_id(uint16_t friendly_id) {
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (_entity_system.friendly_ids[entity_id] == friendly_id) return entity_id;
  }
  return ENTITY_MAX;
}


void entity_system_active_flags_reset_all(void) {
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    array_bit_reset(&_entity_system.active_flags[entity_id]);
  }
}


bool entity_system_component_is_active(EntityId entity_id, enum ComponentId component_id) {
  assert_entity_id(entity_id);
  return array_bit_is_enabled(&_entity_system.active_flags[entity_id], component_id);
}


void entity_system_component_activate(EntityId entity_id, enum ComponentId component_id) {
  assert_entity_id(entity_id);
  array_bit_enable(&_entity_system.active_flags[entity_id], component_id);
}


void entity_system_component_deactivate(EntityId entity_id, enum ComponentId component_id) {
  assert_entity_id(entity_id);
  array_bit_disable(&_entity_system.active_flags[entity_id], component_id);
}


void entity_system_component_active_flags_reset(EntityId entity_id) {
  assert_entity_id(entity_id);
  array_bit_reset(&_entity_system.active_flags[entity_id]);
}