#ifndef __GFX_H_
#define __GFX_H_

typedef struct Gfx_Sprite {
    Vec2i32 scale;
    i32 channel_count;
    u32 id;
} Gfx_Sprite;

global struct Gfx_State {
    u32 vao, vbo, ebo; // OpenGL shader objects
} gfx;

void gfx_init();

Gfx_Sprite
gfx_create_sprite(const u8* data, Vec2i32 scale, i32 channel_count) {
	Gfx_Sprite sprite;
	sprite.scale = scale;
	sprite.channel_count = channel_count;

	assert(data, "NULL is not a valid texture!");

	glGenTextures(1, &sprite.id);
	glBindTexture(GL_TEXTURE_2D, sprite.id);
	
	u32 format = GL_RGB;
	if (channel_count >= 4)
		format = GL_RGBA;
	
	glTexImage2D(GL_TEXTURE_2D, 0, format, sprite.scale.x, sprite.scale.y, 0, format, GL_UNSIGNED_BYTE, data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);
	return sprite;
}

Gfx_Sprite
gfx_load_sprite(const u8* path) {
    Vec2i32 scale;
    i32 channel_count;

    u8* data = stbi_load(path, &scale.x, &scale.y, &channel_count, 4);
    assert(data, "Loading sprite failed! path: %s", path);

    return gfx_create_sprite(data, scale, channel_count);
}

#endif // __GFX_H_