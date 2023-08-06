#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H


#include "entity_system.h"


struct SpriteComponentUnit {
  EntityId entity_id;
  bool active;
  enum SpriteId sprite_id;
};


void sprite_component_init();
void sprite_component_setup(EntityId entity_id, enum SpriteId sprite_id);
enum SpriteId sprite_component_get_sprite_id(EntityId entity_id);
bool sprite_component_is_active(EntityId entity_id);
void sprite_component_set_active(EntityId entity_id, bool active);
struct SpriteComponentUnit sprite_component_get(EntityId);
void sprite_component_set(const struct SpriteComponentUnit*);
void sprite_component_disable(EntityId entity_id);


#endif
