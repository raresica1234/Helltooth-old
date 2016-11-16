#include "ShaderManager.h"

namespace ht { namespace graphics {

	List<ShaderProgram*> ShaderManager::shaders;

	unsigned int ShaderManager::loadProgram(String vertexPath, String fragmentPath, bool path) {
		ShaderProgram* program = htnew ShaderProgram(vertexPath.c_str(), fragmentPath.c_str(), path);
		shaders.push(program);
		HT_INFO("[ShaderManager] Program with id %i loaded!", shaders.size - 1);
		return shaders.size - 1;
	}


	ShaderProgram* ShaderManager::getProgram(unsigned int &id) {
		if (id < shaders.size)
			return shaders[id];
		return nullptr;
	}

	void ShaderManager::cleanUP() {
		if (shaders.size > 0)
			for (int i=0; i < shaders.size; i++)
				del shaders[i];
	}

	void ShaderManager::reCompile() {
		HT_WARN("[ShaderManager] Shaders Recompiled!");
		for (int i = 0; i < shaders.size; i++)
			shaders[i]->reCompile();
	}
} }