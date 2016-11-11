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

		vertexShader.addOutputVariable("textureCoordinates", VEC2);

		vertexShader.addMainCode("gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0)");
		vertexShader.addMainCode("textureCoordinates = textureCoords");
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


		fragmentShader.addVariable("textures[32]", SAMPLER2D, UNIFORM);

		fragmentShader.addOutputVariable("color", VEC4);

		switch (type) {
		case TILING_SHADER:
			fragmentShader.addVariable("tilingValue", FLOAT, UNIFORM, 40.0f);
			fragmentShader.addMainCode("color = texture(textures[0], textureCoordinates * tilingValue)");
			break;
		}

	} 


	TerrainShader::~TerrainShader() {}


} }

