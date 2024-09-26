#ifndef __ENTITY_H_
#define __ENTITY_H_

//
// Sprites
//
enum Sprite_Id {
    SPRITE_NULL = 0,
    SPRITE_ACTOR = 0,
    SPRITE_MAX
};

//
// Animations
//
typedef struct Animation {
    u32 sprite;
    f32 frame_time;
    f32 frame_last_time;
    Vec2i32 frame_size;
    Vec2i32 frame_index;
    Vec2i32 max_index;
} Animation;

//
// Entities
//
enum Entity_Tag {
    ENTITY_TAG_NULL         = 1 << 0,
    ENTITY_TAG_PLAYER       = 1 << 1,
    ENTITY_TAG_ANIMATED     = 1 << 2,
    ENTITY_TAG_MAX
};

typedef struct Entity {
    bool active;
    u64 tags;
    
    // transform
    Vec2 pos, scale;
    f32 angle;

    // Rendering
    union {
        u32 sprite;
        Animation animation;
    };
} Entity;

#endif // __ENTITY_H_