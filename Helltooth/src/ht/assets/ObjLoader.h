#pragma once

#include "../graphics/rendering/model/RawModel.h"

#include "../maths/maths.h"
#include "../maths/vec2.h"
#include "../maths/vec3.h"

#include <vector>

#include "../utils/Log.h"
#include "../utils/memory/MemoryManager.h"
#include "../utils/String.h"

namespace ht { namespace assets {

	class ObjLoader {
	public:
		static ht::graphics::RawModel* LoadObjFile(ht::utils::String& path);

	private:
		__forceinline static void reserveMemory(std::vector<float> &vector, unsigned int size) {
			if (vector.size() <= size)
				vector.resize(size + 1);
		}

		__forceinline static void processVertex(ht::maths::vec3 vertex, std::vector<unsigned int> &indices, std::vector<ht::maths::vec2> &textures,
			std::vector<ht::maths::vec3> &normals, std::vector<float> &textureArray, std::vector<float> &normalsArray) {

			unsigned int currentVertexPointer = (unsigned int)vertex.x - 1;
			indices.push_back(currentVertexPointer);
			maths::vec2 currentTex = textures[((unsigned int)vertex.y - 1)];

			reserveMemory(textureArray, currentVertexPointer * 2 + 1);
			textureArray[currentVertexPointer * 2] = currentTex.x;
			textureArray[currentVertexPointer * 2 + 1] = currentTex.y;

			maths::vec3 currentNorm = normals[(unsigned int)vertex.z - 1];

			reserveMemory(normalsArray, currentVertexPointer * 3 + 2);

			normalsArray[currentVertexPointer * 3] = currentNorm.x;
			normalsArray[currentVertexPointer * 3 + 1] = currentNorm.y;
			normalsArray[currentVertexPointer * 3 + 2] = currentNorm.z;
		}

		static void readLine(FILE* file, char* buffer, unsigned int bufferLen = 256) {
			char c;
			unsigned int bufferIndex = 0;
			c = fgetc(file);
			while (!feof(file) && c != '\n' && bufferIndex < bufferLen) {
				buffer[bufferIndex++] = c;
				c = fgetc(file);
			}
			if (bufferIndex < bufferLen)
				buffer[bufferIndex] = '\0';
		}

		static char* skipWhitespaces(char* text) {
			char* ptr = text;
			while (*text == ' ' || *text == '\t' || *text == '\v')
				ptr++;
			return ptr;
		}

	};
} }