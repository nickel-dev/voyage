#ifndef __ENTITY_H_
#define __ENTITY_H_

//
// Sprites
//
// \class Hashmap bucket for sprites
typedef struct Sprite_Bucket {
    string key;
    Sprite value;
} Sprite_Bucket;

enum Sprite_Id {
    SPRITE_NULL = 0,
    SPRITE_ACTOR,
    SPRITE_CHAR,
    SPRITE_MAX
};

//
// Animations
//
enum Animation_Id {
    ANIM_NULL = 0,
    ANIM_CHAR_IDLE,
    ANIM_CHAR_RUN,
    ANIM_CHAR_AIR,
    ANIM_MAX
};

typedef struct Animation {
    u32 sprite;
    f32 frame_time, frame_last_time;
    Vec2i32 start_index, max_index, frame_size, frame_index;
} Animation;

//
// Entities
//
enum Entity_Tag {
    ENTITY_TAG_NULL     = 1 << 0,
    ENTITY_TAG_PLAYER   = 1 << 1,
    ENTITY_TAG_ANIMATED = 1 << 2,
    ENTITY_TAG_MAX
};

typedef struct Entity {
    bool active;
    u64 tags;
    
    // Transform
    Vec2 pos, scale;
    f32 angle;

    // Rendering
    union {
        u32 sprite;
        u32 anim;
    };
} Entity;

#endif // __ENTITY_H_