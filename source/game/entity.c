//
// Sprites
//
global Sprite sprites[SPRITE_MAX];
global Animation animations[ANIM_MAX];

Sprite*
get_sprite(u32 id) {
    assert(id < SPRITE_MAX, "Sprite id reached over the set limit! limit: %llu", SPRITE_MAX);
    return &sprites[id];
}

void
load_sprites() {
    sprites[SPRITE_NULL]  = gfx.error_sprite;
    sprites[SPRITE_ACTOR] = gfx_load_sprite("data/images/warrior/Idle.png");
    sprites[SPRITE_CHAR]  = gfx_load_sprite("data/images/char.png");
}

//
// Animation
//
Animation*
get_anim(u32 id) {
    assert(id < ANIM_MAX, "Animation id reached over the set limit! limit: %llu", ANIM_MAX);
    return &animations[id];
}

void
load_animations() {
    animations[ANIM_NULL]  = (Animation){
        .sprite = SPRITE_NULL,
        .start_index = v2i32(0, 0),
        .max_index = v2i32(0, 0),
        .frame_size = v2i32(1, 1),
        .frame_time = 1
    };

    animations[ANIM_CHAR_IDLE] = (Animation){SPRITE_CHAR, 0.25, 0, v2i32(0, 0), v2i32(1, 0), v2i32(8, 8), v2i32(0, 0)};
    animations[ANIM_CHAR_RUN]  = (Animation){SPRITE_CHAR, 0.15, 0, v2i32(0, 1), v2i32(1, 1), v2i32(8, 8), v2i32(0, 1)};
    animations[ANIM_CHAR_AIR]  = (Animation){SPRITE_CHAR, 1.00, 0, v2i32(0, 2), v2i32(0, 2), v2i32(8, 8), v2i32(0, 2)};
}

//
// Entities
//
void
animate(Entity* e) {
    Animation* anim = get_anim(e->anim);

    if (anim->frame_last_time == 0.0)
        anim->frame_index = anim->start_index;

    if (anim->frame_last_time + anim->frame_time < (f32)time.now)
        anim->frame_last_time = (f32)time.now;
    else return;

    if (++anim->frame_index.x > anim->max_index.x) {
        anim->frame_index.x = anim->start_index.x;
        
        if (++anim->frame_index.y > anim->max_index.y)
            anim->frame_index = anim->start_index;
    }
}

void
entity_draw(Entity* e) {
    if (e->tags & ENTITY_TAG_ANIMATED) {
        Animation* anim = get_anim(e->anim);
        Sprite* sprite = get_sprite(anim->sprite);
        gfx_draw_quad(gfx.sprite_shader, sprite, gfx.projection, e->pos, e->scale, e->angle, v2_div(v2_convert(sprite->scale), v2_convert(anim->frame_size)), anim->frame_index);
    }
    else {
        Sprite* sprite = get_sprite(e->sprite);
        gfx_draw_quad(gfx.sprite_shader, sprite, gfx.projection, e->pos, e->scale, e->angle, v2(1, 1), v2i32(0, 0));
    }
}