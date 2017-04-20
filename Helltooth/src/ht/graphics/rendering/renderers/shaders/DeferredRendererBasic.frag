R"(#version 330 core

in DATA {
	vec3 position;
	vec2 textureCoords;
} fs_in;

uniform sampler2D textures[32];

out vec4 color;

void main() {

	//color = vec4(1,1,1,1);

}
)"