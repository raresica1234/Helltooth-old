R"(
#version 330 core

in DATA {
	vec3 position;
	vec2 textureCoords;
	vec3 normal;
} fs_in;

uniform sampler2D textures[32];

struct Light {
	vec3 color;
	vec3 direction;
};

uniform Light light;

uniform float minimumBrightness = 0.0;

layout(location = 0) out vec4 color;

void main() {

	vec3 diffuse =	(texture(textures[0], fs_in.textureCoords)).xyz;

	float brightness = dot(-light.direction, fs_in.normal);
	brightness = max(brightness, minimumBrightness);
	color =  vec4((light.color * diffuse) *	brightness, 1);
}
)"