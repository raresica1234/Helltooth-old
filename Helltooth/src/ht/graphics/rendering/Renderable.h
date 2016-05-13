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

		GLsizei indicesSize;
		GLsizei vertexSize;
		GLsizei normalSize;
		GLsizei textureSize;

		const GLfloat *positions;
		const GLint *indices;
		const GLfloat *normals;
		const GLfloat *textureCoords;

		std::vector<GLuint> vbos;

		GLuint ibo;

		bool usingIndices;

	public:
		Renderable();
		~Renderable();

		void bindVAO() const;
		void unbindVAO() const;

		void flush() const;

		void addBufferData(const GLfloat *data, const GLsizei &dataSize, const int &type);
		void addBufferData(const GLint *data, const GLsizei &dataSize);

		inline const GLfloat* getPositions() {
			return positions;
		}

		inline const GLint* getIndices() {
			return indices;
		}

		inline const GLfloat *getNormals() {
			return normals;
		}

		inline const GLfloat *getTextureCoords() {
			return textureCoords;
		}
	
		inline const GLsizei getVertexSize() {
			return vertexSize;
		}

		inline const GLsizei getIndicesCount() {
			return indicesSize;
		}

	protected:
		void storeDataInAttribNumber(const unsigned int &number, const unsigned int &count, const GLsizei &dataSize, const GLfloat *data);
		void storeIndices(const GLint *data, const GLsizei &dataSize);
	};

} } 