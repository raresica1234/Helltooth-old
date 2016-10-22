#include "sandbox/sandbox.h"
using namespace sandbox;

#include <iostream>
#include <string>

void main() {

	DynamicShader shader(400, true);
	shader.addInputVariable("position", VariableStoreType::VEC3, InputType::POSITIONS);
	shader.addInputVariable("normals", VariableStoreType::VEC3, InputType::NORMALS);
	shader.addInputVariable("textureCoords", VariableStoreType::VEC2, InputType::TEXTURECOORDINATES);

	shader.addVariable("modelMatrix", MAT4, UNIFORM);
	shader.addVariable("viewMatrix", MAT4, UNIFORM);
	shader.addVariable("projectionMatrix", MAT4, UNIFORM);

	shader.addOutputVariable("textureCoordinates", VEC2);
	std::cout << shader.toString();
	system("PAUSE");

	Sandbox* sandbox = htnew Sandbox();

	delete sandbox;
}