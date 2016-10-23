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
		static inline const Texture* loadTextureFromFile(std::string path) {
			const char* file = path.c_str();
			std::string fileName = utils::FileUtils::changeExtension(file, std::string("httexture"));

			if (exists(fileName)) {
				HelltoothTexture texture(fileName.c_str());
				return texture.getTexture();
			}

			HT_WARN("\"%s\" not found! Creating one...", fileName);


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

			HelltoothTexture::storeAsHelltoothTexture(fileName.c_str(), result, width, height, bpp, size);
			const Texture* texture = htnew Texture();

			texture->loadPixelArray(result, width, height, bpp);

			del[] result;
			HT_INFO("[Asset] Texture %s loaded!", file);
			return texture;
		}

		static inline const void loadTexture(const char *file, unsigned int &width, unsigned int &height, unsigned int &bpp, unsigned int &size, BYTE* result) {
			FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file);

			FIBITMAP *dib = nullptr;

			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(file);

			if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, file);


			BYTE* pixels = FreeImage_GetBits(dib);

			width = FreeImage_GetWidth(dib);
			height = FreeImage_GetHeight(dib);
			bpp = FreeImage_GetBPP(dib);

			size = width * height * (bpp / 8);
			if (result)
				del[] result;

			result = htnew BYTE[size];
			memcpy(result, pixels, size);

			FreeImage_Unload(dib);
		}

		static inline RawModel* loadModelFromFile(std::string path) {
			const char* file = path.c_str();
			std::string fileName = utils::FileUtils::changeExtension(file, std::string("htmodel"));
			if (exists(fileName)) {
				HelltoothModel model(fileName.c_str());
				return model.getRawModel();
			}
			
			HT_WARN("\"%s\" not found! Creating one...", fileName);
			RawModel* rawModel = ObjLoader::loadObjFile(file);

			HelltoothModel::storeAsHelltoothModel(fileName.c_str(), rawModel);

			return rawModel;
		}

	protected:
		static bool exists(std::string path) {
			struct stat buffer;
			return (stat(path.c_str(), &buffer) == 0);
		}

	};

} }
