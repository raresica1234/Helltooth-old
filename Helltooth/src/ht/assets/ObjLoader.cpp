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
		std::vector<unsigned int> indices;

		float* verticesArray = nullptr;
		float* normalsArray = nullptr;
		float* texturesArray = nullptr;
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

		verticesArray = htnew float[vertices.size() * 3];
		texturesArray = htnew float[vertices.size() * 2];
		normalsArray = htnew float[vertices.size() * 3];
		indicesArray = htnew unsigned int[indices.size()];

		convertDataToArrays(vertices, textures, normals, verticesArray, texturesArray, normalsArray);

		memcpy(indicesArray, &indices[0], indices.size() * sizeof(unsigned int));
		fclose(file);

		RawModel* model = htnew RawModel(verticesArray, vertices.size() * 3 * sizeof(GLfloat));
		model->storeData(indicesArray, indices.size() * sizeof(GLuint));
		model->storeData(RAWMODEL_NORMALS, normalsArray, vertices.size() * 3 * sizeof(GLfloat));
		model->storeData(RAWMODEL_TEXTURE_COORDS, texturesArray, vertices.size() * 2 * sizeof(GLfloat));
		HT_INFO("[ObjLoader] Model \"%s\" loaded", path);
		return model;
	}

} }