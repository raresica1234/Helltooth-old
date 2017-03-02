#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 textureRot;

uniform float density;
uniform float gradient;

out vec3 normal;
out vec3 toLightVector;
out vec3 toCameraVector;
out vec2 pass_textureCoords;
out float visibility;

vec3 lightPosition = vec3(0, -1.0, -1.0);

void main() {
	vec4 worldPosition = modelMatrix * vec4(position, 1.0);
	vec4 positionRelativeToCam = viewMatrix * worldPosition;

	gl_Position = projectionMatrix * positionRelativeToCam;
	pass_textureCoords = textureCoords;
	lightPosition = (vec4(lightPosition, 0.0) * modelMatrix).xyz;

	normal = (modelMatrix * vec4(normals, 0.0)).xyz;
	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

	float distance = length(positionRelativeToCam.xyz);
	visibility = exp(-pow(distance * density, gradient));
	visibility = clamp(visibility, 0.0, 1.0);

}