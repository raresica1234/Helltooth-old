#pragma once

#include <iostream>
#include <vector>

#include "graphics/textures/Texture.h"

#include "tools/Cereal/Cereal.h"

#include "utils/String.h"
#include "utils/Internal.h"
#include "utils/memory/MemoryManager.h"

namespace ht { namespace assets {

	class HelltoothTexture {
	private:
		friend struct TextureData;

		graphics::Texture* texture = nullptr;
		TextureData* data = nullptr;

	public:
		HelltoothTexture(utils::String filePath, uint32 data = 0);

		__forceinline graphics::Texture* getTexture() { return texture; }
		__forceinline TextureData* getData() { return data; }

		static void StoreAsHelltoothTexture(utils::String filePath, byte* pixels, uint16 width, uint16 height, byte bpp, uint32 dataSize);
	};

} }