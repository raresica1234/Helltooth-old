#include "World.h"

namespace ht { namespace graphics {
	using namespace maths;

	World::World(int size, vec4 terrainCounts)
		: StaticEntity(nullptr) {
		hasShader = true;
		for (float x = terrainCounts.z; x <= terrainCounts.x; x+=1.0f) 
			for (float y = terrainCounts.w; y <= terrainCounts.y; y+= 1.0f) {
				Renderable* current = generateTerrain();
				chunks.push_back(Chunk(vec2(x, y), current));
			}
		std::string vertex = shader.generateVertex(), fragment = shader.generateFragment();
		
		const char *vertexC = vertex.c_str(), *fragmentC = fragment.c_str();

		unsigned int id = API::createShader(vertexC, fragmentC, false);
		program = ShaderManager::Get()->getProgram(id);
	}

	World::~World() {
		for (Chunk chunk : chunks) {
			del chunk.chunk;
		}
	}


	Renderable* World::generateTerrain() {
		RawModel* model = nullptr;

		GLfloat distance = (float)TERRAIN_SIZE / ((float)VERTEX_COUNT - 1);

		int terrainSize = VERTEX_COUNT * VERTEX_COUNT;

		GLfloat* positions = htnew GLfloat[terrainSize * 3];
		GLfloat* normals = htnew GLfloat[terrainSize * 3];
		GLuint* indices = htnew GLuint[6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)];
		GLfloat* textureCoords = htnew GLfloat[terrainSize * 2];

		int vertexPointer = 0;

		for (float y = 0; y < VERTEX_COUNT; y++)
			for (float x = 0; x < VERTEX_COUNT; x++) {
				positions[vertexPointer * 3] = x * distance;
				positions[vertexPointer * 3 + 1] = 0;
				positions[vertexPointer * 3 + 2] = y * distance;

				normals[vertexPointer * 3] = 0.0f;
				normals[vertexPointer * 3 + 1] = 1.0f;
				normals[vertexPointer * 3 + 2] = 0.0f;

				textureCoords[vertexPointer * 2] = x / ((float)VERTEX_COUNT - 1);
				textureCoords[vertexPointer * 2 + 1] = y / ((float)VERTEX_COUNT - 1);
				vertexPointer++;
			}

		int pointer = 0;
		for (unsigned int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
			for (unsigned int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
				unsigned int topLeft = (gz*VERTEX_COUNT) + gx;
				unsigned int topRight = topLeft + 1;
				unsigned int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
				unsigned int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topRight;
				indices[pointer++] = topRight;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomRight;
			}
		}
		model = htnew RawModel(positions, terrainSize * 3 * sizeof(GLfloat));
		model->storeData(indices, 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1) * sizeof(GLuint));
		model->storeData(RAWMODEL_NORMALS, normals, terrainSize * 3 * sizeof(GLfloat));
		model->storeData(RAWMODEL_TEXTURE_COORDS, textureCoords, terrainSize * 2 * sizeof(GLfloat));

		Renderable* renderable = htnew Renderable();
		renderable->loadRawModel(model);
		return renderable;
	}
} } 