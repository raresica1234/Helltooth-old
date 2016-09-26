#include "ShaderManager.h"


namespace ht { namespace graphics {

	std::vector<ShaderProgram*> ShaderManager::shaders;

	unsigned int ShaderManager::loadProgram(const char* vertexPath, const char* fragmentPath, bool path) {
		ShaderProgram* program = htnew ShaderProgram(vertexPath, fragmentPath, path);
		shaders.push_back(program);
		HT_INFO("[ShaderManager] Program with id %i loaded!", shaders.size() - 1);
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
		HT_WARN("[ShaderManager] Shaders Recompiled!");
		for (ShaderProgram* program : shaders)
			program->reCompile();
	}
} }