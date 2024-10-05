#include "screen.h"


struct Screen {
  int width;
  int height;
  ScreenCharacter* screen_buffer; 
  struct ScreenWindow windows[SCREEN_WINDOW_MAX]; 
};


const struct ScreenAlignment SCREEN_ALIGNMENT_TOP_CENTER = {SCREEN_VERTICAL_ALIGNMENT_TOP, SCREEN_HORIZONTAL_ALIGNMENT_CENTER};
const struct ScreenAlignment SCREEN_ALIGNMENT_TOP_RIGHT = {SCREEN_VERTICAL_ALIGNMENT_TOP, SCREEN_HORIZONTAL_ALIGNMENT_RIGHT};
const struct ScreenAlignment SCREEN_ALIGNMENT_CENTER_RIGHT = {SCREEN_VERTICAL_ALIGNMENT_CENTER, SCREEN_HORIZONTAL_ALIGNMENT_RIGHT};
const struct ScreenAlignment SCREEN_ALIGNMENT_BOTTOM_RIGHT = {SCREEN_VERTICAL_ALIGNMENT_BOTTOM, SCREEN_HORIZONTAL_ALIGNMENT_RIGHT};
const struct ScreenAlignment SCREEN_ALIGNMENT_BOTTOM_CENTER = {SCREEN_VERTICAL_ALIGNMENT_BOTTOM, SCREEN_HORIZONTAL_ALIGNMENT_CENTER};
const struct ScreenAlignment SCREEN_ALIGNMENT_BOTTOM_LEFT = {SCREEN_VERTICAL_ALIGNMENT_BOTTOM, SCREEN_HORIZONTAL_ALIGNMENT_LEFT};
const struct ScreenAlignment SCREEN_ALIGNMENT_CENTER_LEFT = {SCREEN_VERTICAL_ALIGNMENT_CENTER, SCREEN_HORIZONTAL_ALIGNMENT_LEFT};
const struct ScreenAlignment SCREEN_ALIGNMENT_TOP_LEFT = {SCREEN_VERTICAL_ALIGNMENT_TOP, SCREEN_HORIZONTAL_ALIGNMENT_LEFT};
const struct ScreenAlignment SCREEN_ALIGNMENT_CENTER_CENTER = {SCREEN_VERTICAL_ALIGNMENT_CENTER, SCREEN_HORIZONTAL_ALIGNMENT_CENTER};


struct Screen l_screen;


void print_char(char c, EntityId entity_id) {
#if DEBUG_COLLISION_VISUALISATION_MODE
  if (c != ' ' && collision_manager_is_collision(entity_id)) {
    attron(COLOR_PAIR(COLOR_PAIR_ID_COLLISION_ON));
    addch(c);
    attroff(COLOR_PAIR(COLOR_PAIR_ID_COLLISION_ON));
  } else {
    addch(c);
  }
#else
  addch(c);
#endif
}


void print_chtype(chtype c, EntityId entity_id) {
#if DEBUG_COLLISION_VISUALISATION_MODE
  if (c != ' ' && collision_manager_is_collision(entity_id)) {
    attron(COLOR_PAIR(COLOR_PAIR_ID_COLLISION_ON));
    addch(c);
    attroff(COLOR_PAIR(COLOR_PAIR_ID_COLLISION_ON));
  } else {
    addch(c);
  }
#else
  addch(c);
#endif
}


struct Screen* screen_get_screen() {
  return &l_screen;
}


void screen_init(struct Screen* screen) {
  int width = SCREEN_WIDTH;
  int height = SCREEN_HEIGHT;

  screen->width = width;
  screen->height = height;
  screen->screen_buffer = malloc(sizeof(ScreenCharacter) * width * height);
  for (int i = 0; i < array_size(screen->windows); i++) {
    screen->windows[i].position = VZERO;
    screen->windows[i].sprite_id = SPRITE_ID_NONE;
  }
}


void screen_render_border(const struct Screen* screen, const struct Vector screen_offset) {
  int left = screen_offset.x - 1;
  int line = screen_offset.y - 1;
  log_info_f("corner={%d, %d}", left, line);

  // Print top border.
  move(line, left);
  addch(ACS_ULCORNER);
  for (int x = 0; x < screen->width; x++) {
    addch(ACS_HLINE);
  }
  addch(ACS_URCORNER);
  line++;

  for (int y = 0; y < screen->height; y++) {
    move(line, left);
    addch(ACS_VLINE);
    move(line, left + 1 + screen->width);
    addch(ACS_VLINE);
    line++;
  }

  // Print bottom border.
  move(line++, left);
  addch(ACS_LLCORNER);
  for (int x = 0; x < screen->width; x++) {
    addch(ACS_HLINE);
  }
  addch(ACS_LRCORNER);
}


struct Vector screen_get_offset(const struct Screen* screen, const struct Terminal* terminal) {
  struct Vector center = terminal_center(terminal);
  struct Vector result = {
    center.x - screen->width / 2,
    center.y - screen->height / 2
  };
  return result;
}


struct RenderingUnit {
  const struct Sprite* sprite;
  EntityId entity_id;
  struct VirtualWindow* window;
  int x;
  int y;
};


int screen_compare_rendering_order(const void* p1, const void* p2) {
  return ((const struct RenderingUnit*)p2)->sprite->sprite_id - ((const struct RenderingUnit*)p1)->sprite->sprite_id;
}


