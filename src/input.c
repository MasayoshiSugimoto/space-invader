#include "input.h"



struct InputTableRow {
  enum GameState game_state;
  KeyboardKey key;
  void (*update_with_input)(KeyboardKey key);
};


struct KeyNamePair {
  KeyboardKey key;
  const char* key_name;
};


void input_log_key_pressed(KeyboardKey key) {
  log_info_f("Key pressed: %s", keyboard_get_key_name(key));
}


KeyboardKey input_get(void) {
  return  getch();
}


KeyboardKey input_process(const struct InputMapping* input_mappings, int length, KeyboardKey key) {
  if (key == ERR) return key;
  input_log_key_pressed(key);
  for (int i = 0; i < length; i++) {
    const struct InputMapping* input_mapping = &input_mappings[i];
    if (input_mapping->key == key || input_mapping->key == KEY_MAX) {
      input_mapping->action(key);
      return key;
    }
  }
  return KEY_MAX;
}