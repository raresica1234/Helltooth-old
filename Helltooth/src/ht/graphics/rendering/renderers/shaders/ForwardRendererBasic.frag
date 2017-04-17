R"(#version 330 core

in DATA {
	vec2 textureCoords;
} fs_in;

uniform sampler2D textures[32];

layout(location = 0) out vec4 color;

void main() {

	color = texture(textures[0], fs_in.textureCoords);
}
)"