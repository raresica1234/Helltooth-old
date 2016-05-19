#pragma once

#include <GL\glew.h>

namespace ht { namespace graphics {

	class VAO {
	private:
		GLuint id; //VAO id

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
		inline GLuint getID() { return id; }
	};

	class VBO {
	private:
		GLuint id; //VAO id
		GLsizei floatCount; //This will be stored in floats, not bytes.
		GLsizei count; //The actual count of the vertices's components

	public:
		//Create new VBO
		VBO() { glGenBuffers(1, &id); }

		//Delete vbo
		~VBO() { unbindVBO(); glDeleteBuffers(1, &id); }

		//Store data
		//Usage: storeDataInAttribList(number of the attribute list, count of the vertex size, dataSize in bytes, data);
		void storeDataInAttribList(const GLsizei &number, const GLsizei &count, const GLsizei &dataSize, const GLfloat *data) {
			this->floatCount = dataSize / sizeof(GLfloat);
			this->count = count;

			bindVBO();
			glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

			glEnableVertexAttribArray(number);
			glVertexAttribPointer(number, count, GL_FLOAT, GL_FALSE, count * sizeof(GLfloat), 0);
		}

		//Bind vbo
		inline void bindVBO() { glBindBuffer(GL_ARRAY_BUFFER, id); }

		//Unbind vbo
		inline void unbindVBO() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	};

	class IBO {
	private:
		GLuint id;
		GLsizei indicesCount;

	public:
		//Create new IBO ( Indices Buffer Object )
		IBO() { glGenBuffers(1, &id); }

		//Delete IBO
		~IBO() { unbindIBO(); glDeleteBuffers(1, &id); }

		//Store indices
		//Usage: storeIndices(data in GLint, dataSize in bytes)
		void storeIndices(const GLuint *data, const GLsizei &dataSize) {
			bindIBO();
			this->indicesCount = dataSize / sizeof(GLuint);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
		}

		//Bind IBO
		inline void bindIBO() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }

		//Unbind IBO
		inline void unbindIBO() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		inline GLsizei getCount() { return indicesCount; }
	};

} }
