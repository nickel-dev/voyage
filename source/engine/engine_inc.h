#ifndef STATIC_ARENA_SIZE
#define STATIC_ARENA_SIZE MEGABYTES(64)
#warning You forgot to define the STATIC_ARENA_SIZE! Defaults to 64MB.
#endif

#ifndef TEMP_ARENA_SIZE
#define TEMP_ARENA_SIZE MEGABYTES(8)
#warning You forgot to define the TEMP_ARENA_SIZE! Defaults to 8MB.
#endif

// Base engine
#include "third_party.c"
#include "vector.c"
#include "matrix.c"
#include "input.c"

// The static_arena has to be cleared by the user and is cleared at the end of  the programs lifetime.
// The temp_arena is automatically cleared at the beginning of every frame.
global Arena static_arena, temp_arena;
global Input_Profile input;

// Functionality
#include "gfx.c"
#include "os_entry.c"