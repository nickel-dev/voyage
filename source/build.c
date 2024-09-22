#include "base/base_inc.h"

#define STATIC_ARENA_SIZE MEGABYTES(256)
#define TEMP_ARENA_SIZE   MEGABYTES(8)

// The static_arena has to be cleared by the user and is cleared at the end of  the programs lifetime.
// The temp_arena is automatically cleared at the beginning of every frame.
global Arena static_arena, temp_arena;

#define GAME_ENTRY_FUNC  void cb_game_entry()
#define GAME_UPDATE_FUNC void cb_game_update()
#define GAME_RENDER_FUNC void cb_game_render()
#define GAME_EXIT_FUNC   void cb_game_exit()

GAME_ENTRY_FUNC;
GAME_UPDATE_FUNC;
GAME_RENDER_FUNC;
GAME_EXIT_FUNC;

#include "engine/engine_inc.h"
#include "engine/example/entry.c"