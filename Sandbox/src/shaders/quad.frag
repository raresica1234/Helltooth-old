#version 330 core

in vec2 textureC;

uniform sampler2D textures[32];

layout(location = 0) out vec4 color;

void main() {
	//color = texture(textures[0], textureC);
	color = vec4(1.0, 1.0, 1.0, 1.0);
}