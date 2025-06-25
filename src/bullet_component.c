#include "bullet_component.h"


#define BULLET_SPACESHIP_BULLET_MAX 3
#define BULLET_ALL_MAX 6 
#define BULLET_SPACESHIP_START 0
#define BULLET_SPACESHIP_END BULLET_SPACESHIP_BULLET_MAX
#define BULLET_ENEMY_START BULLET_SPACESHIP_END
#define BULLET_ENEMY_END BULLET_ALL_MAX
#define UPDATE_RATE_MILLISECOND 20
#define UPDATE_RATE_ENEMY_BULLER_MILLISECOND 200
#define ENEMY_FIRE_RATE_SECOND 1
#define BULLET_Z_COORDINATE 9


struct BulletComponent _bullet_component_array[BULLET_ALL_MAX];
struct SLICE__BulletComponent _bullet_components = {
  .data = _bullet_component_array,
  .length = array_size(_bullet_component_array)
};
struct RecuringFrameTimer _timer;
struct RecuringFrameTimer _enemy_fire_timer;
struct RecuringFrameTimer _enemy_bullet_update_timer;


static void _on_spaceship_bullet_update(void* param) {
  struct Vector up = {0, -1};
  for (int i = BULLET_SPACESHIP_START; i < BULLET_SPACESHIP_END; i++) {
    const struct BulletComponent* bullet = SLICE__BulletComponent__get(&_bullet_components, i);
    if (!bullet->active) continue;
    entity_system_add_coordinates(bullet->entity_id, up);
  }
}


static void _on_enemy_bullet_update(void* param) {
  struct Vector down = {0, 1};
  for (int i = BULLET_ENEMY_START; i < BULLET_ENEMY_END; i++) {
    const struct BulletComponent* bullet = SLICE__BulletComponent__get(&_bullet_components, i);
    if (!bullet->active) continue;
    entity_system_add_coordinates(bullet->entity_id, down);
  }
}


static void _deactivate(struct BulletComponent* bullet_component) {
  log_info_f("Deactivate bullet component: entity_id = %zu", bullet_component->entity_id);
  bullet_component->active = false;
  sprite_component_disable(bullet_component->entity_id);
  collision_manager_deactivate(bullet_component->entity_id);
}


static void _activate(struct BulletComponent* bullet_component) {
  log_info_f("Activate bullet component: entity_id = %zu", bullet_component->entity_id);
  bullet_component->active = true;
  sprite_component_enable(bullet_component->entity_id);
  collision_manager_activate(bullet_component->entity_id);
}


struct BulletComponent* _bullet_component_get(EntityId entity_id) {
  assert_entity_id(entity_id);
  for (int i = 0; i < BULLET_ALL_MAX; i++) {
    struct BulletComponent* bullet = SLICE__BulletComponent__get(&_bullet_components, i);
    if (bullet->entity_id == entity_id) {
      return bullet;
    }
  }
  return NULL;
}


void _on_enemy_fire_timer(void* params) {
  log_info("Enemy fire timer event.");
  int count = 0;
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (!faction_component_is_enabled(entity_id)) continue;
    if (faction_component_faction_id_get(entity_id) != FACTION_ID_ALIEN) continue;
    count++;
  }
  if (count == 0) return;
  int index = rand() % count;
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (!faction_component_is_enabled(entity_id)) continue;
    if (faction_component_faction_id_get(entity_id) != FACTION_ID_ALIEN) continue;
    if (index == 0) {
      bullet_component_fire_enemy(entity_id);
      break;
    } else {
      index--;
    }
  }
}


bool _is_spaceship_bullet_by_bullet_index(int bullet_index) {
  return BULLET_SPACESHIP_START <= bullet_index && bullet_index < BULLET_SPACESHIP_END;
}


bool _is_enemy_bullet_by_bullet_index(int bullet_index) {
  return BULLET_ENEMY_START <= bullet_index && bullet_index < BULLET_ENEMY_END;
}


void bullet_component_init(void) {
  log_info("Initializing bullet component.");
  for (int i = 0; i < BULLET_ALL_MAX; i++) {
    struct BulletComponent* bullet = SLICE__BulletComponent__get(&_bullet_components, i);
    bullet->entity_id = ENTITY_MAX;
    bullet->active = false;
  }
  recurring_frame_timer_set(&_timer, _on_spaceship_bullet_update, NULL, milliseconds_as_duration(UPDATE_RATE_MILLISECOND));
  recurring_frame_timer_set(&_enemy_bullet_update_timer, _on_enemy_bullet_update, NULL, milliseconds_as_duration(UPDATE_RATE_ENEMY_BULLER_MILLISECOND));
  recurring_frame_timer_set(&_enemy_fire_timer, _on_enemy_fire_timer, NULL, seconds_as_duration(ENEMY_FIRE_RATE_SECOND));
}


