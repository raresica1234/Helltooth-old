R"(#version 330 core

in DATA {
	vec3 position;
	vec2 textureCoords;
	vec3 normal;
} fs_in;

uniform sampler2D textures[32];

layout(location = 0) out vec4 color;

struct Light {
	int type;
	vec3 color;
	vec3 direction;
	vec3 position;
	vec3 attenuation;
	vec2 cutoffExponent;
};

uniform Light light;

vec4 processDirectionalLight(Light light, vec3 diffuse, vec3 normal){
	return vec4((light.color * diffuse) * dot(-light.direction, normal), 1);
}

vec4 processPointLight(Light light, vec3 position, vec3 diffuse, vec3 normal) {
	vec3 dir = light.position - position;
	float dist = length(dir);

	dir = normalize(dir);

	float attenuation = 1.0f / (light.attenuation.x + light.attenuation.y * dist + light.attenuation.z * dist * dist + 0.0000001f);

	float brightness = dot(normal, dir) * attenuation;

	return vec4(light.color * diffuse * vec3(brightness), 1);
}

vec4 processSpotLight(Light light, vec3 position, vec3 diffuse, vec3 normal) {
	vec3 dirToLight = light.position - position;
	float distToLight = length(dirToLight);

	dirToLight = normalize(dirToLight);

	float NdotL = dot(normal, dirToLight);
	float attenuation = 0;

	if(NdotL > 0.0) {
		float spotEffect = dot(light.direction, -dirToLight);
		if(spotEffect > light.cutoffExponent.x) {
			spotEffect = pow(abs(spotEffect), light.cutoffExponent.y);
			attenuation = spotEffect / (light.attenuation.x + light.attenuation.y * distToLight + light.attenuation.z * distToLight * distToLight);
		}
	}

	return vec4(light.color * diffuse * attenuation * NdotL, 1);
}

void main() {
	vec3 diffuse = texture(textures[0], fs_in.textureCoords).xyz;

	if(light.type == 1) // 1 -> directional light
		color = processDirectionalLight(light, diffuse, fs_in.normal);
	else if(light.type == 2) // 2 -> point light
		color = processPointLight(light, fs_in.position, diffuse, fs_in.normal);
	else if(light.type == 3) // 3-> spot light
		color = processSpotLight(light, fs_in.position, diffuse, fs_in.normal);
	
	//color = vec4(light.color, 1.0);

}

)"