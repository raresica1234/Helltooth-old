#pragma once

#include "../../utils/List.h"
#include "../../utils/String.h"

#include "Texture.h"

#include "../../assets/Asset.h"

namespace ht { namespace graphics {

	using namespace utils;
	class TextureManager {
	private:
		List<const Texture*> textures;
		static TextureManager* textureManager;
	public:
		__forceinline TextureManager() {}
		~TextureManager();

		unsigned int createTextureFromFile(String path);

		const Texture* getTexture(unsigned int id);

		static TextureManager* Get() { return textureManager; }

		static void End() { delete textureManager; }

		static void Init() { 
			if (!textureManager)
				textureManager = htnew TextureManager();
			else
				HT_WARN("[TextureManager] Reinitialization not possible!");
		}

	};


} }
