#include "API.h"

namespace ht { namespace graphics {
	using namespace utils;
	using namespace assets;

	uint32 API::type;
	uint32 API::mode;

	API::Fog API::fog;


	RawModel* API::loadObjFile(String path) {
		String resolvedpath;
		if (VFS::resolvePhysicalPath(path, resolvedpath))
			return Asset::loadModelFromFile(resolvedpath);
		else {
			HT_FATAL("[API] Can not load \"%s\"", path.c_str());
			return nullptr;
		}
	}

	Cubemap* API::loadCubemap(String path) {
		String resolvedpath;
		if (VFS::resolvePhysicalPath(path, resolvedpath))
			return Asset::loadCubemapFromFile(resolvedpath);
		else {
			HT_FATAL("[API] Can not load \"%s\"", path.c_str());
			return nullptr;
		}
	}

	unsigned int API::createShader(String VERTEX_PATH, String FRAGMENT_PATH, bool path) {
		return ShaderManager::Get()->loadProgram(VERTEX_PATH, FRAGMENT_PATH, path);
	}

	unsigned int API::createWindow(String title, const uint16 &width, const uint16 &height) {
		return WindowManager::Get()->createWindow(title, width, height);
	}

} }
