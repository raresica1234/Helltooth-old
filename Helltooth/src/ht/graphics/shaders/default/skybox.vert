R"(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normals;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out DATA {
	vec3 position;
} vs_out;

void main() {
	vs_out.position = position;

	vec3 pos = vec3(position.x * 900.0f, position.y * 900.0f, position.z * 900.0f);
	gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1.0);
}
)"