#version 400 core

in vec3 positions;
in vec2 pass_textureCoords;

uniform sampler2D textureSampler;

out vec4 color;

void main(){

	color = texture(textureSampler, pass_textureCoords);
}