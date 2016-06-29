#pragma once

#define RENDERABLE_COORDS 0
#define RENDERABLE_TEXTURE_COORDS 1
#define RENDERABLE_NORMALS 2
#define RENDERABLE_COLORS 3

#include "../textures/Texture.h"

#include "vertex.h"
#include "../API.h"
#include "../../utils/memory/MemoryManager.h"
#include "model/RawModel.h"


namespace ht { namespace graphics {

	class Renderable {
	private:
		VAO* vao;
		VBO* vbos;
		IBO* ibo;

		const Texture* texture;

		bool usingIbo;

		unsigned int vboNumber;

	public:
		//Construcotr
		Renderable();
		~Renderable();

		//load all the data from a rawModel
		void loadRawModel(const RawModel* model);

		//Store data
		void storeData(const int usage, const GLfloat *data, const GLsizei &dataSize);
		void storeData(const GLuint *data, const GLsizei &dataSize);

		//Render
		void render() const;

		//Get vao ID
		inline GLuint getVaoID() { return vao->getID(); }

		//prepare for rendering
		inline void prepare() { 
			vao->bindVAO();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->getID());
		}

		//Unbind vao
		inline void end() { vao->unbindVAO(); }

		//set texture
		inline void setTexture(const Texture* texture) { this->texture = texture; }

	};

} }