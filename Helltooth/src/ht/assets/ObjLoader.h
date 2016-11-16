#pragma once

#include "../graphics/rendering/model/RawModel.h"

#include "../maths/maths.h"
#include "../maths/vec2.h"
#include "../maths/vec3.h"

#include <sstream>

#include "../utils/Log.h"
#include "../utils/memory/MemoryManager.h"
#include "../utils/List.h"
#include "../utils/String.h"

namespace ht { namespace assets {

	using namespace utils;
	using namespace maths;
	using namespace graphics;

	class ObjLoader {
	public:
		static RawModel* loadObjFile(String& path) {
			FILE* file = fopen(path.c_str(), "rt");
			if (file == nullptr) {
				HT_FATAL("[ObjLoader] file \"%s\" could not be opened!", path);
				return nullptr;
			}

			fseek(file, 0, SEEK_SET);

			Vec3s vertices;
			Vec2s textures;
			Vec3s normals;

			Floats texturesIndex;
			Floats normalsIndex;

			UInts indices;

			float* verticesArray = nullptr;
			float* normalsArray = nullptr;
			float* textureArray = nullptr;
			unsigned int* indicesArray = nullptr;

			while (!feof(file)) {
				char buffer[256] = { '\0' };
				readLine(file, buffer);
				char* textbegins = skipWhitespaces(buffer);
				std::string currentLine(textbegins);

				if (textbegins == "#") continue;

				if (currentLine.substr(0, 2) == "v ") {
					vec3 vertex;
					sscanf(textbegins, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
					vertices.push(vertex);
				} else if (currentLine.substr(0, 3) == "vt ") {
					vec2 texture;
					sscanf(textbegins, "vt %f %f", &texture.x, &texture.y);
					textures.push(texture);
				}
				else if (currentLine.substr(0, 3) == "vn ") {
					vec3 normal;
					sscanf(textbegins, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
					normals.push(normal);
				}
				else if (currentLine.substr(0, 2) == "f ") {
					vec3 vertex1, vertex2, vertex3;

					sscanf(textbegins, "f %f/%f/%f %f/%f/%f %f/%f/%f", &vertex1.x, &vertex1.y, &vertex1.z,
						&vertex2.x, &vertex2.y, &vertex2.z, &vertex3.x, &vertex3.y, &vertex3.z);

					processVertex(vertex1, indices, textures, normals, texturesIndex, normalsIndex);
					processVertex(vertex2, indices, textures, normals, texturesIndex, normalsIndex);
					processVertex(vertex3, indices, textures, normals, texturesIndex, normalsIndex);
				}
			}
			
			verticesArray = htnew float[vertices.size * 3];
			indicesArray = htnew unsigned int[indices.size];
			textureArray = htnew float[vertices.size * 2];
			normalsArray = htnew float[vertices.size * 3];

			texturesIndex.fit();
			normalsIndex.fit();

			memcpy(verticesArray, &vertices[0], vertices.size * 3 * sizeof(float));
			memcpy(indicesArray, &indices[0], indices.size * sizeof(unsigned int));
			memcpy(textureArray, &texturesIndex[0], vertices.size * 2 * sizeof(float));
			memcpy(normalsArray, &normalsIndex[0], vertices.size * 3 * sizeof(float));
			fclose(file);

			RawModel* model = htnew RawModel(verticesArray, vertices.size * 3 * sizeof(GLfloat));
			model->storeData(indicesArray, indices.size * sizeof(GLuint));
			model->storeData(RAWMODEL_NORMALS, normalsArray, vertices.size * 3 * sizeof(GLfloat));
			model->storeData(RAWMODEL_TEXTURE_COORDS, textureArray, vertices.size * 2 * sizeof(GLfloat));
			HT_INFO("[ObjLoader] Model \"%s\" loaded", path);
			return model;
		}

	private:
		static void reserveMemory(Floats &vector, unsigned int size) {
			if (vector.size <= size)
				vector.resize(size + 1);
		}

		static void processVertex(vec3 vertex, List<unsigned int> &indices, List<vec2> &textures,
			List<vec3> &normals, List<float> &textureArray, List<float> &normalsArray) {

			unsigned int currentVertexPointer = (unsigned int)vertex.x - 1;
			indices.push(currentVertexPointer);
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