#version 330 core

layout (location = 0) vec3 position;
layout (location = 1) vec2 uv;
layout (location = 2) vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out DATA {
	vec2 position;
	vec2 textureCoords;
	vec2 normal;
} vs_out;

void main() {
	vec4 transformPos = modelMatrix * vec4(position, 1.0);
	vec4 fullPos = projectionMatrix * viewMatrix * transformPos;
	vs_out.position = fullPos;
	gl_Position = fullPos;

	vs_out.textureCoords = uvs;
	vs_out.normal = (projectionMatrix * viewMatrix * modelMatrix * vec4(normal, 0.0)).xyz;

}