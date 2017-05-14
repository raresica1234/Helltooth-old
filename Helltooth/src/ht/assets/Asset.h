#pragma once

#include <Windows.h>

#include <FreeImage/FreeImage.h>
#include <GL/glew.h>

#include "ObjLoader.h"
#include "HelltoothTexture.h"
#include "HelltoothModel.h"
#include "HelltoothCubemap.h"

#include "graphics/textures/Texture.h"

#include "utils/Internal.h"
#include "utils/FileUtils.h"
#include "utils/Log.h"
#include "utils/String.h"
#include "utils/memory/MemoryManager.h"

namespace ht { namespace assets {

	struct TextureData {
		byte* pixels;
		uint16 width, height;
		byte bpp;

		~TextureData() { del[] pixels; }
	};

	class Asset {
	public:
		static const graphics::Texture* loadTextureFromFile(utils::String path);
		static const graphics::Texture* loadTextureFromMemory(byte* array, uint32 size);
		static graphics::RawModel* loadModelFromFile(utils::String path);

		static TextureData* loadTextureDataFromFile(utils::String path);
		static Cubemap* loadCubemapFromFile(utils::String path);

	protected:
		__forceinline static bool exists(ht::utils::String path) { struct stat buffer; return (stat(path.c_str(), &buffer) == 0); }
	};
} }
