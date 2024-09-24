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
global Arena static_arena;
global Arena temp_arena;

global struct Os_Window {
	bool should_close;
    string title;
    i32 width, height;
    i32 x, y;
    i32 screen_width, screen_height;
    f32 zoom;
    Vec3 clear_color;
#if OS_WINDOWS
    HWND handle;
	HDC device;
#endif
} window;

global struct Time {
    f64 now, last, delta;
    f32 seconds_counter;
    i32 frame_count, fps;
} time;

global Input_Profile input;

// Functionality
#include "gfx.c"
#include "os_entry.c"