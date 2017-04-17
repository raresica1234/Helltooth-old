#pragma once

#include <vector>

#include "FileSystem/FileSystem.h"

#include "graphics/rendering/Renderable.h"
#include "graphics/textures/Texture.h"
#include "graphics/rendering/Skybox.h"

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


		unsigned int loaded = 0;
	public:
		ResourceStack() {}
		~ResourceStack();

		__forceinline graphics::Renderable* getAsModel(unsigned int id) {
			Path p = paths[id];
			if (p.type != p.MODEL) {
				HT_ERROR("[ResourceStack] Type is not compatible!");
				return nullptr;
			}

			return (graphics::Renderable*)resources[id];
		}

		__forceinline graphics::Texture* getAsTexture(unsigned int id) {
			Path p = paths[id];
			if (p.type != p.TEXTURE) {
				HT_ERROR("[ResourceStack] Type is not compatible!");
				return nullptr;
			}

			return (graphics::Texture*)resources[id];
		}

		__forceinline graphics::Skybox* getAsSkybox(unsigned int id) {
			Path p = paths[id];
			if (p.type != p.CUBEMAP) {
				HT_ERROR("[ResourceStack] Type is not compatible!");
				return nullptr;
			}

			return (graphics::Skybox*)resources[id];
		}

		void queueUp();
		void prepareResources();
		bool isLoaded() { return loaded == paths.size(); }

		Path& operator[](unsigned int id);

		__forceinline unsigned int getSize() { return paths.size(); }

	};



} }

