/********************************************************************************
 * This file manages collisions between entities.
 *
 * Collision will occur between sprites of opposite faction. We consider a sprite
 * to be equal to the collision box. When sprites overlap, we consider that
 * a collision has occured.
 *******************************************************************************/


#include "collision_manager.h"


static uint8_t* _buffer;
static int _width;
static int _height;
static bool _is_collisions[ENTITY_MAX];
static void (*_on_collision[ENTITY_MAX])(EntityId entity_id);


static void _no_op(EntityId entity_id) {
  // Do nothing
}


int _collision_buffer_index(int x, int y) {
  assert(0 <= x && x < _width, "x too big or negative");
  assert(0 <= y && y < _height, "y too big or negative");
  return y * _width + x;
}


int _buffer_length_get(void) {
  return _width * _height;
}


bool _is_active_entity(EntityId entity_id) {
  if (!entity_system_is_active(entity_id)) return false;
  if (!entity_system_component_is_active(entity_id, COMPONENT_ID_COLLISION)) return false;
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
  for (int i = 0; i < ENTITY_MAX; i++) {
    _on_collision[i] = _no_op;
  }
}


void collision_manager_allocate(int width, int height) {
  _buffer = malloc(sizeof(*_buffer) * width * height);
  _width = width;
  _height = height;
}


void collision_manager_release(void) {
  assert(_buffer != NULL, "Collision manager has already been released.");
  free(_buffer);
  _width = 0;
  _height = 0;
  memset(_is_collisions, 0, ENTITY_MAX * sizeof(_is_collisions[0]));
  for (int i = 0; i < ENTITY_MAX; i++) {
    _on_collision[i] = _no_op;
  }
}


void collision_manager_update(void) {
  // Cleanup the buffer
  for (int i = 0; i < _buffer_length_get(); i++) {
    _buffer[i] = 0;
  }

  // Iterate over all entities and mark the buffer flags based on entity's faction.
  uint8_t* buffer = _buffer;
  for (int i = 0; i < ENTITY_MAX; i++) {
    _is_collisions[i] = false;
    if (!_is_active_entity(i)) continue;
    const struct VirtualWindow* window = sprite_component_window_get(i);
    const struct VirtualWindow* game_window = game_screen_get();
    struct Vector v = {window->offset_x - game_window->offset_x, window->offset_y - game_window->offset_y};
    const struct SpriteBuffer* sprite = window->buffer;
    for (int dy = 0; dy < sprite->height; dy++) {
      for (int dx = 0; dx < sprite->width; dx++) {
        int x = v.x + dx;
        int y = v.y + dy;
        if (x < 0 || _width <= x) continue;
        if (y < 0 || _height <= y) continue;
        buffer[_collision_buffer_index(x, y)] |= ((uint8_t)1 << faction_component_faction_id_get(i));
      }
    }
  }
  // Iterate over all entities and compare their sprite buffer with the collision buffer.
  for (int i = 0; i < ENTITY_MAX; i++) {
    if (!_is_active_entity(i)) continue;
    const struct VirtualWindow* window = sprite_component_window_get(i);
    const struct VirtualWindow* game_window = game_screen_get();
    const struct SpriteBuffer* sprite = window->buffer;
    struct Vector v = {window->offset_x - game_window->offset_x, window->offset_y - game_window->offset_y};
    for (int dy = 0; dy < sprite->height; dy++) {
      for (int dx = 0; dx < sprite->width; dx++) {
        int x = v.x + dx;
        int y = v.y + dy;
        if (x < 0 || _width <= x) continue;
        if (y < 0 || _height <= y) continue;
        if (buffer[_collision_buffer_index(x, y)] != ((uint8_t)1 << faction_component_faction_id_get(i))) {
          _is_collisions[i] = true;
          break;
        }
      }
      if (_is_collisions[i]) {
        break;
      }
    }
  }

  for (int i = 0; i < ENTITY_MAX; i++) {
    if (!_is_active_entity(i)) continue;
    if (_is_collisions[i]) _on_collision[i](i);
  }
}


bool collision_manager_is_collision(EntityId entity_id) {
  assert_entity_id(entity_id);
  return entity_system_component_is_active(entity_id, COMPONENT_ID_COLLISION) && _is_collisions[entity_id];
}


void collision_manager_set_collision_handler(EntityId entity_id, void (*on_collision)(EntityId)) {
  assert_entity_id(entity_id);
  _on_collision[entity_id] = on_collision;
}


void collision_manager_deactivate(EntityId entity_id) {
  entity_system_component_deactivate(entity_id, COMPONENT_ID_COLLISION);
}


void collision_manager_activate(EntityId entity_id) {
  entity_system_component_activate(entity_id, COMPONENT_ID_COLLISION);
}