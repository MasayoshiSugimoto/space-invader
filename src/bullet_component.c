#include "bullet_component.h"


#define BULLET_SPACESHIP_BULLET_MAX 3
#define UPDATE_RATE_MILLISECOND 100


struct BulletComponent {
  EntityId entity_id;
  bool active;
};
struct BulletComponent _bullet_components[BULLET_SPACESHIP_BULLET_MAX];
struct RecuringFrameTimer _timer;


void _on_timer(void* param) {
  struct Vector v = {0, -1};
  for (int i = 0; i < BULLET_SPACESHIP_BULLET_MAX; i++) {
    if (!_bullet_components[i].active) continue;
    entity_system_add_coordinates(entity_system_get(), _bullet_components[i].entity_id, v);
  }
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
    _bullet_components[i].entity_id = entity_id;
    sprite_component_setup(entity_id, sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_SPACESHIP_BULLET));
    sprite_component_disable(entity_id);
    _bullet_components[i].active = false;
    faction_component_set(entity_id, FACTION_ID_PLAYER);
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
  struct EntitySystem* entity_system = entity_system_get();
  bullet->active = true;
  entity_system_set_coordinates(entity_system, bullet->entity_id, bullet_position);
  sprite_component_enable(bullet->entity_id);
}


void bullet_component_update(void) {
  recurring_frame_timer_update(&_timer);
  const struct VirtualWindow2* game_screen = game_screen_get();
  for (int i = 0; i < BULLET_SPACESHIP_BULLET_MAX; i++) {
    struct BulletComponent* bullet = &_bullet_components[i];
    if (!bullet->active) continue;
    if (!sprite_component_is_active(bullet->entity_id)) continue;
    const struct VirtualWindow2* window = sprite_component_window_get(bullet->entity_id);
    if (window == NULL) continue;
    if (window_manager_window_is_inside_window_2(window, game_screen)) continue;
    _bullet_components[i].active = false;
    sprite_component_disable(bullet->entity_id);
  }
}


void bullet_component_cleanup(void) {
  for (int i = 0; i < BULLET_SPACESHIP_BULLET_MAX; i++) {
    EntityId entity_id = _bullet_components[i].entity_id;
    entity_system_disable(entity_system_get(), entity_id);
    sprite_component_disable(entity_id);
    faction_component_disable(entity_id);
  }
}


void bullet_component_disable(EntityId entity_id) {
  assert_entity_id(entity_id);
  for (int i = 0; i < BULLET_SPACESHIP_BULLET_MAX; i++) {
    if (_bullet_components->entity_id == entity_id) {
      _bullet_components->active = false;
      sprite_component_disable(entity_id);
      break;
    }
  }
}
