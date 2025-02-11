/********************************************************************************
 * This AI will follow the basic movement of the basic enemies in space invader.
 * Enemy will move left then right then left again.
 * They will move one line down every time they change direction.
 *******************************************************************************/


#include "enemy_ai_basic_component.h"


#define MARGIN_FROM_BORDER 5
#define UPDATE_RATE_MILLISECOND 50


enum Direction {
  DIRECTION_LEFT,
  DIRECTION_RIGHT
};


struct EnemyAiBasicComponent {
  enum Direction direction;
  uint64_t timer_millisecond;
  int margin_from_border;
  int update_rate_millisecond;
} _ai;


void enemy_ai_basic_init(void) {
  log_info("Initializing enemy basic ai.");
  _ai.direction = DIRECTION_RIGHT;
  _ai.timer_millisecond = 0;
  _ai.margin_from_border = MARGIN_FROM_BORDER;
  _ai.update_rate_millisecond = UPDATE_RATE_MILLISECOND;
}


bool _is_active(EntityId entity_id) {
  if (!entity_system_is_active(entity_id)) return false;
  if (!entity_system_component_is_active(entity_id, COMPONENT_ID_BASIC_AI)) return false;
  if (!sprite_component_is_active(entity_id)) return false;
  return true;
}


void enemy_ai_basic_update(uint64_t delta_time_millisecond) {
  _ai.timer_millisecond += delta_time_millisecond;
  if (_ai.timer_millisecond < _ai.update_rate_millisecond) return;

  _ai.timer_millisecond = 0;

  int max_x = 0;
  int min_x = 99999;
  for (int i = 0; i < ENTITY_MAX; i++) {
    if (!_is_active(i)) continue;
    struct SpriteComponentUnit sprite_component = sprite_component_get(i);
    struct VirtualWindow* window = sprite_component.window;
    min_x = imin(min_x, window->offset_x);
    max_x = imax(max_x, window->offset_x + sprite_component.sprite_buffer->width);
  }

  const struct VirtualWindow* game_screen = game_screen_get();
  bool is_change_direction = false;
  if (_ai.direction == DIRECTION_RIGHT && max_x >= virtual_window_right_get(game_screen) - _ai.margin_from_border) {
    _ai.direction = DIRECTION_LEFT;
    is_change_direction = true;
  } else if (_ai.direction == DIRECTION_LEFT && min_x <= virtual_window_left_get(game_screen) + _ai.margin_from_border) {
    _ai.direction = DIRECTION_RIGHT;
    is_change_direction = true;
  }
  struct Vector v = VZERO;
  if (is_change_direction) {
    v.y = 1;
  } else if (_ai.direction == DIRECTION_RIGHT) {
    v.x = 1;
  } else {
    v.x = -1;
  }
  for (int i = 0; i < ENTITY_MAX; i++) {
    if (!_is_active(i)) continue;
    entity_system_add_coordinates(i, v);
  }
}


void enemy_ai_basic_disable(EntityId entity_id) {
  entity_system_component_deactivate(entity_id, COMPONENT_ID_BASIC_AI);
}


void enemy_ai_basic_margin_from_border_set(int margin_from_border) {
  _ai.margin_from_border = margin_from_border;
}


void enemy_ai_basic_activate(EntityId entity_id) {
  entity_system_component_activate(entity_id, COMPONENT_ID_BASIC_AI);
}