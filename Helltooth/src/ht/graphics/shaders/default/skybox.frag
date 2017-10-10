R"(
#version 330 core

in DATA {
	vec3 position;
} fs_in;

uniform samplerCube skybox;

out vec4 color;

void main() {
	color = texture(skybox, fs_in.position);
}
)"