R"(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out DATA {
	vec3 position;
	vec2 textureCoords;
	vec3 normal;
} vs_out;

void main() {
	vec4 transform = modelMatrix * vec4(position, 1.0);
	gl_Position = projectionMatrix * viewMatrix * transform;

	vs_out.position = transform.xyz;
	vs_out.normal = (modelMatrix * vec4(normal, 0.0)).xyz;
	vs_out.textureCoords = uv;
}
)"