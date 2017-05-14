#include "ShaderManager.h"

namespace ht { namespace graphics {
	using namespace utils;

	ShaderManager* ShaderManager::sManager= nullptr;

	uint32 ShaderManager::loadProgram(String vertexPath, String fragmentPath, bool path) {
		ShaderProgram* program = htnew ShaderProgram(vertexPath.c_str(), fragmentPath.c_str(), path);
		shaders.push_back(program);
		HT_INFO("[ShaderManager] Program with id %i loaded!", shaders.size() - 1);
		return shaders.size() - 1;
	}


	ShaderProgram* ShaderManager::getProgram(uint32 &id) {
		if (id < shaders.size())
			return shaders[id];
		return nullptr;
	}

	void ShaderManager::cleanUP() {
		if (shaders.size() > 0)
			for (unsigned int i=0; i < shaders.size(); i++)
				del shaders[i];
	}

	void ShaderManager::reCompile() {
		HT_WARN("[ShaderManager] Shaders Recompiled!");
		for (unsigned int i = 0; i < shaders.size(); i++)
			shaders[i]->reCompile();
	}
} }