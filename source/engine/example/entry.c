void voyage_entry_proc() {
    return;
}

void voyage_update_proc() {
    return;
}

void voyage_render_proc() {
    persist u64 i = 0;
	gfx_draw_quad(gfx.sprite_shader, NULL, gfx.projection, v3(.5, 1, 0), v2(2, 1), v2(1, 1), v2(0, 0), (f32)++i / 1000);
}

void voyage_exit_proc() {
    return;
}