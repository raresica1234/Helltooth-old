#pragma once

#define RENDERABLE_COORDS 0
#define RENDERABLE_TEXTURE_COORDS 1
#define RENDERABLE_NORMALS 2
#define RENDERABLE_COLORS 3

#include "Vertex.h"

#include "model/RawModel.h"

#include "../API.h"

#include "../textures/Texture.h"
#include "../textures/TextureManager.h"

#include "utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	class Renderable {
	private:
		VAO* vao;
		VBO* vbos;
		IBO* ibo;

		std::vector<const Texture*> textures;

		bool usingIbo;

		uint32 vboNumber;

	public:
		//Construcotr
		Renderable();
		~Renderable();

		//load all the data from a rawModel
		void loadRawModel(const RawModel* model);

		//Store data
		void storeData(const int32 usage, const f32 *data, const uint32 &dataSize);
		void storeData(const uint32 *data, const uint32 &dataSize);

		//Render
		void render() const;

		//Prepare for rendering
		void prepare() const;
		//Get vao ID
		__forceinline uint32 getVaoID() { return vao->getID(); }

		//Unbind vao
		__forceinline void end() const { vao->unbindVAO(); }

		//set texture
		__forceinline void addTexture(const uint32 &id) { textures.push_back(TextureManager::Get()->getTexture(id));}

		__forceinline void addTexture(const Texture* texture) { textures.push_back(texture); }

	};

} }