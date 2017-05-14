#pragma once
#include "tools/Cereal/Cereal.h"

#include "utils/Internal.h"
#include "utils/String.h"
#include "utils/memory/MemoryManager.h"

namespace ht { namespace assets {

	struct Cubemap {
		int32 width, height; 
		uint32 bpp;

		byte *right = nullptr, *left = nullptr, *front = nullptr, *back = nullptr, *top = nullptr, *bottom = nullptr;

		~Cubemap() { del[] right, left, front, back, top, bottom; }
	};

	class HelltoothCubemap {
	private:
		Cubemap *cubemap = nullptr;

	public:
		HelltoothCubemap(utils::String path);

		__forceinline Cubemap* getCubemap() { return cubemap; }
	};
} }