inline void
seed_random(u32 s) {
    persist u32 __rand_seed = 1;
    __rand_seed = s;
}

inline i32
random() {
    persist u32 __rand_seed = 1;
    __rand_seed = (1664525 * __rand_seed + 1013904223) % 4294967296;
    return (i32)__rand_seed;
}

inline i32
random_range(i32 min, i32 max) {
    return random() % (++max - min) + min;
}