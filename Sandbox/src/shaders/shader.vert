#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 textureRot;

out vec3 positions;
out vec2 pass_textureCoords;

void main() {
	positions = position;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
	pass_textureCoords = textureCoords;
}