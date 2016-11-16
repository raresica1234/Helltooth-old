#pragma once

#include "../../utils/memory/MemoryManager.h"

#include "ShaderProgram.h"
#include <vector>

#include "../../utils/Log.h"
#include "../../utils/List.h"
#include "../../utils/String.h"

namespace ht {namespace graphics {
	using namespace utils;
	class ShaderManager {
	private:
		static List<ShaderProgram*> shaders;

	public:
		static unsigned int loadProgram(String vertexPath, String fragmentPath, bool path = true);
		static ShaderProgram* getProgram(unsigned int &id);
		static void cleanUP();

		static void reCompile();
	};


} }