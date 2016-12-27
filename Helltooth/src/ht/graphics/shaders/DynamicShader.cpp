#include "DynamicShader.h"
#include "../../utils/Log.h"

namespace ht { namespace graphics {
	using namespace utils;

	DynamicShader::DynamicShader(unsigned int version, bool core) {
		blocks.push_back(String("#version ") + std::to_string(version).c_str() + String(core == true ? " core" : String()) + "\n");
		for (int i = 1; i <= MAIN_BLOCK; i++)
			addBlock();
	}
	void DynamicShader::addVariable(const char* name, VariableStoreType storeType, VariableType type, float value) {
		selectBlock(VARIABLE_BLOCK + type);
		if (value == DYNAMIC_SHADER_MAGIC_NUMBER)
			addLine(String(type == UNIFORM ? "uniform " : "") + storeTypeToString(storeType) + " " + name);
		else
			addLine(String(type == UNIFORM ? "uniform " : "") + storeTypeToString(storeType) + " " + name + " = " + std::to_string(value).c_str());

	}

	void DynamicShader::addInputVariable(const char* name, VariableStoreType storeType, InputType type) {
		selectBlock(0);
		if (type != FRAGMENT)
			addLine(String("layout(location = ") + std::to_string(type).c_str() + ") in " + storeTypeToString(storeType) + " " + name);
		else
			addLine(String("in ") + storeTypeToString(storeType) + " " + name);
	}

	void DynamicShader::addOutputVariable(const char* name, VariableStoreType storeType) {
		selectBlock(3);
		addLine(String("out ") + storeTypeToString(storeType) + " " + name);
	}

	void DynamicShader::addMainCode(const char* line) {
		selectBlock(MAIN_BLOCK);
		addLine(String(line));
	}

	utils::String DynamicShader::toString() {
		utils::String output;
		for (unsigned int i = 0; i < blocks.size(); i++) {
			if (i == MAIN_BLOCK) {
				output += "void main() { \n";
				output += blocks[i];
				output += "} \n";
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
		HT_ERROR("[DynamicShader] Variable Store Type not avalible.");
		return "error";
	}
} }
