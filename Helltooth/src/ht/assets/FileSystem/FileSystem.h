#pragma once

#include <atomic>
#include <list>
#include <thread>

#include "assets/Asset.h"

#include "utils/Internal.h"
#include "utils/String.h"
#include "utils/Pair.h"

#include "graphics/rendering/Renderable.h"
#include "graphics/textures/Texture.h"
#include "graphics/textures/TextureManager.h"

namespace ht { namespace assets {

	struct Resource {
		void* res = nullptr;
		enum Type {
			OBJ_MODEL,
			TEXTURE,
			CUBEMAP,

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

		std::atomic<Node*> front, back;

		std::atomic<uint16> frontLoaded;
		std::atomic<bool> running, dequeing;

	public:
		FileSystem();
		~FileSystem() {}
		void addToQueue(utils::String path);

		__forceinline bool hasLoadedResources(uint16 size = 1) {
			return frontLoaded.load() >= size;
		}

		__forceinline Resource getNextResource() {
			if (!(frontLoaded.load() > 0)) { HT_ERROR("[FileSystem] No resource loaded!"); return Resource(); }
			return dequeue();
		}

		__forceinline graphics::RawModel* getAsModel(Resource& r) {
			if (r.type == Resource::OBJ_MODEL) { return (graphics::RawModel*)r.res; }
			HT_ERROR("[FileSystem] Resource type not correct!");
			return nullptr;
		}

		__forceinline Cubemap* getAsCubemap(Resource& r) {
			if (r.type == Resource::CUBEMAP) { return (Cubemap*)r.res; }
			HT_ERROR("[FileSystem] Resource type not correct!");
			return nullptr;
		}

		__forceinline TextureData* getAsTextureData(Resource& r) {
			if (r.type == Resource::TEXTURE) { return (assets::TextureData*)r.res; }
			HT_ERROR("[FileSystem] Resource type not correct!");
			return nullptr;
		}

		__forceinline static void Init() {
			if (fileSystem) { HT_ERROR("[FileSystem] Reinitialization not possible!"); return;
			}
			fileSystem = htnew FileSystem();

			std::thread fs(start, fileSystem);
			fs.detach();
		}

		__forceinline static FileSystem* Get() {
			if(!fileSystem){ Init(); HT_ERROR("[FileSystem] FileSystem not initialized, initialization forced!"); }
			return fileSystem;
		}

		__forceinline static void End() {
			if (!fileSystem) { HT_ERROR("[FileSystem] Deletion not possible, FileSystem not initialized!"); return; }
			fileSystem->running.store(false);
			del fileSystem;
			fileSystem = nullptr;
		}

	protected:
		void loadNext();
		static void start(FileSystem* fs);
		bool isNextLoadingAvaliable();
		Resource dequeue();
	};
} }
