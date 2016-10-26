#include "Asset.h"

namespace ht { namespace assets {
	const Texture* Asset::loadTextureFromFile(std::string path) {
		const char* file = path.c_str();
		std::string fileName = utils::FileUtils::changeExtension(file, std::string("httexture"));

		if (exists(fileName)) {
			HelltoothTexture texture(fileName.c_str());
			HT_INFO("[Asset] Texture \"%s\" loaded!", fileName);
			return texture.getTexture();
		}

		HT_INFO("[Asset]\"%s\" not found! Creating one...", fileName);


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
		HT_INFO("[Asset] Texture \"%s\" loaded!", file);
		return texture;
	}

	RawModel* Asset::loadModelFromFile(std::string path) {
		const char* file = path.c_str();
		std::string fileName = utils::FileUtils::changeExtension(file, std::string("htmodel"));
		if (exists(fileName)) {
			HelltoothModel model(fileName.c_str());
			HT_INFO("[Asset] Model \"%s\" loaded!", fileName);
			return model.getRawModel();
		}

		HT_INFO("[Asset]\"%s\" not found! Creating one...", fileName);
		RawModel* rawModel = ObjLoader::loadObjFile(file);

		HelltoothModel::storeAsHelltoothModel(fileName.c_str(), rawModel);
		HT_INFO("[Asset] Model \"%s\" loaded!", fileName);
		return rawModel;
	}

} }