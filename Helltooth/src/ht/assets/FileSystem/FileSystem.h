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
			utils::String path;

			Node* next;

			Node(utils::String path) : path(path) {}
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

		__forceinline bool hasLoadedResources(unsigned int size = 1) {
			return frontLoaded.load() >= size;
		}

		__forceinline Resource getNextResource() {
			if (!(frontLoaded.load() > 0)) {
				HT_ERROR("[FileSystem] No resource loaded!");
				return Resource();
			}

			Resource r = front.load()->resource;
			frontLoaded.store(frontLoaded.load() - 1);
			dequeue();
			return r;
		}

		__forceinline graphics::RawModel* getAsModel(Resource& r) {
			if (r.type == Resource::OBJ_MODEL) {
				return (graphics::RawModel*)r.res;
			}
			HT_ERROR("[FileSystem] Resource type not correct!");
			return nullptr;
		}

		__forceinline assets::TextureData* getAsTextureData(Resource& r) {
			if (r.type == Resource::TEXTURE) {
				return (assets::TextureData*)r.res;
			}
			HT_ERROR("[FileSystem] Resource type not correct!");
			return nullptr;
		}

		__forceinline static void Init() {
			if (!fileSystem) {
				fileSystem = htnew FileSystem();

				std::thread fs(start, fileSystem);
				fs.detach();

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

			if (current->resource.res == nullptr)
				return true;

			while (current != back.load()) {
				if (current->resource.res == nullptr) {
					HT_ERROR("Space found!");
					return true;
				}
				
				current = current->next;
			}
			if (back.load()->resource.res == nullptr)
				return true;

			return false;
		}

		Resource dequeue() {
			if (!front.load()) {
				HT_ERROR("[FileSystem] No resource loaded!");
				return Resource();
			}

			Node* temp = front.load();
			Resource r = temp->resource;
			front.store(temp->next);
			del temp;
			return r;
		}
	};

} }