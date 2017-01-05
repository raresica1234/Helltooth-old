#include "TerrainShader.h"

namespace ht { namespace graphics {

	TerrainShader::TerrainShader(TerrainShaderType type)
		: vertexShader(330, true), fragmentShader(330, true) {

		/*#version 330 core

			layout(location = 0) in vec3 position;
		layout(location = 1) in vec2 textureCoords;
		layout(location = 2) in vec3 normals;

		uniform mat4 projectionMatrix;
		uniform mat4 modelMatrix;
		uniform mat4 viewMatrix;

		out vec2 textureCoordinates;

		void main() {
			gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
			textureCoordinates = textureCoords;
		}"*/

		vertexShader.addInputVariable("position", VEC3, POSITIONS);
		vertexShader.addInputVariable("textureCoords", VEC2, TEXTURECOORDINATES);
		vertexShader.addInputVariable("normals", VEC3, NORMALS);

		vertexShader.addVariable("projectionMatrix", MAT4, UNIFORM);
		vertexShader.addVariable("modelMatrix", MAT4, UNIFORM);
		vertexShader.addVariable("viewMatrix", MAT4, UNIFORM);
		vertexShader.addVariable("lightPosition = vec3(0.0, 10000.0, 0.0)", VEC3);
		vertexShader.addVariable("density", FLOAT, UNIFORM);
		vertexShader.addVariable("gradient", FLOAT, UNIFORM);

		vertexShader.addOutputVariable("textureCoordinates", VEC2);
		vertexShader.addOutputVariable("surfaceNormal", VEC3);
		vertexShader.addOutputVariable("toLightVector", VEC3);
		vertexShader.addOutputVariable("visibility", FLOAT);

		/*float distance = length(positionRelativeToCam.xyz);
		visibility = exp(-pow(distance * density, gradient));
		visibility = clamp(visibility, 0.0, 1.0);*/

		vertexShader.addMainCode("vec4 worldPosition = modelMatrix * vec4(position, 1.0)");
		vertexShader.addMainCode("vec4 positionRelativeToCam = viewMatrix * worldPosition");
		vertexShader.addMainCode("gl_Position = projectionMatrix * positionRelativeToCam");

		vertexShader.addMainCode("surfaceNormal = (modelMatrix * vec4(normals,0.0)).xyz");
		vertexShader.addMainCode("textureCoordinates = textureCoords");
		vertexShader.addMainCode("toLightVector = lightPosition - worldPosition.xyz");

		vertexShader.addMainCode("float distance = length(positionRelativeToCam.xyz)");
		vertexShader.addMainCode("visibility = exp(-pow(distance * density, gradient))");
		vertexShader.addMainCode("visibility = clamp(visibility, 0.0, 1.0)");
		/*R"(

		#version 330 core

		in vec2 textureCoordinates;

		uniform float tilingValue = 40.0;

		uniform int hasBlendMap = 0;

		uniform sampler2D textures[32];

		out vec4 color;

		void main() {
			color = texture(textures[0], textureCoordinates * tilingValue);
		}
		)"*/

		fragmentShader.addInputVariable("textureCoordinates", VEC2, FRAGMENT);
		fragmentShader.addInputVariable("surfaceNormal", VEC3, FRAGMENT);
		fragmentShader.addInputVariable("toLightVector", VEC3, FRAGMENT);
		fragmentShader.addInputVariable("visibility", FLOAT, FRAGMENT);

		fragmentShader.addVariable("textures[32]", SAMPLER2D, UNIFORM);
		fragmentShader.addVariable("skyColor", VEC4, UNIFORM);
		fragmentShader.addOutputVariable("color", VEC4);

		fragmentShader.addMainCode("if (visibility < 0.1) discard");

		fragmentShader.addMainCode("float dotl = dot(surfaceNormal, normalize(toLightVector))");
		fragmentShader.addMainCode("float brightness = max(dotl, 0.5)");
		switch (type) {
		case TILING_SHADER:
			fragmentShader.addVariable("tilingValue", FLOAT, UNIFORM, 40.0f);
			fragmentShader.addMainCode("color = brightness * texture(textures[0], textureCoordinates * tilingValue)");
			//fragmentShader.addMainCode("color = vec4(surfaceNormal, 1.0)");
			break;
		}

		fragmentShader.addMainCode("color = mix(skyColor, color, visibility)");
	} 


	TerrainShader::~TerrainShader() {}


} }

