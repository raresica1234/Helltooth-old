R"(
#version 330 core

in DATA {
	vec3 position;
	vec2 textureCoords;
} fs_in;

uniform sampler2D textures[3];
uniform float minimumBrightness = 0.0;

struct Light {
	vec3 color;
	vec3 direction;
	vec3 position;
	vec3 attenuation;
	vec2 cutoffExponent;
};

uniform Light light;

out vec4 color;

void main() {
	vec3 diffuse = texture(textures[0], fs_in.textureCoords).xyz;
	vec3 position = texture(textures[1], fs_in.textureCoords).xyz;
	vec3 normal = texture(textures[2], fs_in.textureCoords).xyz;

	vec3 dirToLight = light.position - position;
	float distToLight = length(dirToLight);

	dirToLight = normalize(dirToLight);

	float NdotL = dot(normal, dirToLight);
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