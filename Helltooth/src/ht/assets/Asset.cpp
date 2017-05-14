#include "Asset.h"


namespace ht { namespace assets {
	using namespace graphics;
	using namespace utils;

	const Texture* Asset::loadTextureFromFile(String path) {
		String fileName = utils::FileUtils::changeExtension(path, "httexture");

		if (exists(fileName)) {
			HelltoothTexture texture(fileName.c_str());
			HT_INFO("[Asset] Texture \"%s\" loaded!", fileName);
			return texture.getTexture();
		}

		HT_INFO("[Asset]\"%s\" not found! Creating one...", fileName);

		const char* file = path.c_str();
		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file);

		FIBITMAP *dib = nullptr;

		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(file);

		if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, file);

		FreeImage_FlipVertical(dib);

		BYTE* pixels = FreeImage_GetBits(dib);

		GLsizei width = FreeImage_GetWidth(dib);
		GLsizei height = FreeImage_GetHeight(dib);
		GLsizei bpp = FreeImage_GetBPP(dib);

		unsigned int size = width * height * (bpp / 8);

		BYTE* result = htnew BYTE[size];
		memcpy(result, pixels, size);

		FreeImage_Unload(dib);

		HelltoothTexture::StoreAsHelltoothTexture(fileName, result, width, height, bpp, size);
		const Texture* texture = htnew Texture();

		texture->loadPixelArray(result, width, height, bpp);

		del[] result;
		HT_INFO("[Asset] Texture \"%s\" loaded!", file);
		return texture;
	}

	const graphics::Texture* Asset::loadTextureFromMemory(unsigned char* array, unsigned int size) {
		FIMEMORY* data = FreeImage_OpenMemory(array, size);
		FREE_IMAGE_FORMAT format = FreeImage_GetFileTypeFromMemory(data, size);

		FIBITMAP* dib = nullptr;
		
		dib = FreeImage_LoadFromMemory(format, data);
		
		BYTE* pixels = FreeImage_GetBits(dib);

		GLsizei width = FreeImage_GetWidth(dib);
		GLsizei height = FreeImage_GetHeight(dib);
		GLsizei bpp = FreeImage_GetBPP(dib);

		long long bmpsize = width * height * (bpp / 8);

		BYTE* result = htnew BYTE[bmpsize];
		memcpy(result, pixels, bmpsize);

		FreeImage_Unload(dib);
		FreeImage_CloseMemory(data);

		const Texture* texture = htnew Texture();
		texture->loadPixelArray(result, width, height, bpp);

		del[] result;
		HT_INFO("[Asset] Texture loaded from memory!");
		return texture;
	}

	TextureData* Asset::loadTextureDataFromFile(ht::utils::String path) {
		String fileName = utils::FileUtils::changeExtension(path, "httexture");

		if (exists(fileName)) {
			HelltoothTexture texture(fileName.c_str(), 1);
			HT_INFO("[Asset] Texture \"%s\" loaded!", fileName);
			return texture.getData();
		}

		HT_INFO("[Asset]\"%s\" not found! Creating one...", fileName);

		const char* file = path.c_str();
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

		HelltoothTexture::StoreAsHelltoothTexture(fileName, result, width, height, bpp, size);

		TextureData* data = htnew TextureData();
		data->pixels = result;
		data->width = width;
		data->height = height;
		data->bpp = bpp;

		return data;
	}

	Cubemap* Asset::loadCubemapFromFile(utils::String path) {
		if (exists(path)) {
			HelltoothCubemap cubemap(path);
			HT_INFO("[Asset] Cubemap \"%s\" loaded!", path);
			return cubemap.getCubemap();
		}
		else
			HT_ERROR("[Asset] Cubemap \"%s\" not found", path);
	}

	RawModel* Asset::loadModelFromFile(String path) {
		String fileName = utils::FileUtils::changeExtension(path, "htmodel");

		if (exists(fileName)) {
			HelltoothModel model(fileName);
			HT_INFO("[Asset] Model \"%s\" loaded!", fileName);
			return model.getRawModel();
		}

		HT_INFO("[Asset]\"%s\" not found! Creating one...", fileName);
		RawModel* rawModel = ObjLoader::LoadObjFile(path);

		HelltoothModel::StoreAsHelltoothModel(fileName, rawModel);
		HT_INFO("[Asset] Model \"%s\" loaded!", fileName);
		return rawModel;
	}

} }