R"(
#version 330 core

in DATA {
	vec3 position;
	vec2 textureCoords;
	vec3 normal;
} fs_in;

uniform sampler2D textures[32];

layout(location = 0) out vec4 color;

struct Light {
	vec3 color;
	vec3 direction;
	vec3 position;
	vec3 attenuation;
	vec2 cutoffExponent;
};

uniform Light light;

uniform float minimumBrightness = 0.0;

out vec4 color;

void main() {
	vec3 diffuse = texture(textures[0], fs_in.textureCoords).xyz;

	vec3 dirToLight = light.position - fs_in.position;
	float distToLight = length(dirToLight);

	dirToLight = normalize(dirToLight);

	float NdotL = dot(fs_in.normal, dirToLight);
	float attenuation = 0;

	NdotL = max(NdotL, minimumBrightness);

	if(NdotL > 0.0) {
		float spotEffect = dot(light.direction, -dirToLight);
		if(spotEffect > light.cutoffExponent.x) {
			spotEffect = pow(abs(spotEffect), light.cutoffExponent.y);
			attenuation = spotEffect / (light.attenuation.x + light.attenuation.y * distToLight + light.attenuation.z * distToLight * distToLight);
		}
	}

	color = vec4(light.color * diffuse * attenuation * NdotL, 1);
}
)"