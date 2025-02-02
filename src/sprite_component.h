#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H


#include "entity_system.h"
#include "sprite_buffer.h"
#include "window_manager.h"
#include "game_screen.h"
#include "entity_system.h"


struct SpriteComponentUnit {
  EntityId entity_id;
  bool active;
  struct SpriteBuffer* sprite_buffer;
  struct VirtualWindow* window;
};


void sprite_component_init();
void sprite_component_setup(EntityId entity_id, struct SpriteBuffer* sprite_buffer);
void sprite_component_sprite_buffer_set(EntityId entity_id, struct SpriteBuffer* sprite_buffer);
bool sprite_component_is_active(EntityId entity_id);
void sprite_component_set_active(EntityId entity_id, bool active);
struct SpriteComponentUnit sprite_component_get(EntityId);
void sprite_component_set(const struct SpriteComponentUnit*);
void sprite_component_disable(EntityId entity_id);
void sprite_component_enable(EntityId entity_id);
void sprite_component_update(void);
void sprite_component_render(void);
const struct VirtualWindow* sprite_component_window_get(EntityId entity_id);
void sprite_component_container_set(const struct VirtualWindow* window);
void sprite_component_position_move(EntityId entity_id, struct Vector dv);
void sprite_component_position_set(EntityId entity_id, struct Vector v);
void sprite_component_z_set(EntityId entity_id, uint8_t z);


#endif
