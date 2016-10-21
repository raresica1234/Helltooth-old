#pragma once

#include <string>
#include <vector>
namespace ht { namespace graphics {
	enum BlockType {
		//VERSION BLOCK
		VARIABLE_BLOCK = 1,
		MAIN_BLOCK = 4,
		FUNCTION_BLOCK
	};

	enum VariableType {
		STATIC,
		UNIFORM
	};

	enum VariableStoreType {
		FLOAT,
		MAT4,
		SAMPLER2D,
		SAMPLER3D,
		VEC2,
		VEC3,
		VEC4
	};

	enum InputType {
		POSITIONS,
		NORMALS,
		TEXTURECOORDINATES,

	};

	class DynamicShader {

		//BLOCK 0: VERSION RESERVED!
		std::vector<std::string> blocks;

		int currentBlock = 0;

	public:
		DynamicShader(unsigned int version, bool core = false) {
			blocks.push_back(std::string("#version ") + std::to_string(version) + (core == true ? std::string(" core") : std::string()) + std::string("\n"));
			for (int i = 1; i < MAIN_BLOCK; i++)
				addBlock();
		}

		void addVariable(const char* name, VariableStoreType storeType, VariableType type = VariableType::STATIC) {
			selectBlock(VARIABLE_BLOCK + type);
			addLine((type == UNIFORM ? std::string("uniform ") : std::string()) + std::string(storeTypeToString(storeType)) + std::string(" ") + std::string(name));
		}

		void addInputVariable(const char* name, VariableStoreType storeType, InputType type) {
			selectBlock(0);
			addLine(std::string("layout(location = ") + std::to_string(type) + std::string(") in ") + std::string(storeTypeToString(storeType))+ std::string(" ") + std::string(name));
		}

		void addOutputVariable(const char* name, VariableStoreType storeType) {
			selectBlock(3);
			addLine(std::string("out ") + std::string(storeTypeToString(storeType)) + std::string(" ") + std::string(name));
		}

		std::string toString() {
			std::string output;
			for (std::string block : blocks) {
				output += block;
				output += "\n";
			}
			return output;
		}

	private:
		const char* storeTypeToString(VariableStoreType type) {
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

		void selectBlock(int id) {
			currentBlock = id;
		}

		int addBlock() {
			blocks.push_back(std::string());
			currentBlock = blocks.size() - 1;
			return currentBlock;
		}

		void addLine(std::string line) {
			blocks[currentBlock].append(line + ";" + "\n");
		}

		void deleteBlock() {
			blocks[currentBlock].clear();
		}

	};
} }
