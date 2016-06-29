#pragma once

#include <FreeImage/FreeImage.h>

#include <vector>
#include <string>
#include <iostream>

#include <sys/stat.h>

#include "../graphics/textures/Texture.h"
#include "../utils/memory/MemoryManager.h"

#include "../tools/Cereal/Cereal.h"

#include <GL/glew.h>

#include "HelltoothTexture.h"

#include "../utils/Log.h"

namespace ht{ namespace assets{

	using namespace graphics;

	class Asset {
	public:
		static inline const Texture* loadTextureFromFile(char *file) {
			std::string fileName(file);
			fileName += ".httexture";

			if (exists(fileName)) {
				HelltoothTexture texture(fileName.c_str());
				return texture.getTexture();
			}

			HT_INFO("\"%s\" not found! Creating one...", fileName);

			const Texture* texture = htnew Texture();

			FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file);

			FIBITMAP *dib = nullptr;

			if (fif == FIF_UNKNOWN) 
				fif = FreeImage_GetFIFFromFilename(file);
			
			if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, file);


			BYTE* pixels = FreeImage_GetBits(dib);

			GLsizei width = FreeImage_GetWidth(dib);
			GLsizei height = FreeImage_GetHeight(dib);
			GLsizei bpp = FreeImage_GetBPP(dib);

			unsigned int size = width * height * (bpp / 8);

			BYTE* result = htnew BYTE[size];
			memcpy(result, pixels, size);

			FreeImage_Unload(dib);

			std::string name(file);
			name.append(".httexture");
			HelltoothTexture::storeAsHelltoothTexture(name.c_str(), result, width, height, bpp, size);

			texture->loadPixelArray(result, width, height, bpp);

			delete[] result;

			return texture;
		}

	protected:
		static bool exists(std::string path) {
			struct stat buffer;
			return (stat(path.c_str(), &buffer) == 0);
		}

	};

} }
