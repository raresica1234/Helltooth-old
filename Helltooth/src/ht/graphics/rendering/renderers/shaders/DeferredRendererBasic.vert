R"(#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;

out DATA {
	vec3 position;
	vec2 textureCoords;
} vs_out;

void main() {
	gl_Position = vec4(position.xy, position.z - 0.5, 1);
	vs_out.position = position;
	vs_out.textureCoords = textureCoords;
}
)"