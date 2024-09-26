Entity* player;

extern void
voyage_entry_proc() {
    load_sprites();
    load_animations();

    gfx.projection = mat_ortho2d(-8, 8, -6, 6, -1, 1);

    player = new_entity();
    player->tags = ENTITY_TAG_PLAYER | ENTITY_TAG_ANIMATED;
    player->scale = v2(1, 1);
    player->pos = v2(0, 0);
    player->anim = ANIM_CHAR_IDLE;
}

extern void
voyage_update_proc() {
    if (input.keys['D']) {
        player->anim = ANIM_CHAR_RUN;
        player->scale.x = 1;

        player->pos.x += 2.5 * time.delta;
    } else if (input.keys['A']) {
        player->anim = ANIM_CHAR_RUN;
        player->scale.x = -1;

        player->pos.x -= 2.5 * time.delta;
    } else if (input.keys[' '])
        player->anim = ANIM_CHAR_AIR;
    else
        player->anim = ANIM_CHAR_IDLE;
}

extern void
voyage_render_proc() {
    for (u64 i = 0; i < MAX_ENTITY_COUNT; ++i) {
        Entity* e = &state.entities[i];
        
        animate(e);
        if (e->active)
            entity_draw(e);
    }
}

extern void
voyage_exit_proc() {
    return;
}