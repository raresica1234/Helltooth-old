R"(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;

uniform mat4 projectionViewMatrix;
uniform mat4 modelMatrix;

uniform float density;
uniform float gradient;

out DATA {
	vec3 position;
	vec2 textureCoords;
	vec3 normal;
} vs_out;

void main() {
	vec4 worldPosition = modelMatrix * vec4(position, 1.0);
	vec4 pos = projectionViewMatrix * worldPosition;
	gl_Position = pos;

	vs_out.textureCoords = textureCoords;
	vs_out.position = worldPosition.xyz;

	vs_out.normal = (modelMatrix * vec4(normals, 0.0)).xyz;
}

)"