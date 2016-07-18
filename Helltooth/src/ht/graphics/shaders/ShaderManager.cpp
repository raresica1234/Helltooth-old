#include "ShaderManager.h"


namespace ht { namespace graphics {

	std::vector<ShaderProgram*> ShaderManager::shaders;

	unsigned int ShaderManager::loadProgram(const char* vertexPath, const char* fragmentPath) {
		ShaderProgram* program = htnew ShaderProgram(vertexPath, fragmentPath);
		shaders.push_back(program);
		return shaders.size() - 1;
	}

	ShaderProgram* ShaderManager::getProgram(unsigned int &id) {
		if (id < shaders.size())
			return shaders[id];
		return nullptr;
	}

	void ShaderManager::cleanUP() {
		if (shaders.size() > 0)
			for (ShaderProgram* shader : shaders)
				delete shader;
	}

	void ShaderManager::reCompile() {
		for (ShaderProgram* program : shaders)
			program->reCompile();
	}
} }