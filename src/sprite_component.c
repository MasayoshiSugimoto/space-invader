#include "sprite_component.h"


struct SpriteComponent {
  bool active[ENTITY_MAX];
  enum SpriteId sprite_id[ENTITY_MAX];
} sprite_component;


void sprite_component_init() {
  for (int i = 0; i < ENTITY_MAX; i++) {
    sprite_component.sprite_id[i] = SPRITE_ID_NONE;
    sprite_component.active[i] = false;
  }
}


void sprite_component_setup(EntityId entity_id, enum SpriteId sprite_id) {
  assert_entity_id(entity_id);
  sprite_component.sprite_id[entity_id] = sprite_id;
  sprite_component.active[entity_id] = false;
}


enum SpriteId sprite_component_get_sprite_id(EntityId entity_id) {
  assert_entity_id(entity_id);
  return sprite_component.sprite_id[entity_id];
}


bool sprite_component_is_active(EntityId entity_id) {
  assert_entity_id(entity_id);
  return sprite_component.sprite_id[entity_id] < ENTITY_MAX
    && sprite_component.active[entity_id];
}


void sprite_component_set_active(EntityId entity_id, bool active) {
  assert_entity_id(entity_id);
  sprite_component.active[entity_id] = active;
}


struct SpriteComponentUnit sprite_component_get(EntityId entity_id) {
  assert_entity_id(entity_id);
  struct SpriteComponentUnit unit = {
    entity_id,
    sprite_component.active[entity_id],
    sprite_component.sprite_id[entity_id]
  };
  return unit;
}


void sprite_component_set(const struct SpriteComponentUnit* unit) {
  assert_entity_id(unit->entity_id);
  sprite_component.active[unit->entity_id] = unit->active;
  sprite_component.sprite_id[unit->entity_id] = unit->sprite_id;
}
