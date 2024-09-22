GAME_ENTRY_FUNC {

}

GAME_UPDATE_FUNC {

}

GAME_RENDER_FUNC {
    persist u64 i = 0;
	gfx_draw_quad(gfx.sprite_shader, NULL, gfx.projection, v3(1, 1, 0), v2(2, 1), v2(1, 1), v2(0, 0), (f32)++i / 1000);
}

GAME_EXIT_FUNC {

}