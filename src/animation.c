#include "animation.h"


const AnimationId ANIMATION_ID_EXPLOSION = 0;


struct AnimationPhase {
  enum SpriteId sprite_id;
  Duration duration;
};


struct Animation {
  const struct AnimationPhase* animation_phase_begin;
};


struct AnimationStatus {
  const struct Animation* animation;
  const struct AnimationPhase* animation_phase;
  struct Timer timer;
};


struct AnimationComponent {
  bool active[ENTITY_MAX];
  struct AnimationStatus status[ENTITY_MAX];
} animation_component;


const struct AnimationPhase* animation_phases;
const struct Animation* animations;
const struct AnimationPhase* animation_phase_end;
const struct Animation* animation_end;


const struct AnimationPhase animation_phases_data[] = {
  {SPRITE_ID_EXPLOSION_1, 300},
  {SPRITE_ID_EXPLOSION_2, 300},
  {SPRITE_ID_EXPLOSION_3, 300},
};


void animation_phase_next(struct AnimationStatus* status) {
  const struct AnimationPhase* next_animation_phase = status->animation_phase + 1;
  const struct Animation* next_animation = status->animation + 1;
  if (
      next_animation_phase >= animation_phase_end
      || (next_animation < animation_end && next_animation_phase >= next_animation->animation_phase_begin)
  ) {
    status->animation_phase = NULL;
    return;
  }

  status->animation_phase = next_animation_phase;
  timer_init(&status->timer, next_animation_phase->duration);
}


bool is_end(const struct AnimationStatus* status) {
  return status->animation_phase == NULL;
}


void init_status(struct AnimationStatus* status, AnimationId animation_id) {
  const struct Animation* animation = &animations[animation_id];
  status->animation = animation;
  status->animation_phase = animation->animation_phase_begin;
  timer_init(&status->timer, status->animation_phase->duration);
}


void animation_dump() {
  log_info("Dumping animation status...");
  for (const struct AnimationPhase* it = animation_phases; it < animation_phase_end; it++) {
    log_info_f("{sprite_id=%d, duration=%ld}", it->sprite_id, it->duration);
  }
  for (const struct Animation* it = animations; it < animation_end; it++) {
    log_info_f("{animation_phase_begin=%p}", it->animation_phase_begin);
  }
}


void animation_init() {
  animation_phases = animation_phases_data;
  int nb_animation_phase = 3;
  int nb_animation = 1;
  struct Animation* animation_ptr = malloc(sizeof(*animations) * nb_animation);
  animation_ptr[0].animation_phase_begin = &animation_phases[0];
  animations = animation_ptr;
  animation_phase_end = &animation_phases[nb_animation_phase];
  animation_end = &animation_ptr[nb_animation];
  animation_dump();
}


void animation_update(Duration delta_time) {
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (!animation_component.active[entity_id]) continue;
    struct AnimationStatus* animation_status = &animation_component.status[entity_id];
    if (is_end(animation_status)) continue;
    if (!timer_update(&animation_status->timer, delta_time)) continue;
    animation_phase_next(animation_status);
    if (is_end(animation_status)) {
      struct SpriteComponentUnit spu = {
        entity_id,
        false,
        SPRITE_ID_NONE
      };
      sprite_component_set(&spu);
    } else {
      struct SpriteComponentUnit spu = {
        entity_id,
        true,
        animation_status->animation_phase->sprite_id
      };
      sprite_component_set(&spu);
    }
  }
}


void animation_set(EntityId entity_id, AnimationId animation_id) {
  assert_entity_id(entity_id);
  animation_component.active[entity_id] = true;
  init_status(&animation_component.status[entity_id], animation_id);
  struct SpriteComponentUnit spu = {
    entity_id,
    true,
    animation_component.status[entity_id].animation_phase->sprite_id
  };
  sprite_component_set(&spu);
}
