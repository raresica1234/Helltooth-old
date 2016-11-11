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
		TEXTURECOORDINATES,
		NORMALS,
		FRAGMENT
	};
#define MAGIC_NUMBER 28947.0f
	class DynamicShader {

		//BLOCK 0: VERSION RESERVED!
		std::vector<std::string> blocks;

		int currentBlock = 0;

	public:
		DynamicShader(unsigned int version, bool core = false);

		void addVariable(const char* name, VariableStoreType storeType, VariableType type = VariableType::STATIC, float value = MAGIC_NUMBER);
		void addInputVariable(const char* name, VariableStoreType storeType, InputType type);
		void addOutputVariable(const char* name, VariableStoreType storeType);
		void addMainCode(const char* line);

		

		std::string toString();

	private:
		const char* storeTypeToString(VariableStoreType type);

		inline void selectBlock(int id) {
			currentBlock = id;
		}

		inline int addBlock() {
			blocks.push_back(std::string());
			currentBlock = blocks.size() - 1;
			return currentBlock;
		}

		inline void addLine(std::string line) {
			blocks[currentBlock].append(line + ";" + "\n");
		}

		inline void deleteBlock() {
			blocks[currentBlock].clear();
		}

	};
} }
