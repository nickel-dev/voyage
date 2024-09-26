//
// Sprites
//
global Gfx_Sprite sprites[SPRITE_MAX];

Gfx_Sprite*
get_sprite(u32 id) {
    assert(id < SPRITE_MAX, "Sprite id reached over the set limit! limit: %llu", SPRITE_MAX);
    return &sprites[id];
}

void
load_sprites() {
    sprites[SPRITE_NULL]  = gfx_load_sprite("data/images/null.png");
    sprites[SPRITE_ACTOR] = gfx_load_sprite("data/images/warrior/Idle.png");
}

//
// Animation
//
void
animate(Animation* anim) {
    if (anim->frame_last_time + anim->frame_time < (f32)time.now)
        anim->frame_last_time = (f32)time.now;
    else return;

    anim->frame_index.x += 1;
    if (anim->frame_index.x > anim->max_index.x) {
        anim->frame_index.x = 0;
        anim->frame_index.y += 1;
    }

    if (anim->frame_index.y > anim->max_index.y)
        anim->frame_index = v2i32(0, 0);
}


//
// Entities
//
void
entity_draw(Entity* e) {
    if (e->tags & ENTITY_TAG_ANIMATED) {
        Gfx_Sprite* sprite = get_sprite(e->animation.sprite);
        gfx_draw_quad(gfx.sprite_shader, sprite, gfx.projection, e->pos, e->scale, e->angle, v2_div(v2_convert(sprite->scale), v2_convert(e->animation.frame_size)), e->animation.frame_index);
    }
    else {
        Gfx_Sprite* sprite = get_sprite(e->sprite);
        gfx_draw_quad(gfx.sprite_shader, sprite, gfx.projection, e->pos, e->scale, e->angle, v2(1, 1), v2i32(0, 0));
    }
}