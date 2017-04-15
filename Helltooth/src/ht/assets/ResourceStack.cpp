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

		std::vector<String> strings = path.split('.');

		String additions[6] = { "_left", "_right", "_top", "_bottom", "_back", "_front" };

		for (int i = 0; i < 6; i++) {
			String currPath = strings[0];
			currPath += additions[i] + "." + strings[1];
			paths.push_back(currPath);
		}

		return *this;
	}

	ResourceStack::~ResourceStack() { }

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
				for (unsigned int i = 1; i < path.paths.size(); i++) {
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
			else if (path.type == path.CUBEMAP) {
				Skybox* skybox = htnew Skybox();
				for (unsigned int i = 0; i < path.paths.size(); i++) {
					TextureData* textureData = FileSystem::Get()->getAsTextureData(FileSystem::Get()->getNextResource());
					skybox->addTexture(textureData, (Face)((unsigned int)RIGHT + i));
				}
				resources.push_back((void*)skybox);
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
