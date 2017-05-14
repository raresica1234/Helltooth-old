#include "TextureManager.h"

namespace ht { namespace graphics {
	using namespace utils;
	using namespace assets;

	TextureManager* TextureManager::tManager = nullptr;

	unsigned int TextureManager::createTextureFromFile(String path) {
		String output;
		if (!VFS::resolvePhysicalPath(path, output))
			HT_FATAL("[TextureManager] Cannot open \"%s\"", path.c_str());
		const Texture* tex = Asset::loadTextureFromFile(output.c_str());
		textures.push_back(tex);
		return textures.size() - 1;
	}

	unsigned int TextureManager::createTextureFromData(TextureData* data) {
		Texture* texture = htnew Texture();
		texture->loadPixelArray(data->pixels, data->width, data->height, data->bpp);
		del data;
		textures.push_back(texture);
		return textures.size() - 1;
	}

	TextureManager::~TextureManager() {
		for (unsigned int i = 0; i < textures.size(); i++)
			del textures[i];
	}

	const Texture* TextureManager::getTexture(unsigned int id) {
		return textures[id];
	}

	unsigned int TextureManager::createTextureFromMemory(unsigned char* array, long long size) {
		const Texture* tex = Asset::loadTextureFromMemory(array, size);
		textures.push_back(tex);
		return textures.size() - 1;
	}
} }
