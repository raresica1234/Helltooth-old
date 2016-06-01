#pragma once

#define RENDERABLE_COORDS 0
#define RENDERABLE_TEXTURE_COORDS 1
#define RENDERABLE_NORMALS 2
#define RENDERABLE_COLORS 3

#include "vertex.h"
#include "../API.h"
#include "../../utils/memory/MemoryManager.h"
#include "model/RawModel.h"

#include "../textures/Texture.h"

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
		Renderable();
		~Renderable();

		void loadRawModel(const RawModel* model);

		void storeData(const int usage, const GLfloat *data, const GLsizei &dataSize);
		void storeData(const GLuint *data, const GLsizei &dataSize);

		void render() const;

		inline GLuint getVaoID() { return vao->getID(); }

		inline void prepare() { 
			vao->bindVAO();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->getID());
		}

		inline void end() { vao->unbindVAO(); }

		inline void setTexture(const Texture* texture) { this->texture = texture; }

	};

} }