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

	enum Type {
		OBJ_MODEL,
		TEXTURE,

		UNKOWN
	};

	class FileSystem {
	private:
		static FileSystem* fileSystem;

		struct Resource {
			void* res;
			Type type = UNKOWN;
		};

		std::atomic<std::list<utils::String>> paths;
		std::atomic<std::list<Resource>> fifo;

		std::atomic<bool> frontLoaded;

		std::atomic<bool> running;
	public:

		FileSystem();

		void addToQueue(utils::String path);

		__forceinline Resource getNextResource() {
			Resource r = fifo.load().front();
			fifo.load().pop_front();
			if (fifo.load().size() < 1)
				frontLoaded.store(false);
			return r;
		}

		__forceinline RawModel* getAsModel(Resource r) {
			if (r.type == OBJ_MODEL) {
				return (RawModel*)r.res;
			}
			HT_ERROR("[FileSystem] Resource type not correct!");
			return nullptr;
		}

		__forceinline Texture* getAsTexture(Resource r) {
			if (r.type == TEXTURE) {
				return (Texture*)r.res;
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
				if (fs->paths.load().size() > 1)
					fs->loadNext();
				else
					Sleep(10);
			}
		}
	};

} }
