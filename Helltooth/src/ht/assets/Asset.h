#pragma once

#include <Windows.h>

#include <FreeImage/FreeImage.h>

#include <string>
#include <sys/stat.h>

#include "../graphics/textures/Texture.h"
#include "../utils/memory/MemoryManager.h"


#include <GL/glew.h>

#include "HelltoothTexture.h"

#include "../utils/FileUtils.h"

#include "../utils/Log.h"

#include "ObjLoader.h"

#include "HelltoothModel.h"

namespace ht { namespace assets {

	using namespace graphics;

	class Asset {
	public:
		static const Texture* loadTextureFromFile(std::string path);

		static RawModel* loadModelFromFile(std::string path);

	protected:
		inline static bool exists(std::string path) {
			struct stat buffer;
			return (stat(path.c_str(), &buffer) == 0);
		}

	};

} }
