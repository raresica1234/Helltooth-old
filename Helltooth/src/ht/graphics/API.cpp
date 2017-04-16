#include "API.h"

namespace ht { namespace graphics {
	using namespace utils;

	unsigned int API::type;
	unsigned int API::mode;

	API::Fog API::fog;


	RawModel* API::loadObjFile(String path) {
		String resolvedpath;
		if (utils::VFS::resolvePhysicalPath(path, resolvedpath))
			return assets::Asset::loadModelFromFile(resolvedpath);
		else {
			HT_FATAL("[API] Can not load \"%s\"", path.c_str());
			return nullptr;
		}
	}

	assets::Cubemap* API::loadCubemap(utils::String path) {
		String resolvedpath;
		if (utils::VFS::resolvePhysicalPath(path, resolvedpath))
			return assets::Asset::loadCubemapFromFile(resolvedpath);
		else {
			HT_FATAL("[API] Can not load \"%s\"", path.c_str());
			return nullptr;
		}
	}

	unsigned int API::createShader(String VERTEX_PATH, String FRAGMENT_PATH, bool path) {
		return ShaderManager::Get()->loadProgram(VERTEX_PATH, FRAGMENT_PATH, path);
	}

	unsigned int API::createWindow(String title, const int &width, const int &height) {
		return WindowManager::Get()->createWindow(title, width, height);
	}

} }
