#include "API.h"

namespace ht { namespace graphics {

	unsigned int API::type;
	unsigned int API::mode;


	RawModel* API::loadObjFile(const char* path) {
		return ObjLoader::loadObjFile(path);
	}

	const Texture* API::loadTextureFromFile(const char* path) {
		return assets::Asset::loadTextureFromFile(path);
	}

	unsigned int createShader(const char* VERTEX_PATH, const char* FRAGMENT_PATH) {
		return ShaderManager::loadProgram(VERTEX_PATH, FRAGMENT_PATH);
	}

} }
