#pragma once

#define RAWMODEL_COORDS 0
#define RAWMODEL_TEXTURE_COORDS 1
#define RAWMODEL_NORMALS 2
#define RAWMODEL_COLORS 3

#include <GL/glew.h>

#include "utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	class RawModel {
	private:
		bool usingColor;

		//Size of arrays
		uint32 positionSize;
		uint32 textureCoordSize;
		uint32 normalSize;;
		uint32 indexSize;

		//Arrays of data for model
		const f32 *positions;
		const f32 *textureCoords;
		const f32 *normals;
		const uint32 *indices;

	public:

		//RawModel(GLFloat array of positions, GLsizei positionSize in bytes)
		__forceinline RawModel(f32 *positions, const uint32 positionSize)
			: positionSize(positionSize), textureCoordSize(0), normalSize(0), indexSize(0) {
			this->textureCoords = nullptr;
			this->normals = nullptr;
			this->indices = nullptr;

			this->positions = positions;
		}

		//Deconstructor
		__forceinline ~RawModel() {
			del[] positions;
			if(textureCoords != nullptr)
				del[] textureCoords;
			if (normals != nullptr)
				del[] normals;
			if (indices != nullptr)
				del[] indices;
		}

		//storeData(int usage, GLfloat *data, Glsizei dataSize in bytes)
		__forceinline void storeData(const int32 usage, const f32 *data, const uint32 &dataSize) {
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

		//storeData(Gluint *data, const GLsizei dataSize in bytes) for indices
		__forceinline void storeData(const uint32 *data, const uint32 &dataSize) {
			indices = data;
			indexSize = dataSize;
		}

		//some getters
		__forceinline uint32 getPositionSize() const { return positionSize; }
		__forceinline uint32 getTextureCoordsSize() const { return textureCoordSize; }
		__forceinline uint32 getNormalSize() const { return normalSize; }
		__forceinline uint32 getIndexSize() const { return indexSize; }

		__forceinline const f32* getPositions() const { return positions; }
		__forceinline const f32* getTextureCoords() const { return textureCoords; }
		__forceinline const f32* getNormals() const { return normals; }
		__forceinline const uint32* getIndices() const { return indices; }

		__forceinline bool usingColors() const { return usingColor; }
	};

} }
