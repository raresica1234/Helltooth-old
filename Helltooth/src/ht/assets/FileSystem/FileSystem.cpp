#include <FreeImage/FreeImage.h>
#include "FileSystem.h"

namespace ht { namespace assets {
	using namespace utils;
	using namespace graphics;

	FileSystem* FileSystem::fileSystem = nullptr;

	FileSystem::FileSystem() {
		frontLoaded.store(false);
		running.store(false);

		std::thread fs(start, this);
		fs.detach();
	}

	void FileSystem::addToQueue(utils::String path) {
		paths.load().push_back(path);
	}

	void FileSystem::loadNext() {
		String path = paths.load().front();
		paths.load().pop_front();

		bool success = false;

		//test what path is:
		std::vector<String> strings = path.split('/');
		
		String lastString = strings[strings.size() - 1];
		Resource r;
		if (lastString == ".htmodel" || lastString == ".obj") {
			r.type = OBJ_MODEL;
			r.res = (void*)API::loadObjFile(path);
			success = true;
		}
		
		const char* file = path.c_str();

		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file);


		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(file);

		if (FreeImage_FIFSupportsReading(fif)) {
			r.type = TEXTURE;
			unsigned int id = TextureManager::Get()->createTextureFromFile(path);
			r.res = (void*)TextureManager::Get()->getTexture(id);
			success = true;
		}
		if(!success)
			HT_ERROR("[FileSystem] Resource type not supported!");
		fifo.load().push_back(r);
		frontLoaded.store(true);
	}

} }