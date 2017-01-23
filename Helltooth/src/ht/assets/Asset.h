#pragma once

#include <Windows.h>

#include <FreeImage/FreeImage.h>
#include <GL/glew.h>

#include "ObjLoader.h"
#include "HelltoothTexture.h"
#include "HelltoothModel.h"

#include "../graphics/textures/Texture.h"

#include "../utils/memory/MemoryManager.h"
#include "../utils/FileUtils.h"
#include "../utils/Log.h"
#include "../utils/String.h"

namespace ht { namespace assets {

	struct TextureData {
		BYTE* pixels;
		unsigned int width;
		unsigned int height;
		unsigned short bpp;

		~TextureData() { del[] pixels; }
	};

	class Asset {
	public:
		static const ht::graphics::Texture* loadTextureFromFile(ht::utils::String path);

		static TextureData* loadTextureDataFromFile(ht::utils::String path);

		static ht::graphics::RawModel* loadModelFromFile(ht::utils::String path);

	protected:
		inline static bool exists(ht::utils::String path) {
			struct stat buffer;
			return (stat(path.c_str(), &buffer) == 0);
		}

	};

} }
