#include "Renderable.h"

namespace ht {	namespace graphics {

	Renderable::Renderable()
		: vboNumber(0), usingIndices(false)	{
		glGenVertexArrays(1, &vaoID);
	}

	void Renderable::bindVAO() {
		glBindVertexArray(vaoID);
	}

	void Renderable::unbindVAO() {
		glBindVertexArray(0);
	}

	void Renderable::addBufferData(const GLfloat *data, const GLsizei &dataSize, const int &type) {
		switch (type) {
		case RENDERABLE_COORDS:
#if API_MODE == API_MODE_2D
			storeDataInAttribNumber(0, 2, dataSize, data);
#else
			storeDataInAttribNumber(0, 3, dataSize, data);
#endif
			vertexSize = dataSize / sizeof(GLfloat);
			return;
		case RENDERABLE_TEXTURE:
			storeDataInAttribNumber(1, 2, dataSize, data);
			vboNumber++;
			return;
		case RENDERABLE_NORMAL:
			storeDataInAttribNumber(2, 3, dataSize, data);
			return;
		case RENDERABLE_COLOR:
			storeDataInAttribNumber(3, 4, dataSize, data);
			return;
		default:
			//FATAL ERROR ( logging system)
			std::cout << "Type incorrect!" << std::endl;
			return;
		}
	}

	void Renderable::addBufferData(const GLint *data, const GLsizei &dataSize) {
		storeIndices(data, dataSize);
		usingIndices = true;
	}

	void Renderable::storeDataInAttribNumber(const unsigned int &number, const unsigned int &count, const GLsizei &dataSize, const GLfloat *data) {
		GLuint vboID;

		glGenBuffers(1, &vboID);
		vbos.push_back(vboID);

		std::cout << "dataSize " << dataSize << std::endl;

		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(number);
		glVertexAttribPointer(number, count, GL_FLOAT, GL_FALSE, count * sizeof(float), 0);

		glEnableVertexAttribArray(number);

	}

	void Renderable::storeIndices(const GLint *data, const GLsizei &dataSize) {
		glGenBuffers(1, &ibo);
		indicesSize = dataSize / sizeof(GLint);

		std::cout << "indices " << indicesSize << std::endl;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

	}

	void Renderable::flush() {
		bindVAO();
		if (usingIndices) {
			glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, (void*) 0);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		unbindVAO();
	}

	Renderable::~Renderable() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_INDEX_ARRAY, 0);
		glBindVertexArray(0);

		glDeleteVertexArrays(1, &vaoID);
		
		for (GLuint vbo : vbos) {
			glDeleteBuffers(1, &vbo);
		}

	}
} }