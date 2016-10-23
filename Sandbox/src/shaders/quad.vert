#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

out vec2 textureC;

void main() {
	gl_Position = projectionMatrix * modelMatrix * vec4(position, 1.0);
	textureC.x = 1 - textureCoords.x;
	textureC.y = 1 - textureCoords.y;
}