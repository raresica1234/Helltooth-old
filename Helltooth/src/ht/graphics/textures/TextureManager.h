#pragma once

#include "Texture.h"

#include "assets/Asset.h"

#include "tools/VFS/VFS.h"

#include "utils/String.h"
#include "utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	class TextureManager {
	private:
		std::vector<const Texture*> textures;
		static TextureManager* tManager;

	public:
		__forceinline TextureManager() {}
		~TextureManager();

		unsigned int createTextureFromFile(ht::utils::String path);

		unsigned int createTextureFromData(ht::assets::TextureData* data);

		const Texture* getTexture(unsigned int id);

		inline unsigned int addTexture(const Texture* texture) {
			textures.push_back(texture);

			return textures.size() - 1;
		}

		static TextureManager* Get() { return tManager; }

		static void End() { del tManager; tManager = nullptr; }

		static void Init() { 
			if (!tManager)
				tManager = htnew TextureManager();
			else
				HT_WARN("[TextureManager] Reinitialization not possible!");
		}
	};
} }
