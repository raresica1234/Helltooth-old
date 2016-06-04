#pragma once

#include <FreeImage/FreeImage.h>

#include <vector>
#include <string>
#include <iostream>

#include "../graphics/textures/Texture.h"
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
		static inline const Texture* loadTextureFromFile(char *file) {
			const Texture* texture = new Texture();
			
			

			std::string fileName(file);
			if (fileName.substr(fileName.size() - HELLTOOTH_FORMAT_SIZE, fileName.size()) == ".httexture") {
				
			}

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

			texture->loadPixelArray(result, width, height, bpp, size);

			return texture;
		}

	};

} }
