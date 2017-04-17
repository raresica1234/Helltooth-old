R"(#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform float density;
uniform float gradient;

out DATA {
	vec2 textureCoords;
} vs_out;

void main() {
	vec4 positionRelativeToCamera = viewMatrix * modelMatrix * vec4(position, 1.0);
	gl_Position = projectionMatrix * positionRelativeToCamera;

	vs_out.textureCoords = textureCoords;
}

)"