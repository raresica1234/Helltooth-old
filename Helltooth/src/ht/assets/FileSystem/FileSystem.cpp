#include "FileSystem.h"
#include <FreeImage.h>

namespace ht { namespace assets {
	using namespace utils;
	using namespace graphics;

	FileSystem* FileSystem::fileSystem = nullptr;

	FileSystem::FileSystem() {
		frontLoaded.store(0);

		running.store(false);
		dequeing.store(false);

		front.store(nullptr);
		back.store(nullptr);
	}

	void FileSystem::addToQueue(String path) {
		Node *newNode = htnew Node(path);
		if (front.load() == nullptr)
			front.store(newNode);
		else
			back.load()->next = newNode;

		back.store(newNode);
	}

	void FileSystem::loadNext() {
		Node* current = front.load();
		while (current != nullptr || current != back.load()) {
			if (current->resource.res == nullptr)
				break;
			current = current->next;
		}

		if (current->resource.res != nullptr)
			return;

		String path = current->path;

		bool success = false;

		//test what path is:
		std::vector<String> strings = path.split('.');
		
		String lastString = strings[strings.size() - 1];
		Resource r;
		if (lastString == "htmodel" || lastString == "obj") {
			r.type = Resource::OBJ_MODEL;
			r.res = (void*)API::loadObjFile(path);
			success = true;
		}
		else if (lastString == "htcubemap") {
			r.type = Resource::CUBEMAP;
			r.res = (void*)API::loadCubemap(path);
			success = true;
		}
		
		const char* file = path.c_str();

		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file);

		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(file);

		if (FreeImage_FIFSupportsReading(fif)) {
			r.type = Resource::TEXTURE;
			String outPath;
			VFS::resolvePhysicalPath(path, outPath);

			r.res = (void*)Asset::loadTextureDataFromFile(outPath);
			success = true;
		}

		if(!success)
			HT_ERROR("[FileSystem] Resource type not supported!");
		current->resource = r;
		int l = frontLoaded.load();
		frontLoaded.store(l + 1);
	}

	void FileSystem::start(FileSystem* fs) {
		if (fs->running.load())
			return;

		if (!(fs->running.load()))
			fs->running.store(true);

		while (fs->running.load()) {
			if (fs->isNextLoadingAvaliable())
				fs->loadNext();
			else
				Sleep(10);
		}
	}

	bool FileSystem::isNextLoadingAvaliable() {
		while (dequeing.load())
			Sleep(10);

		if (!front.load()) {
			return false;
		}

		Node* current = front.load();

		if (current->resource.res == nullptr) {
			return true;
		}

		while (current != back.load()) {
			if (current->resource.res == nullptr) {
				return true;
			}

			current = current->next;
		}

		if (back.load()->resource.res == nullptr) {
			return true;
		}

		return false;
	}

	Resource FileSystem::dequeue() {
		dequeing.store(true);
		if (!front.load()) {
			frontLoaded.store(0);
			HT_ERROR("[FileSystem] No resource loaded!");
			dequeing.store(false);
			return Resource();
		}
		uint16 current = frontLoaded.load();
		frontLoaded.store(current - 1);

		Node* temp = front.load();
		Resource r = temp->resource;
		front.store(temp->next);
		bool dele = false;
		if (temp == back.load() && frontLoaded.load() == 0) {
			dele = true;
		}
		del temp;

		if (dele) {
			front.store(nullptr);
			back.store(nullptr);
		}

		dequeing.store(false);
		return r;
	}
} }