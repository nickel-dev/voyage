Entity* player;

extern void
voyage_entry_proc() {
    load_sprites();

    player = new_entity();
    player->scale = v2(1, 1);
    player->pos = v2(0, 0);
    player->angle = 0;
    player->sprite = SPRITE_NULL;
    player->tags = ENTITY_TAG_PLAYER | ENTITY_TAG_ANIMATED;

    player->animation = (Animation){
        .sprite = SPRITE_NULL,
        .frame_index = v2i32(0, 0),
        .frame_size = v2i32(150, 150),
        .frame_time = 0.2,
        .max_index = v2i32(7 , 0)
    };
}

extern void
voyage_update_proc() {
    return;
}

extern void
voyage_render_proc() {

    for (u64 i = 0; i < MAX_ENTITY_COUNT; ++i) {
        Entity* e = &state.entities[i];
        
        animate(&e->animation);
        if (e->active)
            entity_draw(e);
    }
}

extern void
voyage_exit_proc() {
    return;
}