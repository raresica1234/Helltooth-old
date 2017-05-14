#pragma once

#include "Texture.h"

#include "assets/Asset.h"

#include "tools/VFS/VFS.h"

#include "utils/Internal.h"
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

		uint32 createTextureFromFile(utils::String path);

		uint32 createTextureFromData(assets::TextureData* data);
		uint32 createTextureFromMemory(byte* array, uint32 size);

		const Texture* getTexture(uint32 id);

		__forceinline uint32 addTexture(const Texture* texture) { textures.push_back(texture); return textures.size() - 1; }

		__forceinline static void Init() { 
			if (tManager) { HT_ERROR("[TextureManager] Reinitialization not possible!"); return; }
			tManager = htnew TextureManager();
		}
		__forceinline static TextureManager* Get() {
			if (!tManager) { Init(); HT_ERROR("[TextureManager] TextureManager not initialized, initialization forced!"); }
			return tManager; 
		}

		__forceinline static void End() {
			if (!tManager) { HT_ERROR("[TextureManager] Deletion not possible, TextureManager not initialized!"); return; }
			del tManager;
			tManager = nullptr; 
		}
	};
} }
