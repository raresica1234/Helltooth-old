#pragma once

#include "../../utils/memory/MemoryManager.h"

#include "ShaderProgram.h"
#include <vector>

namespace ht {namespace graphics {

	class ShaderManager {
	private:
		static std::vector<ShaderProgram*> programs;

	public:
		static unsigned int loadProgram(const char* vertexPath, const char* fragmentPath);
		static ShaderProgram* getProgram(unsigned int &id);
		static void cleanUP();

	};


} }