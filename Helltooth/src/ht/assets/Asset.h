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

	using namespace graphics;
	using namespace utils;
	class Asset {
	public:
		static const Texture* loadTextureFromFile(String path);

		static RawModel* loadModelFromFile(String path);

	protected:
		inline static bool exists(String path) {
			struct stat buffer;
			return (stat(path.c_str(), &buffer) == 0);
		}

	};

} }
