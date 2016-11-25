#include "TextureManager.h"

namespace ht { namespace graphics {
	using namespace utils;

	TextureManager* TextureManager::tManager = nullptr;

	unsigned int TextureManager::createTextureFromFile(String path) {
		String output;
		VFS::resolvePhysicalPath(path, output);
		const Texture* tex = assets::Asset::loadTextureFromFile(output.c_str());
		textures.push_back(tex);
		return textures.size() - 1;
	}

	TextureManager::~TextureManager() {
		for (int i = 0; i < textures.size(); i++)
			del textures[i];
	}

	const Texture* TextureManager::getTexture(unsigned int id) {
		return textures[id];
	}


} }
