#include "ShaderManager.h"


namespace ht { namespace graphics {

	std::vector<ShaderProgram*> ShaderManager::shaders;

	unsigned int ShaderManager::loadProgram(std::string vertexPath, std::string fragmentPath, bool path) {
		ShaderProgram* program = htnew ShaderProgram(vertexPath.c_str(), fragmentPath.c_str(), path);
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
				del shader;
	}

	void ShaderManager::reCompile() {
		HT_WARN("[ShaderManager] Shaders Recompiled!");
		for (ShaderProgram* program : shaders)
			program->reCompile();
	}
} }