#version 400 core

in vec2 textureC;

uniform sampler2D textures[32];

out vec4 color;

void main() {
	color = texture(textures[0], textureC);
}