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
		ht::graphics::Texture* texture = nullptr;

	public:
		HelltoothTexture(ht::utils::String filePath);

		inline ht::graphics::Texture* getTexture() {
			return texture;
		}

		static void StoreAsHelltoothTexture(ht::utils::String filePath, byte* pixels, int width, int height, byte bpp, size_t dataSize);
	};

} }