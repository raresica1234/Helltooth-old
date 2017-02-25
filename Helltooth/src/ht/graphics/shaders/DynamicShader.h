#pragma once

#include <vector>
#include <string>

#include "utils/String.h"
#include "utils/Log.h"

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

	class DynamicShader {
#define DYNAMIC_SHADER_MAGIC_NUMBER 28947.0f
		//BLOCK 0: VERSION RESERVED!
		std::vector<utils::String> blocks;

		int currentBlock = 0;

	public:
		DynamicShader(unsigned int version, bool core = false);

		void addVariable(const char* name, VariableStoreType storeType, VariableType type = VariableType::STATIC, float value = DYNAMIC_SHADER_MAGIC_NUMBER);
		void addInputVariable(const char* name, VariableStoreType storeType, InputType type);
		void addOutputVariable(const char* name, VariableStoreType storeType);
		void addMainCode(const char* line);

		

		utils::String toString();

	private:
		const char* storeTypeToString(VariableStoreType type);

		inline void selectBlock(int id) {
			currentBlock = id;
		}

		inline int addBlock() {
			blocks.push_back("");
			currentBlock = blocks.size() - 1;
			return currentBlock;
		}

		inline void addLine(utils::String line) {
			blocks[currentBlock] += line + ";" + "\n";
		}

		inline void deleteBlock() {
			blocks[currentBlock].clear();
		}
	};
} }
