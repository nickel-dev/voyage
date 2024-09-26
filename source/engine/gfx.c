#ifndef __GFX_H_
#define __GFX_H_

typedef struct Gfx_Sprite {
    Vec2i32 scale;
    i32 channel_count;
    u32 id;
} Gfx_Sprite;

typedef struct Gfx_Vertex {
    Vec3 pos;
    Vec2 tex_coord;
} Gfx_Vertex;

global struct Gfx_State {
    u32 vao, vbo, ebo; // OpenGL shader objects
	u32 sprite_shader;
	Mat projection;
	Gfx_Sprite error_sprite;
} gfx;

// gfx implementation
u32
gfx_load_shader(const char* vertex_source, const char* fragment_source) {
	u32 result;
	u32 vertex;
	u32 fragment;
	i32 success;
	GLchar error_log[1024];

	// Create vertex shader.
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, (const GLchar* const*)&vertex_source, NULL);
	glCompileShader(vertex);
	
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(vertex, 512, NULL, error_log);
	if (!success)
		printf("Failed to compile vertex shader. Error log: %s\n", error_log);
	
	// Create fragment shader.
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, (const GLchar* const*)&fragment_source, NULL);
	glCompileShader(fragment);
	
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(fragment, 512, NULL, error_log);
	if (!success)
		printf("Failed to compile fragment shader. Error log: %s\n", error_log);
	
	// Create and Link shader program.
	result = glCreateProgram();
	glAttachShader(result, vertex);
	glAttachShader(result, fragment);
	glLinkProgram(result);
	
	glGetProgramiv(result, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(result, 512, NULL, error_log);
	if (!success)
		printf("Failed to link shader program. Error log: %s\n", error_log);
	
	// Delete unsused shaders.
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	return result;
}

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

inline Gfx_Sprite
gfx_create_sprite_from_v4(Vec4 color) {
	u8 data[] = {
		(u8)color.x * 255,
		(u8)color.y * 255,
		(u8)color.z * 255,
		(u8)color.w * 255
	};
    return gfx_create_sprite((const u8*)data, v2i32(1, 1), 4);
}

inline Gfx_Sprite
gfx_create_sprite_from_v4i32(Vec4i32 color) {
	u8 data[] = {color.x, color.y, color.z, color.w};
    return gfx_create_sprite((const u8*)data, v2i32(1, 1), 4);
}

Gfx_Sprite
gfx_load_sprite(const char* path) {
    Vec2i32 scale;
    i32 channel_count;

	//string s = file_read_to_string(temp_arena, path);
	stbi_set_flip_vertically_on_load(true);
    const u8* data = stbi_load(path, &scale.x, &scale.y, &channel_count, 4);
    assert(data, "Loading sprite failed! path: %s", path);
    Gfx_Sprite result = gfx_create_sprite(data, scale, channel_count);
	stbi_image_free((void*)data);
	
	return result;
}

void
gfx_draw_quad(u32 shader, Gfx_Sprite* sprite, Mat proj_mat, Vec2 pos, Vec2 scale, f32 angle, Vec2 atlas_scale, Vec2i32 atlas_pos) {
	if (!shader)
		shader = gfx.sprite_shader;
	
	if (!sprite)
		glBindTexture(GL_TEXTURE_2D, gfx.error_sprite.id);
	else
		glBindTexture(GL_TEXTURE_2D, sprite->id);
	
	glUseProgram(shader);

	glUniform1f(glGetUniformLocation(shader, "Texture"), 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "Projection"), 1, 0, &proj_mat.e[0]);
	glUniform2f(glGetUniformLocation(shader, "Pos"), pos.x, pos.y);
	glUniform2f(glGetUniformLocation(shader, "Scale"), scale.x, scale.y);
	glUniform2f(glGetUniformLocation(shader, "TexSize"), gfx.error_sprite.scale.x, gfx.error_sprite.scale.y);
	glUniform2f(glGetUniformLocation(shader, "AtlasScale"), atlas_scale.x, atlas_scale.y);
	glUniform2f(glGetUniformLocation(shader, "AtlasPos"), atlas_pos.x, -atlas_pos.y);
	glUniform1f(glGetUniformLocation(shader, "Angle"), angle);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void
gfx_init() {
	// Create buffers
	Gfx_Vertex vertices[] = {
		{{-0.5,  0.5, 0}, {0, 1}},
		{{ 0.5,  0.5, 0}, {1, 1}},
		{{ 0.5, -0.5, 0}, {1, 0}},
		{{-0.5, -0.5, 0}, {0, 0}}
	};
	u32 indices[] = {
		0, 1, 3, // Triangle 1
		1, 2, 3  // Triangle 2
	};

	glGenVertexArrays(1, &gfx.vao);
	glGenBuffers(1, &gfx.vbo);
	glGenBuffers(1, &gfx.ebo);

	glBindVertexArray(gfx.vao);
	glBindBuffer(GL_ARRAY_BUFFER, gfx.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gfx.ebo);
	
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Gfx_Vertex), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(u32), indices, GL_STATIC_DRAW);

	/// Position Vector
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Gfx_Vertex), NULL);

	/// UV Coordinate
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Gfx_Vertex), (void*)sizeof(Vec3));

	// Load shaders
	gfx.sprite_shader = gfx_load_shader(
		"#version 460 core\n\
		layout (location = 0) in vec3 aPos;\n\
		layout (location = 1) in vec2 aTexCoord;\n\
		out vec2 texCoord;\n\
		uniform mat4 Projection;\n\
		uniform vec2 Pos;\n\
		uniform vec2 Scale;\n\
		uniform vec2 TexSize;\n\
		uniform vec2 AtlasScale;\n\
		uniform vec2 AtlasPos;\n\
		uniform float Angle;\n\
		vec2 rotate(vec2 v, float a) {\n\
			float s = sin(a);\n\
			float c = cos(a);\n\
			mat2 m = mat2(c, s, -s, c);\n\
			return m * v;\n\
		}\n\
		void main() {\n\
			gl_Position = Projection * vec4(Pos + rotate(aPos.xy * Scale, Angle), 0.0, 1.0);\n\
			texCoord = (aTexCoord + AtlasPos - vec2(0, 1)) / AtlasScale;\n\
		}",

		"#version 460 core\n\
		uniform sampler2D Texture;\n\
		out vec4 fragColor;\n\
		in vec2 texCoord;\n\
		void main() {\n\
			fragColor = texture(Texture, texCoord);\n\
		}"
	);

	// OpenGL switches
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create error texture
	gfx.error_sprite = gfx_create_sprite_from_v4(v4(1, 0, 1, 1));
}

#endif // __GFX_H_