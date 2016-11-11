#include "DynamicShader.h"

namespace ht { namespace graphics {

	DynamicShader::DynamicShader(unsigned int version, bool core) {
		blocks.push_back(std::string("#version ") + std::to_string(version) + (core == true ? std::string(" core") : std::string()) + std::string("\n"));
		for (int i = 1; i <= MAIN_BLOCK; i++)
			addBlock();
	}
	void DynamicShader::addVariable(const char* name, VariableStoreType storeType, VariableType type, float value) {
		selectBlock(VARIABLE_BLOCK + type);
		if(value == MAGIC_NUMBER)
			addLine((type == UNIFORM ? std::string("uniform ") : std::string()) + std::string(storeTypeToString(storeType)) + std::string(" ") + std::string(name));
		else 
			addLine((type == UNIFORM ? std::string("uniform ") : std::string()) + std::string(storeTypeToString(storeType)) + std::string(" ") + std::string(name) + std::string(" = ") + std::to_string(value));

	}


	void DynamicShader::addInputVariable(const char* name, VariableStoreType storeType, InputType type) {
		selectBlock(0);
		if (type != FRAGMENT)
			addLine(std::string("layout(location = ") + std::to_string(type) + std::string(") in ") + std::string(storeTypeToString(storeType)) + std::string(" ") + std::string(name));
		else
			addLine(std::string("in ") + std::string(storeTypeToString(storeType)) + std::string(" ") + std::string(name));
	}

	void DynamicShader::addOutputVariable(const char* name, VariableStoreType storeType) {
		selectBlock(3);
		addLine(std::string("out ") + std::string(storeTypeToString(storeType)) + std::string(" ") + std::string(name));
	}

	void DynamicShader::addMainCode(const char* line) {
		selectBlock(MAIN_BLOCK);
		addLine(std::string(line));
	}

	std::string DynamicShader::toString() {
		std::string output;
		for (int i = 0; i < blocks.size(); i++) {
			if (i == MAIN_BLOCK) {
				output += std::string("void main() { \n");
				output += blocks[i];
				output += std::string("} \n");
				continue;
			}
			output += blocks[i];
		}
		return output;
	}

	const char* DynamicShader::storeTypeToString(VariableStoreType type) {
		switch (type) {
		case FLOAT:
			return "float";
		case MAT4:
			return "mat4";
		case SAMPLER2D:
			return "sampler2D";
		case SAMPLER3D:
			return "sampler3D";
		case VEC2:
			return "vec2";
		case VEC3:
			return "vec3";
		case VEC4:
			return "vec4";
		}
	}
} }
