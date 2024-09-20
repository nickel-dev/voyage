#if VERTEX_SHADER

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main() {
    gl_Position = Projection  * vec4(aPos, 1);
    texCoord = aTexCoord;
}

#elif FRAGMENT_SHADER

uniform sampler2D Texture;

out vec4 fragColor;

in vec2 texCoord;

void main() {
    fragColor = texture(Texture, texCoord);
}

#endif