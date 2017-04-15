#version 330 core

in DATA {
	vec2 position;
	vec2 textureCoords;
	vec2 normal;
} fs_in;

uniform sampler2D textures[32];

layout (location = 0) out vec4 diffuseColor;
layout (location = 1) out vec4 position;
layout (location = 3) out vec4 normals;
layout (location = 2) out vec4 uvs;

int main() {

	position = fs_in.position;
	uvs = fs_in.textureCoords;
	normals = fs_in.normal;
	diffuseColor = texture(textures[0], fs_in.textureCoords);
}