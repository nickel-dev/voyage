#define STATIC_ARENA_SIZE MEGABYTES(32)
#define TEMP_ARENA_SIZE MEGABYTES(8)

// These procedures have to be defined by your game.
extern void voyage_entry_proc();
extern void voyage_update_proc();
extern void voyage_render_proc();
extern void voyage_exit_proc();

// If you change the name of the procedures above, you have to change them here to.
// These macros get called by the engine.
#define VOYAGE_ENTRY_PROC  voyage_entry_proc
#define VOYAGE_UPDATE_PROC voyage_update_proc
#define VOYAGE_RENDER_PROC voyage_render_proc
#define VOYAGE_EXIT_PROC   voyage_exit_proc

#include "base/_inc.h"
#include "engine/_inc.h"
#include "game/_inc.h"