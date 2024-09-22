#define STATIC_ARENA_SIZE MEGABYTES(32)
#define TEMP_ARENA_SIZE MEGABYTES(8)

// These procedures have to be defined by your game.
void voyage_entry_proc();
void voyage_update_proc();
void voyage_render_proc();
void voyage_exit_proc();

// If you change the name of the procedures above, you have to change them here to.
// These macros get called by the engine.
#define VOYAGE_ENTRY_PROC  voyage_entry_proc
#define VOYAGE_UPDATE_PROC voyage_update_proc
#define VOYAGE_RENDER_PROC voyage_render_proc
#define VOYAGE_EXIT_PROC   voyage_exit_proc

#include "base/base_inc.h"
#include "engine/engine_inc.h"
#include "engine/example/entry.c"