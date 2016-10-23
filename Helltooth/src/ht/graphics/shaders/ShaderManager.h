#pragma once

#include "../../utils/memory/MemoryManager.h"

#include "ShaderProgram.h"
#include <vector>

#include "../../utils/Log.h"


namespace ht {namespace graphics {

	class ShaderManager {
	private:
		static std::vector<ShaderProgram*> shaders;

	public:
		static unsigned int loadProgram(std::string vertexPath, std::string fragmentPath, bool path = true);
		static ShaderProgram* getProgram(unsigned int &id);
		static void cleanUP();

		static void reCompile();
	};


} }