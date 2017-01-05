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

#pragma region Vertex
#define NO_INDEX -1
	struct Vertex {
	public:
		maths::vec3 position;
		GLint textureIndex = NO_INDEX;
		GLint normalIndex = NO_INDEX;
		GLuint index;
		GLfloat length;

		Vertex* duplicatedVertex = nullptr;

	public:
		Vertex(GLuint index, maths::vec3 position)
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
		__forceinline static void reserveMemory(std::vector<float> &vector, unsigned int size) {
			if (vector.size() <= size)
				vector.resize(size + 1);
		}

		__forceinline static void processVertex(maths::vec3 &vertex, std::vector<Vertex> &vertices, std::vector<GLuint> &indices) {
			GLuint index = vertex.x - 1;
			Vertex& currentVertex = vertices[index];
			GLint textureIndex = vertex.y - 1;
			GLint normalIndex = vertex.z - 1;
			if (!currentVertex.isSet()) {
				currentVertex.textureIndex = textureIndex;
				currentVertex.normalIndex = normalIndex;
				indices.push_back(index);
			}
			else {
				dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
			}
		}

		__forceinline static void dealWithAlreadyProcessedVertex(Vertex &previousVertex, GLint &newTextureIndex,
			GLint &newNormalIndex, std::vector<GLuint> &indices, std::vector<Vertex> &vertices) {
			if (previousVertex.hasSameTextureAndNormal(newTextureIndex, newNormalIndex))
				indices.push_back(previousVertex.index);
			else 
				if (previousVertex.duplicatedVertex != nullptr)
					dealWithAlreadyProcessedVertex(*previousVertex.duplicatedVertex, newTextureIndex, newNormalIndex, indices, vertices);
				else {
					Vertex* duplicateVertex = htnew Vertex(vertices.size(), previousVertex.position);
					duplicateVertex->textureIndex = newTextureIndex;
					duplicateVertex->normalIndex = newNormalIndex;
					previousVertex.duplicatedVertex = duplicateVertex;
					vertices.push_back(*duplicateVertex);
					indices.push_back(duplicateVertex->index);
				}
			
		}

		__forceinline static void convertDataToArrays(std::vector<Vertex> &vertices, std::vector<maths::vec2> &textures,
			std::vector<maths::vec3> &normals, float *verticesArray, float *texturesArray, float *normalsArray) {
			for (GLuint i = 0; i < vertices.size(); i++) {
				Vertex currentVertex = vertices[i];
				maths::vec3 position = currentVertex.position;
				maths::vec2 textureCoord = textures[currentVertex.textureIndex];
				maths::vec3 normalVector = normals[currentVertex.normalIndex];
				verticesArray[i * 3] = position.x;
				verticesArray[i * 3 + 1] = position.y;
				verticesArray[i * 3 + 2] = position.z;
				texturesArray[i * 2] = textureCoord.x;
				texturesArray[i * 2 + 1] = textureCoord.y;
				normalsArray[i * 3] = normalVector.x;
				normalsArray[i * 3 + 1] = normalVector.y;
				normalsArray[i * 3 + 2] = normalVector.z;
			}
		}

		__forceinline static void removeUnusedVertices(std::vector<Vertex> &vertices) {
			for (Vertex& vertex : vertices) {
				if (!vertex.isSet()) {
					vertex.textureIndex = 0;
					vertex.normalIndex = 0;
				}
			}
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