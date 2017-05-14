#pragma once

#include <vector>

#include "graphics/rendering/model/RawModel.h"

#include "maths/maths.h"
#include "maths/vec2.h"
#include "maths/vec3.h"

#include "utils/Internal.h"
#include "utils/Log.h"
#include "utils/String.h"
#include "utils/memory/MemoryManager.h"

namespace ht { namespace assets {

#pragma region Vertex
#define NO_INDEX -1
	struct Vertex {
	public:
		maths::vec3 position;
		uint32 textureIndex = NO_INDEX;
		uint32 normalIndex = NO_INDEX;
		uint32 index;
		f32 length;

		Vertex* duplicatedVertex = nullptr;

	public:
		Vertex(uint32 index, maths::vec3 position)
			: index(index), position(position), length(position.length()) {}

		~Vertex() {
			//TODO: Fix this
			//if (duplicatedVertex)
				//del duplicatedVertex;
		}

		bool isSet() {
			return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
		}

		bool hasSameTextureAndNormal(GLuint textureIndexOther, GLuint normalIndexOther) {
			return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
		}
	};
#pragma endregion Vertex Structure

	class ObjLoader {
	public:
		static graphics::RawModel* LoadObjFile(utils::String& path);

	private:
		__forceinline static void reserveMemory(std::vector<f32> &vector, uint32 size) { 
			if (vector.size() <= size) vector.resize(size + 1);
		}

		static void processVertex(maths::vec3 &vertex, std::vector<Vertex> &vertices, std::vector<uint32> &indices);
		static void dealWithAlreadyProcessedVertex(Vertex &previousVertex, uint32 &newTextureIndex,
			uint32 &newNormalIndex, std::vector<uint32> &indices, std::vector<Vertex> &vertices);
		static void convertDataToArrays(std::vector<Vertex> &vertices, std::vector<maths::vec2> &textures,
			std::vector<maths::vec3> &normals, f32 *verticesArray, f32 *texturesArray, f32 *normalsArray);

		__forceinline static void removeUnusedVertices(std::vector<Vertex> &vertices) {
			for (Vertex& vertex : vertices) {
				if (!vertex.isSet()) { vertex.textureIndex = 0; vertex.normalIndex = 0; }
			}
		}

		static void readLine(FILE* file, char* buffer, uint32 bufferLen = 256);
		static sbyte* skipWhitespaces(sbyte* text);
	};
} }