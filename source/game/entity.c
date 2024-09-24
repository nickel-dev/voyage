//
// Sprites
//
enum Sprite_Id {
    SPRITE_NULL = 0,
    SPRITE_ACTOR = 0,
    SPRITE_MAX
};

global Gfx_Sprite sprites[SPRITE_MAX];

Gfx_Sprite*
get_sprite(u32 id) {
    assert(id < SPRITE_MAX, "Sprite id reached over the set limit! limit: %llu", SPRITE_MAX);
    return &sprites[id];
}

void
load_sprites() {
    sprites[SPRITE_NULL]  = gfx_load_sprite("data/images/null.png");
    sprites[SPRITE_ACTOR] = gfx_load_sprite("data/images/actor.png");
}

//
// Entities
//
enum Entity_Arch {
    ENTITY_ARCH_NULL = 0,
    ENTITY_ARCH_MAX
};

typedef struct Entity {
    bool active;
    
    // transform
    Vec2 pos, scale;
    f32 angle;

    // id
    u32 sprite;
    u32 arch;
} Entity;

void
entity_draw(Entity* e) {
    Gfx_Sprite* sprite = get_sprite(e->sprite);
    gfx_draw_quad(gfx.sprite_shader, sprite, gfx.projection, e->pos, e->scale, e->angle, v2((f32)sprite->scale.x / 172.0, (f32)sprite->scale.y / 183.0), v2(0, 0));
}