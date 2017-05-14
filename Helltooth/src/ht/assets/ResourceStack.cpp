#include "ResourceStack.h"

namespace ht { namespace assets {
	using namespace utils;
	using namespace graphics;

	Path& Path::addModelPath(String path) {
		type = MODEL;
		paths.push_back(path);

		return *this;
	}

	Path& Path::addTexturePath(String path) {
		if (type != MODEL)
			type = TEXTURE;

		paths.push_back(path);

		return *this;
	}

	Path& Path::addSkyboxPath(String path) {
		type = CUBEMAP;

		paths.push_back(path);

		return *this;
	}

	ResourceStack::~ResourceStack() { }

	void ResourceStack::queueUp() {
		for (Path path : paths) 
			for (String str : path.paths) 
				FileSystem::Get()->addToQueue(str);
	}

	void ResourceStack::prepareResources() {
		Path path = paths[loaded];
		if (FileSystem::Get()->hasLoadedResources(path.paths.size())) {
			if (path.type == path.MODEL) {
				Renderable* renderable = htnew Renderable();
				RawModel* model = FileSystem::Get()->getAsModel(FileSystem::Get()->getNextResource());
				renderable->loadRawModel(model);
				for (uint32 i = 1; i < path.paths.size(); i++) {
					TextureData* textureData = FileSystem::Get()->getAsTextureData(FileSystem::Get()->getNextResource());
					uint32 id = TextureManager::Get()->createTextureFromData(textureData);
					renderable->addTexture(TextureManager::Get()->getTexture(id));
				}
				resources.push_back((void*)renderable);
			}
			else if(path.type == path.TEXTURE) {
				Resource res = FileSystem::Get()->getNextResource();
				TextureData* textureData = FileSystem::Get()->getAsTextureData(res);
				uint32 id = TextureManager::Get()->createTextureFromData(textureData);
				const Texture* texture = TextureManager::Get()->getTexture(id);
				resources.push_back((void*)texture);
			}
			else if (path.type == path.CUBEMAP) {
				Skybox* skybox = htnew Skybox();
				Cubemap* cubemap = FileSystem::Get()->getAsCubemap(FileSystem::Get()->getNextResource());
				skybox->addCubemap(cubemap);
				resources.push_back((void*)skybox);
			}
			loaded++;
		}
	}
} }