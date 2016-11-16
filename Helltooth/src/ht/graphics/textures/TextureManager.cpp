#include "TextureManager.h"

namespace ht { namespace graphics {

	TextureManager* TextureManager::textureManager = nullptr;

	unsigned int TextureManager::createTextureFromFile(String path) {
		const Texture* tex = assets::Asset::loadTextureFromFile(path.c_str());
		textures.push(tex);
		return textures.size - 1;
	}

	TextureManager::~TextureManager() {
		for (int i = 0; i < textures.size; i++)
			delete textures[i];
	}

	const Texture* TextureManager::getTexture(unsigned int id) {
		return textures[id];
	}


} }
