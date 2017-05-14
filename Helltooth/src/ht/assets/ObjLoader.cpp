#include "ObjLoader.h"

namespace ht { namespace assets {
	using namespace utils;
	using namespace maths;
	using namespace graphics;


	RawModel* ObjLoader::LoadObjFile(String& path) {
		FILE* file = fopen(path.c_str(), "rt");
		if (file == nullptr) {
			HT_FATAL("[ObjLoader] file \"%s\" could not be opened!", path);
			return nullptr;
		}

		fseek(file, 0, SEEK_SET);

		std::vector<Vertex> vertices;
		std::vector<vec2> textures;
		std::vector<vec3> normals;
		std::vector<uint32> indices;

		f32* verticesArray = nullptr;
		f32* normalsArray = nullptr;
		f32* texturesArray = nullptr;
		uint32* indicesArray = nullptr;

		while (!feof(file)) {
			sbyte buffer[256] = { '\0' };
			readLine(file, buffer);
			sbyte* textbegins = skipWhitespaces(buffer);
			std::string currentLine(textbegins);

			if (textbegins == "#") continue;

			if (currentLine.substr(0, 2) == "v ") {
				vec3 vertex;
				sscanf(textbegins, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
				Vertex newVertex = Vertex(vertices.size(), vertex);
				vertices.push_back(newVertex);
			}
			else if (currentLine.substr(0, 3) == "vt ") {
				vec2 texture;
				sscanf(textbegins, "vt %f %f", &texture.x, &texture.y);
				textures.push_back(texture);
			}
			else if (currentLine.substr(0, 3) == "vn ") {
				vec3 normal;
				sscanf(textbegins, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
				normals.push_back(normal);
			}
			else if (currentLine.substr(0, 2) == "f ") {
				vec3 vertex1, vertex2, vertex3;

				sscanf(textbegins, "f %f/%f/%f %f/%f/%f %f/%f/%f", &vertex1.x, &vertex1.y, &vertex1.z,
					&vertex2.x, &vertex2.y, &vertex2.z, &vertex3.x, &vertex3.y, &vertex3.z);

				processVertex(vertex1, vertices, indices);
				processVertex(vertex2, vertices, indices);
				processVertex(vertex3, vertices, indices);
			}
		}
		removeUnusedVertices(vertices);

		verticesArray = htnew f32[vertices.size() * 3];
		texturesArray = htnew f32[vertices.size() * 2];
		normalsArray = htnew f32[vertices.size() * 3];
		indicesArray = htnew uint32[indices.size()];

		convertDataToArrays(vertices, textures, normals, verticesArray, texturesArray, normalsArray);

		memcpy(indicesArray, &indices[0], indices.size() * sizeof(uint32));
		fclose(file);

		RawModel* model = htnew RawModel(verticesArray, vertices.size() * 3 * sizeof(f32));
		model->storeData(indicesArray, indices.size() * sizeof(uint32));
		model->storeData(RAWMODEL_NORMALS, normalsArray, vertices.size() * 3 * sizeof(f32));
		model->storeData(RAWMODEL_TEXTURE_COORDS, texturesArray, vertices.size() * 2 * sizeof(f32));
		HT_INFO("[ObjLoader] Model \"%s\" loaded", path);
		return model;
	}

	void ObjLoader::processVertex(maths::vec3 &vertex, std::vector<Vertex> &vertices, std::vector<uint32> &indices) {
		uint32 index = (uint32)vertex.x - 1;
		Vertex& currentVertex = vertices[index];
		uint32 textureIndex = (uint32)vertex.y - 1;
		uint32 normalIndex = (uint32)vertex.z - 1;
		if (!currentVertex.isSet()) {
			currentVertex.textureIndex = textureIndex;
			currentVertex.normalIndex = normalIndex;
			indices.push_back(index);
		}
		else {
			dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
		}
	}

	void ObjLoader::dealWithAlreadyProcessedVertex(Vertex &previousVertex, uint32 &newTextureIndex,
		uint32 &newNormalIndex, std::vector<uint32> &indices, std::vector<Vertex> &vertices) {
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

	void ObjLoader::convertDataToArrays(std::vector<Vertex> &vertices, std::vector<maths::vec2> &textures,
		std::vector<maths::vec3> &normals, f32 *verticesArray, f32 *texturesArray, f32 *normalsArray) {
		for (uint32 i = 0; i < vertices.size(); i++) {
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

	void ObjLoader::readLine(FILE* file, char* buffer, uint32 bufferLen) {
		sbyte c;
		uint32 bufferIndex = 0;
		c = fgetc(file);
		while (!feof(file) && c != '\n' && bufferIndex < bufferLen) {
			buffer[bufferIndex++] = c;
			c = fgetc(file);
		}
		if (bufferIndex < bufferLen)
			buffer[bufferIndex] = '\0';
	}

	sbyte* ObjLoader::skipWhitespaces(sbyte* text) {
		sbyte* ptr = text;
		while (*text == ' ' || *text == '\t' || *text == '\v')
			ptr++;
		return ptr;
	}

} }