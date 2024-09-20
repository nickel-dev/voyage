#include <stdio.h>

int main(int argc, char** argv) {
    Arena arena = new_arena(MEGABYTES(64));
    u8* str = alloc(arena, sizeof(u8) * 7);

    memcpy(str, "Hello1\n", sizeof(u8) * 7);
    
    printf(str);

    arena_clear(&arena);
    arena_free(&arena);

    return 0;
}