#pragma once

#include <vector>

#include "FileSystem/FileSystem.h"

#include "graphics/rendering/Renderable.h"
#include "graphics/textures/Texture.h"
#include "graphics/rendering/Skybox.h"

#include "utils/Internal.h"
#include "utils/String.h"
#include "utils/memory/MemoryManager.h"

namespace ht { namespace assets {

	struct Path {
	public:
		enum Type {
			MODEL,
			TEXTURE,
			CUBEMAP,

			UNKOWN
		} type = UNKOWN;

		std::vector<utils::String> paths;

		Path& addModelPath(utils::String path);
		Path& addTexturePath(utils::String path);
		Path& addSkyboxPath(utils::String path);
	};

	class ResourceStack {
	private:
		std::vector<Path> paths;
		std::vector<void*> resources;

		uint16 loaded = 0;

	public:
		ResourceStack() {}
		~ResourceStack();

		void queueUp();
		void prepareResources();
		bool isLoaded() { return loaded == paths.size(); }

		__forceinline Path& operator[](uint32 id) {
			if (paths.size() <= id) { paths.resize(id); paths.push_back(Path()); }
			return paths[id];
		}

		__forceinline graphics::Renderable* getAsModel(uint32 id) {
			if (paths[id].type != Path::MODEL) { HT_ERROR("[ResourceStack] Type is not compatible!"); return nullptr; }
			return (graphics::Renderable*)resources[id];
		}

		__forceinline graphics::Texture* getAsTexture(uint32 id) {
			if (paths[id].type != Path::TEXTURE) { HT_ERROR("[ResourceStack] Type is not compatible!"); return nullptr; }
			return (graphics::Texture*)resources[id];
		}

		__forceinline graphics::Skybox* getAsSkybox(uint32 id) {
			if (paths[id].type != Path::CUBEMAP) { HT_ERROR("[ResourceStack] Type is not compatible!"); return nullptr; }
			return (graphics::Skybox*)resources[id];
		}
		__forceinline unsigned int getSize() { return paths.size(); }

	};
} }