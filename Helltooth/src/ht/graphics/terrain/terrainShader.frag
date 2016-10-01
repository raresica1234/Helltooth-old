R"(

#version 330 core

in vec2 textureCoordinates;

uniform float tilingValue = 40.0;

uniform sampler2D textures[32];

out vec4 color;

void main() {
	color = texture(textures[0], textureCoordinates * tilingValue);
}
)"