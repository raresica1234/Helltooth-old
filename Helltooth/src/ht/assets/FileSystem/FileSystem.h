#pragma once

#include <atomic>
#include <list>
#include <thread>

#include "../../utils/String.h"
#include "../../utils/Pair.h"

#include "../Asset.h"
#include "../../graphics/rendering/Renderable.h"
#include "../../graphics/textures/Texture.h"
#include "../../graphics/textures/TextureManager.h"

namespace ht { namespace assets {


	struct Resource {
		void* res = nullptr;
		enum Type {
			OBJ_MODEL,
			TEXTURE,

			UNKOWN
		} type = UNKOWN;
	};

	class FileSystem {
	private:
		static FileSystem* fileSystem;
			
		struct Node {
			Resource resource;
			String path;

			Node* next;

			Node(String path) : path(path) {}
		};

		std::atomic<Node*> front;
		std::atomic<Node*> back;

		std::atomic<int> frontLoaded;
		std::atomic<bool> running;

	public:

	public:
		FileSystem();
		~FileSystem() {}
		void addToQueue(utils::String path);

		__forceinline bool hasLoadedResources() {
			return frontLoaded.load() > 0;
		}

		__forceinline Resource getNextResource() {
			if (!frontLoaded.load() > 0)
				HT_ERROR("[FileSystem] No resource loaded!");
			else
				return Resource();

			Resource r = front.load()->resource;
			frontLoaded.store(frontLoaded.load() - 1);
			return r;
		}

		__forceinline graphics::RawModel* getAsModel(Resource& r) {
			if (r.type == Resource::OBJ_MODEL) {
				return (graphics::RawModel*)r.res;
			}
			HT_ERROR("[FileSystem] Resource type not correct!");
			return nullptr;
		}

		__forceinline graphics::Texture* getAsTexture(Resource& r) {
			if (r.type == Resource::TEXTURE) {
				return (graphics::Texture*)r.res;
			}
			HT_ERROR("[FileSystem] Resource type not correct!");
			return nullptr;
		}

		__forceinline bool isFrontLoaded() { return frontLoaded.load(); }

		__forceinline static void Init() {
			if (!fileSystem) {
				fileSystem = htnew FileSystem();
				return;
			}
			HT_ERROR("[FileSytem] Reinitialization not possible!");
		}

		__forceinline static FileSystem* Get() {
			if(fileSystem)
				return fileSystem;
			else {
				Init();
				HT_ERROR("[FileSystem] FileSystem not initialized, initialization forced.");
				return fileSystem;
			}
		}

		__forceinline static void End() {
			if (fileSystem) {
				fileSystem->running.store(false);
				del fileSystem;
				fileSystem = nullptr;
				return;
			}
			HT_ERROR("[FileSystem] Deletion not possible, FileSystem not initialized.");
		}

	protected:
		void loadNext();

		static void start(FileSystem* fs) {
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

		bool isNextLoadingAvaliable() {
			if (!front.load())
				return false;

			Node* current = front.load();

			while (front.load() != back.load()) {
				if (front.load()->resource.res == nullptr)
					return true;
				current = front.load()->next;
			}
			return false;
		}

		Resource dequeue() {
			if (!front.load()) {
				HT_ERROR("[FileSystem] No resource loaded!");
				return Resource();
			}

			Node* temp = front.load();
			Resource r = temp->resource;

			front.store(front.load()->next);
			del temp;
			return r;
		}
	};

} }
