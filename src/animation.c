#include "animation.h"


#define ANIMATION_ANIMATION_STEP_MAX 10
#define ANIMATION_ANIMATION_MAX 4


#define ANIMATION_ID_EXPLOSION "animation.explosion.dat"


struct Animation {
  const char* animation_name;
  struct SLICE__AnimationStep slice_animation_step;
};


struct AnimationStatus {
  struct Animation* animation;
  struct FrameTimer _time_from_begin;
  void (*on_animation_end)(EntityId entity_id);
  bool is_loop;
};


static struct AnimationComponent {
  struct AnimationStatus status[ENTITY_MAX];
} _animation_component;


static struct AnimationStep _animations_steps[ANIMATION_ANIMATION_STEP_MAX];
static struct Animation _animations[ANIMATION_ANIMATION_MAX];


const struct Animation* _animation_get(const char* animation_name) {
  for (int i = 0; i < ANIMATION_ANIMATION_MAX; i++) {
    if (strcmp(_animations[i].animation_name, animation_name) == 0) return &_animations[i];
  }
  return NULL;
}


uint32_t _current_step_get(EntityId entity_id) {
  assert_entity_id(entity_id);
  Duration duration = 0;
  struct AnimationStatus* status = &_animation_component.status[entity_id];
  struct SLICE__AnimationStep* slice = &status->animation->slice_animation_step;
  uint32_t i = 0;
  while (i < slice->length) {
    struct AnimationStep* step = SLICE__AnimationStep__get(slice, i);
    duration += step->duration;
    if (duration >= frame_timer_get_elapsed_time(&status->_time_from_begin)) break;
    i++;
  }
  return i;
}


void animation_init(void) {
  for (int i = 0; i < ANIMATION_ANIMATION_STEP_MAX; i++) {
    _animations_steps[i].sprite_buffer = NULL;
    _animations_steps[i].duration = 0;
  }
  for (int i = 0; i < ANIMATION_ANIMATION_MAX; i++) {
    _animations[i].animation_name = NULL;
    SLICE__AnimationStep__init(&_animations[i].slice_animation_step);
  }
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    entity_system_component_deactivate(entity_id, COMPONENT_ID_ANIMATION);
    struct AnimationStatus* status = &_animation_component.status[entity_id];
    status->animation = NULL;
    frame_timer_timer_init(&status->_time_from_begin);
  }
}


void animation_setup(void) {
  _animations_steps[0].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_EXPLOSION_3);
  _animations_steps[0].duration = milliseconds_as_duration(200);
  _animations_steps[1].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_EXPLOSION_2);
  _animations_steps[1].duration = milliseconds_as_duration(200);
  _animations_steps[2].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_EXPLOSION_1);
  _animations_steps[2].duration = milliseconds_as_duration(200);
  _animations_steps[3].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_SPACESHIP);
  _animations_steps[3].duration = milliseconds_as_duration(50);
  _animations_steps[4].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_SPACESHIP_2);
  _animations_steps[4].duration = milliseconds_as_duration(50);
  _animations_steps[5].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_ALIEN);
  _animations_steps[5].duration = milliseconds_as_duration(200);
  _animations_steps[6].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_ALIEN_2);
  _animations_steps[6].duration = milliseconds_as_duration(200);
  _animations_steps[7].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_ALIEN_SQUID_1);
  _animations_steps[7].duration = milliseconds_as_duration(200);
  _animations_steps[8].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_ALIEN_SQUID_2);
  _animations_steps[8].duration = milliseconds_as_duration(200);
  _animations[0].animation_name = ANIMATION_NAME_EXPLOSION;
  _animations[0].slice_animation_step.data = &_animations_steps[0];
  _animations[0].slice_animation_step.length = 3;
  _animations[1].animation_name = ANIMATION_NAME_SPACESHIP;
  _animations[1].slice_animation_step.data = &_animations_steps[3];
  _animations[1].slice_animation_step.length = 2;
  _animations[2].animation_name = ANIMATION_NAME_ALIEN;
  _animations[2].slice_animation_step.data = &_animations_steps[5];
  _animations[2].slice_animation_step.length = 2;
  _animations[3].animation_name = ANIMATION_NAME_ALIEN_SQUID;
  _animations[3].slice_animation_step.data = &_animations_steps[7];
  _animations[3].slice_animation_step.length = 2;
}


void animation_update(void) {
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (!entity_system_component_is_active(entity_id, COMPONENT_ID_ANIMATION)) continue;
    struct AnimationStatus* status = &_animation_component.status[entity_id];
    struct SLICE__AnimationStep* slice = &status->animation->slice_animation_step;
    uint32_t current_step_index = _current_step_get(entity_id);
    if (current_step_index < slice->length) {
      sprite_component_sprite_buffer_set(entity_id, SLICE__AnimationStep__get(slice, current_step_index)->sprite_buffer);
    } else if (status->is_loop) {
      animation_set(entity_id, status->animation->animation_name);
      animation_start(entity_id);
    } else {
      // End of the animation. Disable sprite component.
      sprite_component_disable(entity_id);
      entity_system_component_deactivate(entity_id, COMPONENT_ID_ANIMATION);
    }
  }
}


void animation_set(EntityId entity_id, const char* animation_name) {
  log_info_f("Setting animation: entity_id=%zu, animation_name=%s", entity_id, animation_name);
  assert_entity_id(entity_id);
  _animation_component.status[entity_id].animation = _animation_get(animation_name);
}


void animation_start(EntityId entity_id) {
  log_info_f("Animation start: entity_id=%zu", entity_id);
  assert_entity_id(entity_id);
  frame_timer_timer_init(&_animation_component.status[entity_id]._time_from_begin);
  frame_timer_start(&_animation_component.status[entity_id]._time_from_begin, DURATION_ONE_DAY);
  entity_system_component_activate(entity_id, COMPONENT_ID_ANIMATION);
}


bool animation_is_done(EntityId entity_id) {
  assert_entity_id(entity_id);
  return _current_step_get(entity_id) >= _animation_component.status[entity_id].animation->slice_animation_step.length;
}


void animation_is_loop_set(EntityId entity_id, bool is_loop) {
  log_info_f("Enabling animation loop: entity_id=%zu", entity_id);
  assert_entity_id(entity_id);
  _animation_component.status[entity_id].is_loop = is_loop;
}