#include "sprite_component.h"


static const bool _trace = true;


static struct SpriteComponent {
  bool active[ENTITY_MAX];
  enum SpriteId sprite_id[ENTITY_MAX];
  struct VirtualWindow2 windows[ENTITY_MAX];
  const struct VirtualWindow2* container;
} _sprite_component;


void sprite_component_init() {
  log_info("Initializing sprite component.");
  for (int i = 0; i < ENTITY_MAX; i++) {
    _sprite_component.sprite_id[i] = SPRITE_ID_NONE;
    _sprite_component.active[i] = false;
    window_manager_window_2_init(&_sprite_component.windows[i]);
  }
}


void sprite_component_setup(EntityId entity_id, struct SpriteBuffer* sprite_buffer) {
  if (_trace) log_info_f("Setting entity id: entity_id=%ld", entity_id);
  assert_entity_id(entity_id);
  _sprite_component.active[entity_id] = true;
  _sprite_component.sprite_id[entity_id] = SPRITE_ID_NONE;
  _sprite_component.windows[entity_id].buffer = sprite_buffer;
}


enum SpriteId sprite_component_get_sprite_id(EntityId entity_id) {
  assert_entity_id(entity_id);
  return _sprite_component.sprite_id[entity_id];
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
    .sprite_id = _sprite_component.sprite_id[entity_id],
    .sprite_buffer = _sprite_component.windows[entity_id].buffer
  };
  return unit;
}


void sprite_component_set(const struct SpriteComponentUnit* unit) {
  if (_trace) log_info_f("Set component unit: entity_id=%ld", unit->entity_id);
  assert_entity_id(unit->entity_id);
  _sprite_component.active[unit->entity_id] = unit->active;
  _sprite_component.sprite_id[unit->entity_id] = unit->sprite_id;
  _sprite_component.windows[unit->entity_id].buffer = unit->sprite_buffer;
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
  const struct VirtualWindow2* game_screen_window = game_screen_get();
  for (int entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (!entity_system_is_active(entity_id)) continue;
    if (!_sprite_component.active[entity_id]) continue;
    struct VirtualWindow2* window = &_sprite_component.windows[entity_id];
    struct Vector v = entity_system_get_coordinates(entity_id);
    window->offset_x = v.x + game_screen_window->offset_x;
    window->offset_y = v.y + game_screen_window->offset_y;
    _sprite_component.windows[entity_id].container = _sprite_component.container;
  }
}


void sprite_component_render(void) {
  for (int entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (!entity_system_is_active(entity_id)) continue;
    if (!_sprite_component.active[entity_id]) continue;
    struct VirtualWindow2* window = &_sprite_component.windows[entity_id];
    assert_f(window->buffer != NULL, "Attempt to draw null sprite buffer for entity id: %d", entity_id);
    window_manager_window_draw_2(window);
  }
}


const struct VirtualWindow2* sprite_component_window_get(EntityId entity_id) {
  assert_entity_id(entity_id);
  return &_sprite_component.windows[entity_id];
}


void sprite_component_container_set(const struct VirtualWindow2* window) {
  if (_trace) log_info("Set sprite component container.");
  _sprite_component.container = window;
}


void sprite_component_position_move(EntityId entity_id, struct Vector dv) {
  assert_entity_id(entity_id);
  if (!_sprite_component.active[entity_id]) return;
  const struct VirtualWindow2* game_screen_window = game_screen_get();
  entity_system_add_coordinates(entity_id, dv);
  struct Vector v = entity_system_get_coordinates(entity_id);
  struct VirtualWindow2* window = &_sprite_component.windows[entity_id];
  window->offset_x = v.x + game_screen_window->offset_x;
  window->offset_y = v.y + game_screen_window->offset_y;
}


void sprite_component_position_set(EntityId entity_id, struct Vector v) {
  assert_entity_id(entity_id);
  if (!_sprite_component.active[entity_id]) return;
  const struct VirtualWindow2* game_screen_window = game_screen_get();
  entity_system_set_coordinates(entity_id, v);
  struct VirtualWindow2* window = &_sprite_component.windows[entity_id];
  window->offset_x = v.x + game_screen_window->offset_x;
  window->offset_y = v.y + game_screen_window->offset_y;
}


void sprite_component_sprite_buffer_set(EntityId entity_id, struct SpriteBuffer* sprite_buffer) {
  assert_entity_id(entity_id);
  _sprite_component.windows[entity_id].buffer = sprite_buffer;
}