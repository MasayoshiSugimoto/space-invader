/********************************************************************************
 * This AI will follow the basic movement of the basic enemies in space invader.
 * Enemy will move left then right then left again.
 * They will move one line down every time they change direction.
 *******************************************************************************/


#include "enemy_ai_basic.h"


#define MARGIN_FROM_BORDER 5
#define UPDATE_RATE_MILLISECOND 100


enum Direction {
  DIRECTION_LEFT,
  DIRECTION_RIGHT
};


struct EnemyAiBasicComponent {
  enum Direction direction;
  uint64_t timer_millisecond;
  EntityId entity_ids[ENTITY_MAX];
} enemy_ai_basic_component;


void enemy_ai_basic_init() {
  enemy_ai_basic_component.direction = DIRECTION_RIGHT;
  enemy_ai_basic_component.timer_millisecond = 0;
  for (int i = 0; i < ENTITY_MAX; i++) {
    enemy_ai_basic_component.entity_ids[i] = ENTITY_MAX;
  }
}


void enemy_ai_basic_update(struct EntitySystem* entity_system, uint64_t delta_time_millisecond) {
  struct EnemyAiBasicComponent* component = &enemy_ai_basic_component;
  component->timer_millisecond += delta_time_millisecond;
  if (component->timer_millisecond < UPDATE_RATE_MILLISECOND) return;

  component->timer_millisecond = 0;

  int max_x = 0;
  int min_x = 99999;
  for (int i = 0; i < ENTITY_MAX; i++) {
    if (!entity_system->active[i]) continue;
    if (!sprite_component_is_active(i)) continue;
    enum SpriteId sprite_id = sprite_component_get_sprite_id(i);
    if (sprite_id != SPRITE_ID_ALIEN) continue;
    const struct Sprite* sprite = sprite_get_sprite(sprite_id);
    struct Vector v = entity_system->coordinates[i];

    min_x = imin(min_x, v.x);
    max_x = imax(max_x, v.x + sprite->width);
  }

  bool is_change_direction = false;
  if (component->direction == DIRECTION_RIGHT && max_x >= SCREEN_WIDTH - MARGIN_FROM_BORDER) {
    component->direction = DIRECTION_LEFT;
    is_change_direction = true;
  } else if (component->direction == DIRECTION_LEFT && min_x <= MARGIN_FROM_BORDER) {
    component->direction = DIRECTION_RIGHT;
    is_change_direction = true;
  }

  if (is_change_direction) {
    for (int i = 0; i < ENTITY_MAX; i++) {
      if (!sprite_component_is_active(i)) continue;
      enum SpriteId sprite_id = sprite_component_get_sprite_id(i);
      if (sprite_id != SPRITE_ID_ALIEN) continue;
      struct Vector v = {0, 1};
      entity_system_add_coordinates(entity_system, i, v);
    }
  }

  struct Vector v = VZERO;
  if (component->direction == DIRECTION_RIGHT) {
    v.x = 1;
  } else {
    v.x = -1;
  }

  for (int i = 0; i < ENTITY_MAX; i++) {
    if (sprite_component_get_sprite_id(i) == SPRITE_ID_ALIEN) {
      entity_system_add_coordinates(entity_system, i, v);
    }
  }
}
