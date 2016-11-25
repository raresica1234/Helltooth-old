#version 330 core

in float render;
in vec3 normal;
in vec3 toLightVector;
in vec3 toCameraVector;
in vec2 pass_textureCoords;

uniform sampler2D textures[32];

layout(location = 0) out vec4 color;

float ambientLight = 0.2;

void main(){
	if(render){
		discard;
	}
	
	color = texture(textures[0], pass_textureCoords);
	vec4 currentSpecular = texture(textures[1], pass_textureCoords);

	vec3 unitNormal = normalize(normal);
	vec3 unitVectorToCamera = normalize(toCameraVector);
	vec3 lightDirection = -normalize(toLightVector);
	vec3 tolightDirection = normalize(toLightVector);

	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

	float diffuseDot = dot(unitNormal, tolightDirection);
	float brightness = max(diffuseDot, ambientLight);


	float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);

	specularFactor = max(specularFactor, 0.0);
	float dampedFactor = pow(specularFactor, 0.5);

	dampedFactor = pow(dampedFactor, 1 - currentSpecular.r);

	color = color * max(brightness * dampedFactor, ambientLight);
	//color = vec4(normal.x / 2 +0.3, normal.y, normal.z, pass_textureCoords.x);
}