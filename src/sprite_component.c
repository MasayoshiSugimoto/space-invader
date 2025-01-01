#include "sprite_component.h"


struct SpriteComponent {
  bool active[ENTITY_MAX];
  enum SpriteId sprite_id[ENTITY_MAX];
  struct SpriteBuffer* sprite_buffer[ENTITY_MAX];
} _sprite_component;


void sprite_component_init() {
  for (int i = 0; i < ENTITY_MAX; i++) {
    _sprite_component.sprite_id[i] = SPRITE_ID_NONE;
    _sprite_component.active[i] = false;
    _sprite_component.sprite_buffer[i] = NULL;
  }
}


void sprite_component_setup_deprecated(EntityId entity_id, enum SpriteId sprite_id) {
  assert_entity_id(entity_id);
  _sprite_component.sprite_id[entity_id] = sprite_id;
  _sprite_component.active[entity_id] = false;
  _sprite_component.sprite_buffer[entity_id] = NULL;
}


void sprite_component_setup(EntityId entity_id, struct SpriteBuffer* sprite_buffer) {
  assert_entity_id(entity_id);
  _sprite_component.active[entity_id] = false;
  _sprite_component.sprite_id[entity_id] = SPRITE_ID_NONE;
  _sprite_component.sprite_buffer[entity_id] = sprite_buffer;
}


enum SpriteId sprite_component_get_sprite_id(EntityId entity_id) {
  assert_entity_id(entity_id);
  return _sprite_component.sprite_id[entity_id];
}


bool sprite_component_is_active(EntityId entity_id) {
  assert_entity_id(entity_id);
  if (!_sprite_component.active[entity_id]) {
    return false;
  }
  if (_sprite_component.sprite_id[entity_id] == ENTITY_MAX && _sprite_component.sprite_buffer == NULL) {
    return false;
  }
  return true;
}


void sprite_component_set_active(EntityId entity_id, bool active) {
  assert_entity_id(entity_id);
  _sprite_component.active[entity_id] = active;
}


struct SpriteComponentUnit sprite_component_get(EntityId entity_id) {
  assert_entity_id(entity_id);
  struct SpriteComponentUnit unit = {
    entity_id,
    _sprite_component.active[entity_id],
    _sprite_component.sprite_id[entity_id],
    _sprite_component.sprite_buffer[entity_id]
  };
  return unit;
}


void sprite_component_set(const struct SpriteComponentUnit* unit) {
  assert_entity_id(unit->entity_id);
  _sprite_component.active[unit->entity_id] = unit->active;
  _sprite_component.sprite_id[unit->entity_id] = unit->sprite_id;
  _sprite_component.sprite_buffer[unit->entity_id] = unit->sprite_buffer;
}


void sprite_component_disable(EntityId entity_id) {
  assert_entity_id(entity_id);
  _sprite_component.active[entity_id] = false;
  _sprite_component.sprite_id[entity_id] = SPRITE_ID_NONE;
  _sprite_component.sprite_buffer[entity_id] = NULL;
}
