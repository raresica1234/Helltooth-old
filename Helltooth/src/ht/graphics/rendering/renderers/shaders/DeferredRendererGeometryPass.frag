R"(
#version 330 core

in DATA {
	vec3 position;
	vec2 textureCoords;
	vec3 normal;
} fs_in;

uniform sampler2D textures[32];

layout (location = 0) out vec4 diffuseColor;
layout (location = 1) out vec4 position;
layout (location = 2) out vec4 normals;

void main() {

	diffuseColor = texture(textures[0], fs_in.textureCoords);
	position = vec4(fs_in.position, 1.0);
	normals = vec4(fs_in.normal, 1.0);
}
)"