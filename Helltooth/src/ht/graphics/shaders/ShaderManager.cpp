#include "ShaderManager.h"


namespace ht { namespace graphics {

	std::vector<ShaderProgram*> ShaderManager::programs;

	unsigned int ShaderManager::loadProgram(const char* vertexPath, const char* fragmentPath) {
		ShaderProgram* program = htnew ShaderProgram(vertexPath, fragmentPath);
		programs.push_back(program);
		return programs.size() - 1;
	}

	ShaderProgram* ShaderManager::getProgram(unsigned int &id) {
		if (id < programs.size())
			return programs[id];
		return nullptr;
	}

	void ShaderManager::cleanUP() {
		if (programs.size() > 0)
			for (ShaderProgram* program : programs)
				delete program;
	}
} }