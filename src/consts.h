#ifndef CONST_H
#define CONST_H


#define DEBUG_GAME_BOARD_SHOW_ALL false
#define DEBUG_COLLISION_VISUALISATION_MODE true
#define DEBUG_NO_SCREEN_OUTPUT false  // Needed to see the memory sanitizer output

enum TestMode {
    TEST_MODE_DISABLED,
    TEST_MODE_SINGLE_TEST,
    TEST_MODE_TEST_SUITE,
    TEST_MODE_GAME_MODE_SEQUENCE,
    TEST_MODE_SPRITE_EDITOR,
};
#define TEST_MODE TEST_MODE_GAME_MODE_SEQUENCE

#define TERMINAL_MIN_WIDTH 100
#define TERMINAL_MIN_HEIGHT 30

#define DATA_DIRECTORY "data"
#define DATA_SPRITE_DIRECTORY (DATA_DIRECTORY "/sprites")
#define DATA_SPRITE_SET_DIRECTORY (DATA_DIRECTORY "/sprite_sets")
#define DATA_COLOR_PALETTE_DIRECTORY (DATA_DIRECTORY "/color_palettes")
#define DATA_COLOR_PAIR_PALETTE_DIRECTORY (DATA_DIRECTORY "/color_pair_palettes")

#define SPRITE_DIRECTORY "sprites"
#define SPRITE_EMPTY_SPRITE_FILE_NAME "uninitialized.dat"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 20

#define LOG_FILE "/tmp/space-invaders.log"

#define GAME_INIT_GAME_STATE GAME_STATE_IN_GAME_2_INIT

#define SYSTEM_FILE_NAME_MAX 256
#define SYSTEM_PATH_LENGTH_MAX 4096

#define ARENA_FRAME_SIZE (1024 * 100)
#define ARENA_SYSTEM_SIZE (1024 * 100)

#endif

