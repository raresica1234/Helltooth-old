#include "FileSystem.h"
#include <FreeImage/FreeImage.h>

namespace ht { namespace assets {
	using namespace utils;
	using namespace graphics;

	FileSystem* FileSystem::fileSystem = nullptr;

	FileSystem::FileSystem() {
		frontLoaded.store(false);
		running.store(false);

		front.store(nullptr);
		back.store(nullptr);
	}

	void FileSystem::addToQueue(utils::String path) {
		Node *newNode = new Node(path);
		if (front.load() == nullptr)
			front.store(newNode);
		else
			back.load()->next = newNode;

		back.store(newNode);
	}

	void FileSystem::loadNext() {
		Node* current = front.load();
		while (front.load() != back.load()) {
			if (front.load()->resource.res == nullptr)
				break;
			current = front.load()->next;
		}

		String path = current->path;

		bool success = false;

		//test what path is:
		std::vector<String> strings = path.split('.');
		
		String lastString = strings[strings.size() - 1];
		for (int i = 0; i < lastString.size; i++) {
			printf("%x ", lastString[i]);
		}
		Resource r;
		if (lastString == "htmodel" || lastString == "obj") {
			r.type = Resource::OBJ_MODEL;
			r.res = (void*)API::loadObjFile(path);
			success = true;
		}
		
		const char* file = path.c_str();

		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file);


		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(file);

		if (FreeImage_FIFSupportsReading(fif)) {
			r.type = Resource::TEXTURE;
			unsigned int id = TextureManager::Get()->createTextureFromFile(path);
			r.res = (void*)TextureManager::Get()->getTexture(id);
			success = true;
		}

		if(!success)
			HT_ERROR("[FileSystem] Resource type not supported!");
		current->resource = r;
		frontLoaded.store(frontLoaded.load() + 1);
	}

} }