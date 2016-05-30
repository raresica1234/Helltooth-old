#pragma once

#include "../graphics/textures/Texture.h"

#include <vector>
#include <string>
#include <iostream>

#include <FreeImage/FreeImage.h>

#include "../utils/memory/MemoryManager.h"

#include <GL/glew.h>

namespace ht{ namespace assets{

	using namespace graphics;
#define HELLTOOTH_FORMAT_SIZE	10

	class Asset {
	private:
		//static std::vector<Texture> textures;
		//todo models of course

	public:
		static inline Texture loadTextureFromFile(char *file) {
			Texture texture;
			
			std::string fileName(file);
			if (fileName.substr(fileName.size() - HELLTOOTH_FORMAT_SIZE, fileName.size()) == ".httexture") {
				
			}

			FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file);

			FIBITMAP *dib = nullptr;

			if (fif == FIF_UNKNOWN) 
				fif = FreeImage_GetFIFFromFilename(file);

			if (fif == FIF_UNKNOWN) {
				return texture;;
			}
			
			if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, file);

			if (!dib) return texture;

			BYTE* pixels = FreeImage_GetBits(dib);

			GLsizei width = FreeImage_GetWidth(dib);
			GLsizei height = FreeImage_GetHeight(dib);
			GLsizei bpp = FreeImage_GetBPP(dib);

			long long size = width * height * (bpp / 8);

			BYTE* result = htnew BYTE[size];
			memcpy(result, pixels, size);

			FreeImage_Unload(dib);

			texture.loadPixelArray(result, width, height, bpp, size);

			return texture;
		}

	};

} }