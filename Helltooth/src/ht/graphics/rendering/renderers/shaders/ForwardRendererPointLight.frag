R"(
#version 330 core

in DATA {
	vec3 position;
	vec2 textureCoords;
	vec3 normal;
} fs_in;

uniform sampler2D textures[32];

struct Light {
	vec3 position;
	vec3 color;
	vec3 attenuation;
};

uniform Light light;

uniform float minimumBrightness = 0.0;

layout(location = 0) out vec4 color;

void main() {

	vec3 diffuse = texture(textures[0], fs_in.textureCoords).xyz;

	vec3 dir = light.position - fs_in.position;
	float dist = length(dir);

	dir = normalize(dir);

	float attenuation = 1.0f / (light.attenuation.x + light.attenuation.y * dist + light.attenuation.z * dist * dist);

	float brightness = max(dot(dir, fs_in.normal) * attenuation, minimumBrightness);

	color = vec4(light.color * diffuse * brightness, 1.0);
}
)"