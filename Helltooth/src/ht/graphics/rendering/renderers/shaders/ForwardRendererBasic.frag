R"(#version 330 core

in DATA {
	vec2 textureCoords;
	float visibility;
} fs_in;

uniform sampler2D textures[32];
uniform vec4 skyColor;

layout(location = 0) out vec4 color;

void main() {
	//if(fs_in.visibility < 0.1)
	//	discard;

	color = texture(textures[0], fs_in.textureCoords);
	//color = mix(skyColor, color, fs_in.visibility);
}
)"