void bullet_component_setup(void) {
  log_info("Setting up bullet component.");
  for (int i = 0; i < BULLET_ALL_MAX; i++) {
    EntityId entity_id = entity_system_create_entity();
    struct BulletComponent* bullet = SLICE__BulletComponent__get(&_bullet_components, i);
    bullet->active = false;
    bullet->entity_id = entity_id;
		if (_is_spaceship_bullet_by_bullet_index(i)) {
      sprite_component_setup(entity_id, sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_SPACESHIP_BULLET));
      faction_component_set(entity_id, FACTION_ID_PLAYER);
		} else if (_is_enemy_bullet_by_bullet_index(i)) {
      sprite_component_setup(entity_id, sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_SPACESHIP_BULLET));
      faction_component_set(entity_id, FACTION_ID_ALIEN);
    }
    sprite_component_get(entity_id).window->z = BULLET_Z_COORDINATE;
    _deactivate(bullet);
  }
}


void bullet_component_fire(struct Vector bullet_position) {
  log_info("Fire event received.");
  struct BulletComponent* bullet = NULL;
  for (int i = BULLET_SPACESHIP_START; i < BULLET_SPACESHIP_END; i++) {
    if (!SLICE__BulletComponent__get(&_bullet_components, i)->active) {
      bullet = SLICE__BulletComponent__get(&_bullet_components, i);
      break;
    }
  }
  if (bullet == NULL) {
    log_info("No remaining available bullet.");
    return;  // Already fired the max number of bullets.
  }
  _activate(bullet);
  entity_system_set_coordinates(bullet->entity_id, bullet_position);
}


void bullet_component_fire_enemy(EntityId entity_id) {
  log_info_f("Enemy fire event received: entity_id=%zu", entity_id);
  struct BulletComponent* bullet = NULL;
  for (int i = BULLET_ENEMY_START; i < BULLET_ENEMY_END; i++) {
    if (!SLICE__BulletComponent__get(&_bullet_components, i)->active) {
      bullet = SLICE__BulletComponent__get(&_bullet_components, i);
      break;
    }
  }
  if (bullet == NULL) {
    log_info("No remaining available bullet.");
    return;  // Already fired the max number of bullets.
  }
  _activate(bullet);
  entity_system_set_coordinates(bullet->entity_id, entity_system_get_coordinates(entity_id));
}


void bullet_component_update(void) {
  recurring_frame_timer_update(&_timer);
  recurring_frame_timer_update(&_enemy_bullet_update_timer);
  const struct VirtualWindow* game_screen = game_screen_get();
  for (int i = 0; i < BULLET_ALL_MAX; i++) {
    struct BulletComponent* bullet = SLICE__BulletComponent__get(&_bullet_components, i);
    if (!bullet->active) continue;
    if (!sprite_component_is_active(bullet->entity_id)) {
      log_info("Sprite component not active.");
      _deactivate(bullet);
      continue;
    }
    const struct VirtualWindow* window = sprite_component_window_get(bullet->entity_id);
    if (window == NULL) {
      log_info("Window is null");
      bullet_component_disable(bullet->entity_id);
      _deactivate(bullet);
      continue;
    }
    if (!window_manager_window_is_inside_window(window, game_screen)) {
      log_info("bullet outside window.");
      _deactivate(bullet);
      continue;
    }
  }
  recurring_frame_timer_update(&_enemy_fire_timer);
}


void bullet_component_cleanup(void) {
  for (int i = 0; i < BULLET_ALL_MAX; i++) {
    struct BulletComponent* bullet = SLICE__BulletComponent__get(&_bullet_components, i);
    EntityId entity_id = bullet->entity_id;
    log_info_f("Deactivate bullet component: entity_id = %zu", entity_id);
    bullet->active = false;
    bullet->entity_id = 0;
    entity_system_disable(entity_id);
    sprite_component_disable(entity_id);
    faction_component_disable(entity_id);
    collision_manager_deactivate(entity_id);
  }
}


void bullet_component_disable(EntityId entity_id) {
  assert_entity_id(entity_id);
   struct BulletComponent* bullet_component = _bullet_component_get(entity_id);
  if (bullet_component == NULL) return;
  _deactivate(bullet_component);
}


bool bullet_component_is_active(EntityId entity_id) {
  assert_entity_id(entity_id);
  struct BulletComponent* bullet_component = _bullet_component_get(entity_id);
  if (bullet_component == NULL) return false;
  return bullet_component->active;
}
