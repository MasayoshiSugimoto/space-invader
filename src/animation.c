#include "animation.h"


#define ANIMATION_ANIMATION_STEP_MAX 5
#define ANIMATION_ANIMATION_MAX 1


#define ANIMATION_ID_EXPLOSION "animation.explosion.dat"


// New data structure
struct AnimationStep {
  struct SpriteBuffer* sprite_buffer;
  Duration duration;
};


struct Animation {
  const char* animation_name;
  const struct AnimationStep* animation_begin;
  const struct AnimationStep* animation_end;
};


struct AnimationStatus {
  const struct Animation* animation;
  struct FrameTimer _time_from_begin;
  void (*on_animation_end)(EntityId entity_id);
};


static struct AnimationComponent {
  bool active[ENTITY_MAX];
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


void animation_init(void) {
  for (int i = 0; i < ANIMATION_ANIMATION_STEP_MAX; i++) {
    _animations_steps[i].sprite_buffer = NULL;
    _animations_steps[i].duration = 0;
  }
  for (int i = 0; i < ANIMATION_ANIMATION_MAX; i++) {
    _animations[i].animation_begin = NULL;
    _animations[i].animation_end = NULL;
    _animations[i].animation_name = NULL;
  }
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    _animation_component.active[entity_id] = false;
    struct AnimationStatus* status = &_animation_component.status[entity_id];
    status->animation = NULL;
    frame_timer_timer_init(&status->_time_from_begin);
  }
}


void animation_setup(void) {
  _animations_steps[0].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_EMPTY);
  _animations_steps[0].duration = milliseconds_as_duration(400);
  _animations_steps[1].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_EXPLOSION_3);
  _animations_steps[1].duration = milliseconds_as_duration(400);
  _animations_steps[2].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_EXPLOSION_2);
  _animations_steps[2].duration = milliseconds_as_duration(400);
  _animations_steps[3].sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_EXPLOSION_1);
  _animations_steps[3].duration = milliseconds_as_duration(400);
  _animations[0].animation_name = ANIMATION_NAME_EXPLOSION;
  _animations[0].animation_begin = &_animations_steps[0];
  _animations[0].animation_end = &_animations_steps[4];
}


void animation_update(void) {
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (!_animation_component.active[entity_id]) continue;
    struct AnimationStatus* status = &_animation_component.status[entity_id];
    Duration duration = 0;
    const struct AnimationStep* step = status->animation->animation_begin;
    while (step < status->animation->animation_end) {
      duration += step->duration;
      if (duration >= frame_timer_get_elapsed_time(&status->_time_from_begin)) break;
      step++;
    }
    if (step < status->animation->animation_end) {
      sprite_component_sprite_buffer_set(entity_id, step->sprite_buffer);
    } else {
      // End of the animation. Disable sprite component.
      sprite_component_disable(entity_id);
    }
  }
}


void animation_set(EntityId entity_id, const char* animation_name) {
  assert_entity_id(entity_id);
  _animation_component.active[entity_id] = true;
  _animation_component.status[entity_id].animation = _animation_get(animation_name);
  frame_timer_timer_init(&_animation_component.status[entity_id]._time_from_begin);
  frame_timer_start(&_animation_component.status[entity_id]._time_from_begin, DURATION_ONE_DAY);
}


bool animation_is_done(EntityId entity_id) {
  assert_entity_id(entity_id);
  struct AnimationStatus* status = &_animation_component.status[entity_id];
  Duration duration = 0;
  const struct AnimationStep* step = status->animation->animation_begin;
  while (step < status->animation->animation_end) {
    duration += step->duration;
    if (duration >= frame_timer_get_elapsed_time(&status->_time_from_begin)) break;
    step++;
  }
  return step >= status->animation->animation_end;
}