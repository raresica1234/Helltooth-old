#include "API.h"

namespace ht { namespace graphics {
	using namespace utils;

	unsigned int API::type;
	unsigned int API::mode;


	RawModel* API::loadObjFile(String path) {
		String resolvedpath;
		utils::VFS::resolvePhysicalPath(path, resolvedpath);
		return assets::Asset::loadModelFromFile(resolvedpath);
	}

	unsigned int API::createShader(String VERTEX_PATH, String FRAGMENT_PATH, bool path) {
		return ShaderManager::Get()->loadProgram(VERTEX_PATH, FRAGMENT_PATH, path);
	}

	unsigned int API::createWindow(String title, const int &width, const int &height) {
		return WindowManager::Get()->createWindow(title, width, height);
	}

} }
