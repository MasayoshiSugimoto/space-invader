#include "sprite_component.h"


static const bool _trace = true;


static struct SpriteComponent {
  bool active[ENTITY_MAX];
  struct VirtualWindow windows[ENTITY_MAX];
  const struct VirtualWindow* container;
} _sprite_component;


void _update_window_offset(EntityId entity_id) {
  assert_entity_id(entity_id);
  const struct VirtualWindow* game_screen_window = game_screen_get();
  struct Vector v = entity_system_get_coordinates(entity_id);
  struct VirtualWindow* window = &_sprite_component.windows[entity_id];
  window->offset_x = v.x + game_screen_window->offset_x - window->buffer->width / 2;
  window->offset_y = v.y + game_screen_window->offset_y - window->buffer->height / 2;
}


void sprite_component_init() {
  log_info("Initializing sprite component.");
  for (int i = 0; i < ENTITY_MAX; i++) {
    _sprite_component.active[i] = false;
    window_manager_window_init(&_sprite_component.windows[i]);
  }
}


void sprite_component_setup(EntityId entity_id, struct SpriteBuffer* sprite_buffer) {
  if (_trace) log_info_f("Setting entity id: entity_id=%ld", entity_id);
  assert_entity_id(entity_id);
  _sprite_component.active[entity_id] = true;
  _sprite_component.windows[entity_id].buffer = sprite_buffer;
}


bool sprite_component_is_active(EntityId entity_id) {
  assert_entity_id(entity_id);
  if (!_sprite_component.active[entity_id]) return false;
  if (_sprite_component.windows[entity_id].buffer == NULL) return false;
  return true;
}


void sprite_component_set_active(EntityId entity_id, bool active) {
  if (_trace) log_info_f("Set active: entity_id=%ld active=%s", entity_id, boolean_as_string(active));
  assert_entity_id(entity_id);
  _sprite_component.active[entity_id] = active;
}


struct SpriteComponentUnit sprite_component_get(EntityId entity_id) {
  assert_entity_id(entity_id);
  struct SpriteComponentUnit unit = {
    .entity_id = entity_id,
    .active = _sprite_component.active[entity_id],
    .sprite_buffer = _sprite_component.windows[entity_id].buffer,
    .window = &_sprite_component.windows[entity_id]
  };
  return unit;
}


void sprite_component_set(const struct SpriteComponentUnit* unit) {
  if (_trace) log_info_f("Set component unit: entity_id=%ld", unit->entity_id);
  assert_entity_id(unit->entity_id);
  _sprite_component.active[unit->entity_id] = unit->active;
  _sprite_component.windows[unit->entity_id].buffer = unit->sprite_buffer;
  _sprite_component.windows[unit->entity_id].is_transparent = true;
}


void sprite_component_disable(EntityId entity_id) {
  if (_trace) log_info_f("Disable: entity_id=%ld", entity_id);
  assert_entity_id(entity_id);
  _sprite_component.active[entity_id] = false;
}


void sprite_component_enable(EntityId entity_id) {
  if (_trace) log_info_f("Enable: entity_id=%ld", entity_id);
  assert_entity_id(entity_id);
  if (_sprite_component.windows[entity_id].buffer != NULL) {
    _sprite_component.active[entity_id] = true;
  }
}


void sprite_component_update(void) {
  // Update all windows.
  for (int entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (!entity_system_is_active(entity_id)) continue;
    if (!_sprite_component.active[entity_id]) continue;
    _update_window_offset(entity_id);
    _sprite_component.windows[entity_id].container = _sprite_component.container;
  }
}


void sprite_component_render(void) {
  uint8_t z_current = 0;
  uint8_t z_next = 0;
  do {
    z_current = z_next;
    z_next = UINT8_MAX;
    for (int entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
      if (!entity_system_is_active(entity_id)) continue;
      if (!_sprite_component.active[entity_id]) continue;
      struct VirtualWindow* window = &_sprite_component.windows[entity_id];
      if (window->z == z_current) {
        assert_f(window->buffer != NULL, "Attempt to draw null sprite buffer for entity id: %d", entity_id);
        window_manager_window_draw(window);
      } else if (window->z > z_current && window->z < z_next) {
        z_next = window->z;
      }
    }
  } while (z_next != UINT8_MAX);
}


const struct VirtualWindow* sprite_component_window_get(EntityId entity_id) {
  assert_entity_id(entity_id);
  return &_sprite_component.windows[entity_id];
}


void sprite_component_container_set(const struct VirtualWindow* window) {
  if (_trace) log_info("Set sprite component container.");
  _sprite_component.container = window;
}


void sprite_component_position_move(EntityId entity_id, struct Vector dv) {
  assert_entity_id(entity_id);
  if (!_sprite_component.active[entity_id]) return;
  entity_system_add_coordinates(entity_id, dv);
  _update_window_offset(entity_id);
}


void sprite_component_position_set(EntityId entity_id, struct Vector v) {
  assert_entity_id(entity_id);
  if (!_sprite_component.active[entity_id]) return;
  entity_system_set_coordinates(entity_id, v);
  _update_window_offset(entity_id);
}


void sprite_component_sprite_buffer_set(EntityId entity_id, struct SpriteBuffer* sprite_buffer) {
  assert_entity_id(entity_id);
  _sprite_component.windows[entity_id].buffer = sprite_buffer;
}


void sprite_component_z_set(EntityId entity_id, uint8_t z) {
  assert_entity_id(entity_id);
  _sprite_component.windows[entity_id].z = z;
}