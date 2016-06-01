#pragma once

#define RAWMODEL_COORDS 0
#define RAWMODEL_TEXTURE_COORDS 1
#define RAWMODEL_NORMALS 2
#define RAWMODEL_COLORS 3

#include <GL/glew.h>
#include "../../../utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	class RawModel {
	private:
		bool usingColor;

		GLsizei positionSize;
		GLsizei textureCoordSize;
		GLsizei normalSize;;
		GLsizei indexSize;

		const GLfloat *positions;
		const GLfloat *textureCoords;
		const GLfloat *normals;
		const GLuint *indices;

	public:

		//RawModel(GLFloat array of positions, GLsizei positionSize in bytes)
		inline RawModel(GLfloat *positions, const GLsizei positionSize)
			: positionSize(positionSize), textureCoordSize(0), normalSize(0), indexSize(0) {
			this->textureCoords = nullptr;
			this->normals = nullptr;
			this->indices = nullptr;

			this->positions = positions;
		}

		inline ~RawModel() {
			delete[] positions;
			if(textureCoords != nullptr)
				delete[] textureCoords;
			if (normals != nullptr)
				delete[] normals;
			if (indices != nullptr)
				delete[] indices;
		}

		//storeData(int usage, GLfloat *data, Glsizei dataSize in bytes)
		inline void storeData(const int usage, const GLfloat *data, const GLsizei &dataSize) {
			switch (usage) {
			case RAWMODEL_COORDS:
				positions = data;
				positionSize = dataSize;
				break;
			case RAWMODEL_NORMALS:
				normals = data;
				normalSize = dataSize;
				break;
			case RAWMODEL_TEXTURE_COORDS:
				usingColor = false;
				textureCoords = data;
				textureCoordSize = dataSize;
				break;
			case RAWMODEL_COLORS:
				usingColor = true;
				textureCoords = data;
				textureCoordSize = dataSize;
				break;
			}
		}

		inline void storeData(const GLuint *data, const GLsizei &dataSize) {
			indices = data;
			indexSize = dataSize;
		}

		inline GLsizei getPositionSize() const { return positionSize; }
		inline GLsizei getTextureCoordsSize() const { return textureCoordSize; }
		inline GLsizei getNormalSize() const { return normalSize; }
		inline GLsizei getIndexSize() const { return indexSize; }

		inline const GLfloat* getPositions() const { return positions; }
		inline const GLfloat* getTextureCoords() const { return textureCoords; }
		inline const GLfloat* getNormals() const { return normals; }
		inline const GLuint* getIndices() const { return indices; }

		inline bool usingColors() const { return usingColor; }
	};

} }
