#pragma once

#include "RawModel.h"

#include "../../../maths/maths.h"
#include "../../../maths/vec2.h"
#include "../../../maths/vec3.h"

#include <vector>
#include <string>
#include <sstream>

#include "../../../utils/Log.h"
#include "../../../utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	class ObjLoader {
	private:

		inline static std::vector<std::string> split(const std::string &s, char delim) {
			std::vector<std::string> split;
			std::stringstream ss(s);
			std::string item;
			while (getline(ss, item, delim)) {
				split.push_back(item);
			}
			return split;
		}

	public:
		inline static RawModel* loadObjFile(const char* path) {
			FILE* file = fopen(path, "rt");
			if (file == nullptr) {
				HT_FATAL("[ObjLoader] file %s could not be opened!", path);
				return nullptr;
			}

			fseek(file, 0, FILE_END);
			long dataSize = ftell(file);
			char* data = new char[dataSize];

			fseek(file, 0, SEEK_SET);

			fread(data, 1, dataSize, file);
			fclose(file);
			std::string fileContent(data);
			std::vector<std::string> lines = split(fileContent, '\n');

			std::vector<maths::vec3> vertices;
			std::vector<maths::vec2> textures;
			std::vector<maths::vec3> normals;
			std::vector<unsigned int> indices;
			float* verticesArray = nullptr;
			float* normalsArray = nullptr;
			float* textureArray = nullptr;
			unsigned int* indicesArray = nullptr;
			size_t i;
			std::vector<std::string> currentLine;
			for (i = 0; i < lines.size(); i++) {
				currentLine.clear();
				currentLine = split(lines[i], ' ');

				if (lines[i].substr(0, 2) == "v ") {
					maths::vec3 vertex(std::stof(currentLine[1]), std::stof(currentLine[2]), std::stof(currentLine[3]));
					vertices.push_back(vertex);
				}
				else if (lines[i].substr(0, 3) == "vt ") {
					maths::vec2 texture(std::stof(currentLine[1]), std::stof(currentLine[2]));
					textures.push_back(texture);
				}
				else if (lines[i].substr(0, 3) == "vn ") {
					maths::vec3 normal(std::stof(currentLine[1]), std::stof(currentLine[2]), std::stof(currentLine[3]));
					normals.push_back(normal);
				}
				else if (lines[i].substr(0, 2) == "f ") {
					textureArray = new float[vertices.size() * 2];
					normalsArray = new float[vertices.size() * 3];
					break;
				}
			}

			for (i; i < lines.size(); i++) {
				currentLine = split(lines[i], ' ');
				
				if (currentLine[0] != "f")
					continue;

				std::vector<std::string> vertex1 = split(currentLine[1], '/');
				std::vector<std::string> vertex2 = split(currentLine[2], '/');
				std::vector<std::string> vertex3 = split(currentLine[3], '/');

				processVertex(vertex1, indices, textures, normals, textureArray, normalsArray);
				processVertex(vertex2, indices, textures, normals, textureArray, normalsArray);
				processVertex(vertex3, indices, textures, normals, textureArray, normalsArray);
			}

			verticesArray = new float[vertices.size() * 3];
			indicesArray = new unsigned int[indices.size()];
			int vertexPointer = 0;
			for (maths::vec3 vertex : vertices) {
				verticesArray[vertexPointer++] = vertex.x;
				verticesArray[vertexPointer++] = vertex.y;
				verticesArray[vertexPointer++] = vertex.z;
			}

			for (int i = 0; i < indices.size(); i++) {
				indicesArray[i] = indices[i];
			}

			RawModel* model = new RawModel(verticesArray, vertices.size() * 3 * sizeof(GLfloat));
			model->storeData(indicesArray, indices.size() * sizeof(GLuint));
			model->storeData(RAWMODEL_NORMALS, normalsArray, vertices.size() * 3 * sizeof(GLfloat));
			model->storeData(RAWMODEL_TEXTURE_COORDS, textureArray, vertices.size() * 2 * sizeof(GLfloat));
			return model;
		}


	private:
		static void processVertex(std::vector<std::string> &vertexData, std::vector<unsigned int> &indices,
			std::vector<maths::vec2> &textures, std::vector<maths::vec3> &normals, float* textureArray, float* normalsArray) {

			unsigned int currentVertexPointer = std::stoul(vertexData[0]) - 1;
			indices.push_back(currentVertexPointer);
			maths::vec2 currentTex = textures[std::stoi(vertexData[1]) - 1];
			textureArray[currentVertexPointer * 2] = currentTex.x;
			textureArray[currentVertexPointer * 2 + 1] = currentTex.y;
			maths::vec3 currentNorm = normals[std::stoi(vertexData[2]) - 1];
			normalsArray[  currentVertexPointer * 3  ] = currentNorm.x;
			normalsArray[currentVertexPointer * 3 + 1] = currentNorm.y;
			normalsArray[currentVertexPointer * 3 + 2] = currentNorm.z;
		}
	};

} }
