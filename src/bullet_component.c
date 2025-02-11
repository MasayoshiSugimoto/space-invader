#include "bullet_component.h"


#define BULLET_SPACESHIP_BULLET_MAX 3
#define UPDATE_RATE_MILLISECOND 100


struct BulletComponent {
  EntityId entity_id;
  bool active;
};
struct BulletComponent _bullet_components[BULLET_SPACESHIP_BULLET_MAX];
struct RecuringFrameTimer _timer;


static void _on_timer(void* param) {
  struct Vector v = {0, -1};
  for (int i = 0; i < BULLET_SPACESHIP_BULLET_MAX; i++) {
    if (!_bullet_components[i].active) continue;
    entity_system_add_coordinates(_bullet_components[i].entity_id, v);
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
  for (int i = 0; i < BULLET_SPACESHIP_BULLET_MAX; i++) {
    if (_bullet_components[i].entity_id == entity_id) {
      return &_bullet_components[i];
    }
  }
  return NULL;
}


void bullet_component_init(void) {
  log_info("Initializing bullet component.");
  for (int i = 0; i < BULLET_SPACESHIP_BULLET_MAX; i++) {
    _bullet_components[i].entity_id = ENTITY_MAX;
    _bullet_components[i].active = false;
  }
  recurring_frame_timer_set(&_timer, _on_timer, NULL, milliseconds_as_duration(UPDATE_RATE_MILLISECOND));
}


void bullet_component_setup(void) {
  log_info("Setting up bullet component.");
  for (int i = 0; i < BULLET_SPACESHIP_BULLET_MAX; i++) {
    EntityId entity_id = entity_system_create_entity();
    _bullet_components[i].active = false;
    _bullet_components[i].entity_id = entity_id;
    sprite_component_setup(entity_id, sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_SPACESHIP_BULLET));
    faction_component_set(entity_id, FACTION_ID_PLAYER);
    _deactivate(&_bullet_components[i]);
  }
}


void bullet_component_fire(struct Vector bullet_position) {
  log_info("Fire event received.");
  struct BulletComponent* bullet = NULL;
  for (int i = 0; i < BULLET_SPACESHIP_BULLET_MAX; i++) {
    if (!_bullet_components[i].active) {
      bullet = &_bullet_components[i];
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


void bullet_component_update(void) {
  recurring_frame_timer_update(&_timer);
  const struct VirtualWindow* game_screen = game_screen_get();
  for (int i = 0; i < BULLET_SPACESHIP_BULLET_MAX; i++) {
    struct BulletComponent* bullet = &_bullet_components[i];
    if (!bullet->active) continue;
    if (!sprite_component_is_active(bullet->entity_id)) {
      _deactivate(bullet);
      continue;
    }
    const struct VirtualWindow* window = sprite_component_window_get(bullet->entity_id);
    if (window == NULL) {
      bullet_component_disable(bullet->entity_id);
      _deactivate(bullet);
      continue;
    }
    if (!window_manager_window_is_inside_window(window, game_screen)) {
      _deactivate(bullet);
      continue;
    }
  }
}


void bullet_component_cleanup(void) {
  for (int i = 0; i < BULLET_SPACESHIP_BULLET_MAX; i++) {
    EntityId entity_id = _bullet_components[i].entity_id;
    log_info_f("Deactivate bullet component: entity_id = %zu", entity_id);
    _bullet_components[i].active = false;
    _bullet_components[i].entity_id = 0;
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