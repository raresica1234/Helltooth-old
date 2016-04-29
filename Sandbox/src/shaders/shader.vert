#version 400 core

layout (location = 0) in vec3 position;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;


out vec3 positions;

void main() {
	positions = (projectionMatrix * vec4(position, 1.0)).xyz;
	gl_Position = vec4(positions, 1.0);
}