void screen_render_entities(const struct Screen* screen, const struct Vector screen_offset, const struct EntitySystem* entity_system) {
  // We need to render sprites in some particular order. Explosions should be in the back to stay playable.
  struct RenderingUnit rendering_units[ENTITY_MAX];
  int nb_rendering_unit = 0;
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    struct SpriteComponentUnit sprite_unit = sprite_component_get(entity_id);
    if (sprite_unit.sprite_id == SPRITE_ID_NONE || !sprite_unit.active) continue;
    struct Vector top_left = vector_add(entity_system->coordinates[entity_id], screen_offset);
    struct RenderingUnit* rendering_unit = &rendering_units[nb_rendering_unit++];
    rendering_unit->sprite = sprite_get_sprite(sprite_unit.sprite_id);
    rendering_unit->entity_id = entity_id;
    rendering_unit->x = top_left.x;
    rendering_unit->y = top_left.y;
  }

  qsort(rendering_units, nb_rendering_unit, sizeof(rendering_units[0]), &screen_compare_rendering_order);

  for (int i = 0; i < nb_rendering_unit; i++) {
    struct RenderingUnit* rendering_unit = &rendering_units[i];
    const struct Sprite* sprite = rendering_unit->sprite;
    for (int j = 0; j < sprite->buffer_length; j++) {
      int y = sprite_buffer_y(sprite, j);
      int x = sprite_buffer_x(sprite, j);
      move(rendering_unit->y + y, rendering_unit->x + x);
      print_chtype(sprite->buffer[j], rendering_unit->entity_id);
    }
  }
}


void screen_render(struct Screen* screen, struct Terminal* terminal, struct EntitySystem* entity_system) {
  const struct Vector screen_offset = screen_get_offset(screen, terminal);

  screen_render_entities(screen, screen_offset, entity_system);
  screen_render_border(screen, screen_offset);
}


void screen_set_entity_alignment(const struct Screen* screen, struct EntitySystem* entity_system, EntityId entity_id, const struct ScreenAlignment screen_alignment) {
  const struct Sprite* sprite = sprite_get_sprite(sprite_component_get_sprite_id(entity_id));

  struct Vector v = entity_system_get_coordinates(entity_system, entity_id);
  switch (screen_alignment.vertical_alignment) {
    case SCREEN_VERTICAL_ALIGNMENT_NONE:
      // Keep y as is.
      break;
    case SCREEN_VERTICAL_ALIGNMENT_TOP:
      v.y = 0;
      break;
    case SCREEN_VERTICAL_ALIGNMENT_CENTER:
      v.y = screen->height / 2 - sprite->height / 2;
      break;
    case SCREEN_VERTICAL_ALIGNMENT_BOTTOM:
      v.y = screen->height - sprite->height;
      break;
  }

  switch (screen_alignment.horizontal_alignment) {
    case SCREEN_HORIZONTAL_ALIGNMENT_NONE:
      // Keep as is.
      break;
    case SCREEN_HORIZONTAL_ALIGNMENT_LEFT:
      v.x = 0;
      break;
    case SCREEN_HORIZONTAL_ALIGNMENT_CENTER:
      v.x = screen->width / 2 - sprite->width / 2;
      break;
    case SCREEN_HORIZONTAL_ALIGNMENT_RIGHT:
      v.x = screen->width - sprite->width;
      break;
  }

  entity_system_set_coordinates(entity_system, entity_id, v);
}


int screen_get_width() {
  return l_screen.width;
}


int screen_get_height() {
  return l_screen.height;
}


#define SCREEN_RENDERING_UNIT_MAX 256


struct VirtualWindow* _game_screen;
struct RenderingUnit _rendering_units[SCREEN_RENDERING_UNIT_MAX];
int _rendering_unit_count;


void screen_setup(void) {
  memset(&_rendering_units, 0, sizeof(_rendering_units));
  _rendering_unit_count = 0;

  window_manager_init();
  _game_screen = window_manager_window_new(SCREEN_WIDTH, SCREEN_HEIGHT);
  _game_screen->has_border = true;
}


void screen_entities_to_window(const struct EntitySystem* entity_system) {
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    struct SpriteComponentUnit sprite_unit = sprite_component_get(entity_id);
    if (sprite_unit.sprite_id == SPRITE_ID_NONE || !sprite_unit.active) continue;
    struct VirtualWindow* window = window_manager_window_setup_from_sprite(sprite_get_sprite(sprite_unit.sprite_id));
    struct RenderingUnit* rendering_unit = &_rendering_units[_rendering_unit_count++];
    rendering_unit->window = window;
    rendering_unit->entity_id = entity_id;
  }
}


void screen_render_in_game(const struct EntitySystem* entity_system) {
  window_manager_window_center_screen_x(_game_screen);
  window_manager_window_center_screen_y(_game_screen);
  window_manager_window_draw(_game_screen);

  struct Vector top_left = {_game_screen->offset_x, _game_screen->offset_y};
  for (int i = 0; i < _rendering_unit_count; i++) {
    struct RenderingUnit* rendering_unit = &_rendering_units[i];
    struct VirtualWindow* window = rendering_unit->window;
    struct Vector v = vector_add(entity_system->coordinates[rendering_unit->entity_id], top_left);
    window->offset_x = v.x;
    window->offset_y = v.y;
    window_manager_window_draw(rendering_unit->window);
  }
  
  virtual_screen_render();
}
