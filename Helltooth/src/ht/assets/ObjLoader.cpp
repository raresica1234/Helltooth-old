#include "ObjLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "TOL/tiny_obj_loader.h"

namespace ht { namespace assets {

	using namespace utils;
	using namespace maths;
	using namespace graphics;


	RawModel* ObjLoader::LoadObjFile(String& path) {
		std::vector<vec3> ver;
		std::vector<vec3> nor;
		std::vector<vec2> uvs;

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string err;
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str());

		if (!err.empty()) {
			HT_WARN("[ObjLoader] %s", err.c_str());
		}

		if (!ret) {
			HT_FATAL("[ObjLoader] Model can't be loaded!");
			return htnew RawModel(nullptr, 0);
		}

		for (size_t s = 0; s < shapes.size(); s++) {

			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];

				for (size_t v = 0; v < fv; v++) {
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					vec3 position(attrib.vertices[3 * idx.vertex_index + 0], attrib.vertices[3 * idx.vertex_index + 1],
						attrib.vertices[3 * idx.vertex_index + 2]);
					vec3 normal(attrib.normals[3 * idx.normal_index + 0], attrib.normals[3 * idx.normal_index + 1],
						attrib.normals[3 * idx.normal_index + 2]);
					vec2 texture(attrib.texcoords[2 * idx.texcoord_index + 0], attrib.texcoords[2 * idx.texcoord_index + 1]);

					ver.push_back(position);
					nor.push_back(normal);
					uvs.push_back(texture);
				}
				index_offset += fv;
			}
		}


		std::vector<unsigned int> indices;
		
		std::vector<vec3> vertices;
		std::vector<vec3> normals;
		std::vector<vec2> txC;
		
		for (unsigned int i = 0; i < ver.size(); i++) {
			unsigned int index;
			if (!find(ver[i], nor[i], uvs[i], &index, vertices, normals, txC)) {
				vertices.push_back(ver[i]);
				normals.push_back(nor[i]);
				txC.push_back(uvs[i]);
				index = i;
			}
			indices.push_back(index);
		}


		float *verticesArray = htnew float[vertices.size() * 3];
		float *normalsArray = htnew float[normals.size() * 3];
		float *textureArray = htnew float[txC.size() * 2];
		unsigned int* indicesArray = htnew unsigned int[indices.size()];

		memcpy(verticesArray, &ver[0], vertices.size() * 3 * sizeof(GLuint));
		memcpy(normalsArray, &nor[0], normals.size() * 3 * sizeof(GLuint));
		memcpy(textureArray, &uvs[0], txC.size() * 2 * sizeof(GLuint));
		
		RawModel* model = htnew RawModel(verticesArray, vertices.size() * 3 * sizeof(GLfloat));
		model->storeData(indicesArray, indices.size() * sizeof(GLuint));
		model->storeData(RAWMODEL_NORMALS, normalsArray, vertices.size() * 3 * sizeof(GLfloat));
		model->storeData(RAWMODEL_TEXTURE_COORDS, textureArray, vertices.size() * 2 * sizeof(GLfloat));
		HT_INFO("[ObjLoader] Model \"%s\" loaded", path);
		return model;
	}

} }