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

	ResourceStack::~ResourceStack() {
		for (void* resource : resources)
			if(resource)
				del resource;
	}

	void ResourceStack::queueUp() {
		for (Path path : paths) 
			for (utils::String str : path.paths) 
				FileSystem::Get()->addToQueue(str);
		
	}

	void ResourceStack::prepareResources() {
		Path path = paths[loaded];
		
		if (FileSystem::Get()->hasLoadedResources(path.paths.size())) {
			if (path.type == path.MODEL) {
				Renderable* renderable = htnew Renderable();
				RawModel* model = FileSystem::Get()->getAsModel(FileSystem::Get()->getNextResource());
				renderable->loadRawModel(model);
				for (int i = 1; i < paths.size(); i++) {
					TextureData* textureData = FileSystem::Get()->getAsTextureData(FileSystem::Get()->getNextResource());
					unsigned int id = TextureManager::Get()->createTextureFromData(textureData);
					renderable->addTexture(TextureManager::Get()->getTexture(id));
				}
				resources.push_back((void*)renderable);
			}
			else if(path.type == path.TEXTURE) {
				auto res = FileSystem::Get()->getNextResource();
				TextureData* textureData = FileSystem::Get()->getAsTextureData(res);
				unsigned int id = TextureManager::Get()->createTextureFromData(textureData);
				const Texture* texture = TextureManager::Get()->getTexture(id);
				resources.push_back((void*)texture);
			}
			loaded++;
		}
	}

	Path& ResourceStack::operator[](unsigned int id) {
		if (paths.size() <= id) {
			paths.resize(id);
			paths.push_back(Path());
		}
		return paths[id];
	}

} }
