#include "API.h"

namespace ht { namespace graphics {

	unsigned int API::type;
	unsigned int API::mode;


	RawModel* API::loadObjFile(const char* path) {
		std::string resolvedpath;
		utils::VFS::resolvePhysicalPath(std::string(path), resolvedpath);
		return assets::Asset::loadModelFromFile(resolvedpath);
	}

	const Texture* API::loadTextureFromFile(const char* path) {
		std::string resolvedpath;
		utils::VFS::resolvePhysicalPath(std::string(path), resolvedpath);
		return assets::Asset::loadTextureFromFile(resolvedpath);
	}

	unsigned int API::createShader(const char* VERTEX_PATH, const char* FRAGMENT_PATH, bool path) {
		return ShaderManager::loadProgram(VERTEX_PATH, FRAGMENT_PATH, path);
	}

	unsigned int API::createWindow(const char *title, const int &width, const int &height) {
		return WindowManager::createWindow(title, width, height);
	}

} }
