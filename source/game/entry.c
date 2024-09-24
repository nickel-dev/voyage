Entity* player;

extern void
voyage_entry_proc() {
    load_sprites();

    player = new_entity();
    player->scale = v2(1, .5);
    player->pos = v2(0, .5);
    player->angle = 0;
    player->sprite = SPRITE_NULL;
}

extern void
voyage_update_proc() {
    return;
}

extern void
voyage_render_proc() {
    for (u64 i = 0; i < MAX_ENTITY_COUNT; ++i) {
        Entity* e = &state.entities[i];
        if (e->active)
            entity_draw(e);
            //gfx_draw_quad(gfx.sprite_shader, get_sprite(e->sprite), gfx.projection, e->pos, e->scale, e->angle, v2(1, 1), v2(0, 0));
    }
}

extern void
voyage_exit_proc() {
    return;
}