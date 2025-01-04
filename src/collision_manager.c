/********************************************************************************
 * This file manages collisions between entities.
 *
 * Collision will occur between sprites of opposite faction. We consider a sprite
 * to be equal to the collision box. When sprites overlap, we consider that
 * a collision has occured.
 *******************************************************************************/


#include "collision_manager.h"


uint8_t* _buffer;
int _width;
int _height;
bool _is_collisions[ENTITY_MAX];


int _collision_buffer_index(int x, int y) {
  return y * _width + x;
}


int _buffer_length_get(void) {
  return _width * _height;
}


bool _is_active_entity(struct EntitySystem* entity_system, EntityId entity_id) {
  if (!entity_system->active[entity_id]) return false;
  if (!sprite_component_is_active(entity_id)) return false;
  if (faction_component_faction_id_get(entity_id) == FACTION_ID_NEUTRAL) return false;
  if (faction_component_faction_id_get(entity_id) >= FACTION_ID_MAX) return false;
  return true;
}


void collision_manager_init(void) {
  _buffer = NULL;
  _width = 0;
  _height = 0;
  memset(_is_collisions, 0, ENTITY_MAX * sizeof(_is_collisions[0]));
}


void collision_manager_allocate(int width, int height) {
  _buffer = malloc(sizeof(_buffer[0]) * width * height);
  _width = width;
  _height = height;
}


void collision_manager_release(void) {
  assert(_buffer != NULL, "Collision manager has already been released.");
  free(_buffer);
  _width = 0;
  _height = 0;
  memset(_is_collisions, 0, ENTITY_MAX * sizeof(_is_collisions[0]));
}


void collision_manager_update(struct EntitySystem* entity_system) {
  // Cleanup the buffer
  for (int i = 0; i < _buffer_length_get(); i++) {
    _buffer[i] = 0;
  }

  // Iterate over all entities and mark the buffer flags based on entity's faction.
  uint8_t* buffer = _buffer;
  for (int i = 0; i < ENTITY_MAX; i++) {
    _is_collisions[i] = false;
    if (!_is_active_entity(entity_system, i)) continue;
    struct Vector v = entity_system_get_coordinates(entity_system, i);
    struct SpriteBuffer* sprite = sprite_component_get(i).sprite_buffer;
    for (int dy = 0; dy < sprite->height; dy++) {
      for (int dx = 0; dx < sprite->width; dx++) {
        buffer[_collision_buffer_index(v.x + dx, v.y + dy)] |= faction_component_faction_id_get(i);
      }
    }
  }
  // Iterate over all entities and compare their sprite buffer with the collision buffer.
  for (int i = 0; i < ENTITY_MAX; i++) {
    if (!_is_active_entity(entity_system, i)) continue;
    struct SpriteBuffer* sprite = sprite_component_get(i).sprite_buffer;
    struct Vector v = entity_system_get_coordinates(entity_system, i);
    for (int dy = 0; dy < sprite->height; dy++) {
      for (int dx = 0; dx < sprite->width; dx++) {
        if (buffer[_collision_buffer_index(v.x + dx, v.y + dy)] != faction_component_faction_id_get(i)) {
          _is_collisions[i] = true;
          break;
        }
      }
      if (_is_collisions[i]) break;
    }
  }
}


bool collision_manager_is_collision(EntityId entity_id) {
  assert_entity_id(entity_id);
  return _is_collisions[entity_id];
}
