#pragma once

#include <GL/glew.h>

#include "utils/Internal.h"

namespace ht { namespace graphics {

	class VAO {
	private:
		uint32 id; //VAO id

	public:
		//Create a new VAO
		VAO() { glGenVertexArrays(1, &id); }

		//Delete existing VAO
		~VAO() { unbindVAO(); glDeleteVertexArrays(1, &id); }

		//Unbind current VAO
		inline void unbindVAO() { glBindVertexArray(0); }

		//Bind existing VAO
		inline void bindVAO() { glBindVertexArray(id); }

		//Returns id
		inline uint32 getID() { return id; }
	};

	class VBO {
	private:
		uint32 id; //VAO id
		uint32 floatCount; //This will be stored in floats, not bytes.
		uint32 count; //The actual count of the vertices's components

	public:
		//Create new VBO
		VBO() { glGenBuffers(1, &id); }

		//Delete vbo
		~VBO() { unbindVBO(); glDeleteBuffers(1, &id); }

		//Store data
		//Usage: storeDataInAttribList(number of the attribute list, count of the vertex size, dataSize in bytes, data);
		void storeDataInAttribList(const uint32 &number, const uint32 &count, const uint32 &dataSize, const f32 *data) {
			this->floatCount = dataSize / sizeof(f32);
			this->count = count;

			bindVBO();
			glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

			glEnableVertexAttribArray(number);
			glVertexAttribPointer(number, count, GL_FLOAT, GL_FALSE, count * sizeof(f32), 0);
		}

		//Bind vbo
		inline void bindVBO() { glBindBuffer(GL_ARRAY_BUFFER, id); }

		//Unbind vbo
		inline void unbindVBO() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	};

	class IBO {
	private:
		uint32 id;
		uint32 indicesCount;

	public:
		//Create new IBO ( Indices Buffer Object )
		IBO() { glGenBuffers(1, &id); }

		//Delete IBO
		~IBO() { unbindIBO(); glDeleteBuffers(1, &id); }

		//Store indices
		//Usage: storeIndices(data in GLint, dataSize in bytes)
		void storeIndices(const uint32 *data, const uint32 &dataSize) {
			bindIBO();
			this->indicesCount = dataSize / sizeof(uint32);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
		}

		void storeIndices(const uint16 *data, const uint32 count) {
			bindIBO();
			this->indicesCount = count;

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint16), data, GL_STATIC_DRAW);
		}

		//Bind IBO
		inline void bindIBO() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }

		//Unbind IBO
		inline void unbindIBO() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		inline uint32 getCount() { return indicesCount; }
	};

} }
