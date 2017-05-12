R"(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;
layout (location = 2) in float tID;
layout (location = 3) in vec4 colors;


uniform mat4 projectionMatrix;

out vec2 textureCoord;
out vec4 color;
out float texID;

void main() {

	vec4 pos = projectionMatrix * vec4(position, 1.0);
	gl_Position = vec4(pos.xy, 0.0, 1.0);

	textureCoord = uvs;
	color = colors;
	texID = tID;
}
)"