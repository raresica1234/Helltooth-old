#pragma once

#include <iostream>
#include <vector>

#include "../graphics/textures/Texture.h"

#include "../utils/memory/MemoryManager.h"
#include "../utils/String.h"

#include "../tools/Cereal/Cereal.h"

namespace ht { namespace assets {

	class HelltoothTexture {
	private:
		friend class Asset;
		friend struct TextureData;

		ht::graphics::Texture* texture = nullptr;
		TextureData* data = nullptr;

	public:
		HelltoothTexture(ht::utils::String filePath, unsigned int data = 0);

		inline ht::graphics::Texture* getTexture() {
			return texture;
		}
		inline ht::assets::TextureData* getData() {
			return data;
		}

		static void StoreAsHelltoothTexture(ht::utils::String filePath, byte* pixels, int width, int height, byte bpp, size_t dataSize);
	};

} }