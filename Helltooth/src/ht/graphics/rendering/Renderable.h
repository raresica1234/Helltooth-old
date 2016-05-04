#pragma once

#include "../API.h"

#include <iostream>
#include <GL/glew.h>

#include <vector>

#define RENDERABLE_COORDS 1
#define RENDERABLE_NORMAL 2
#define RENDERABLE_TEXTURE 3
#define RENDERABLE_COLOR 4


namespace ht { namespace graphics { 

	class Renderable {
	private:
		GLuint vaoID;
		unsigned int vboNumber;

		GLsizei indicesSize;
		GLsizei vertexSize;

		std::vector<GLuint> vbos;

		GLuint ibo;

		bool usingIndices;

	public:
		Renderable();
		~Renderable();

		void bindVAO();
		void unbindVAO();

		void flush();

		void addBufferData(const GLfloat *data, const GLsizei &dataSize, const int &type);
		void addBufferData(const GLint *data, const GLsizei &dataSize);

	protected:
		void storeDataInAttribNumber(const unsigned int &number, const unsigned int &count, const GLsizei &dataSize, const GLfloat *data);
		void storeIndices(const GLint *data, const GLsizei &dataSize);
	};

} } 