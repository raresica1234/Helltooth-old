#pragma once

#include <iostream>
#include <vector>

#include "../graphics/textures/Texture.h"

#include "../utils/memory/MemoryManager.h"
#include "../utils/String.h"

#include "../tools/Cereal/Cereal.h"

namespace ht { namespace assets {

	using namespace graphics;
	using namespace utils;

	class HelltoothTexture {
	private:
		Texture* texture = nullptr;

	public:
		HelltoothTexture(String filePath);

		inline Texture* getTexture() {
			return texture;
		}

		static void storeAsHelltoothTexture(String filePath, byte* pixels, int width, int height, byte bpp, size_t dataSize);
	};

} }