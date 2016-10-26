#pragma once

#include <iostream>
#include <vector>

#include "../graphics/textures/Texture.h"

#include "../utils/memory/MemoryManager.h"

#include "../tools/Cereal/Cereal.h"

namespace ht { namespace assets {

	using namespace graphics;

	class HelltoothTexture {
	private:
		Texture* texture = nullptr;

	public:
		HelltoothTexture(const char* filePath);

		inline Texture* getTexture() {
			return texture;
		}

		static void storeAsHelltoothTexture(const char* filePath, byte* pixels, int width, int height, byte bpp, size_t dataSize);
	};

} }