#include "Terrain.h"

#include "../rendering/model/Quad.h"

namespace ht { namespace graphics {

	static const char* shaderVert =
	#include "terrainShader.vert"
	;

	static const char* shaderFrag =
	#include "terrainShader.frag"
	;

	Terrain::Terrain(maths::vec2 location) 
		: StaticEntity(nullptr, vec3(location.x, 0.0f, location.y)) {
		unsigned int id = API::createShader(shaderVert, shaderFrag, false);
		program = ShaderManager::getProgram(id);
		RawModel* model = nullptr;
		
		GLfloat distance = TERRAIN_SIZE / VERTEX_COUNT;

		int terrainSize = VERTEX_COUNT * VERTEX_COUNT;

		GLfloat* positions = htnew GLfloat[terrainSize * 3];
		GLfloat* normals = htnew GLfloat[terrainSize * 3];
		GLuint* indices = htnew GLuint[6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)];
		GLfloat* textureCoords = htnew GLfloat[terrainSize * 2];

		int vertexPointer = 0;

		for (int y = 0; y < VERTEX_COUNT; y++)
			for (int x = 0; x < VERTEX_COUNT; x++) {
				positions[vertexPointer * 3] = (float)x * distance;
				positions[vertexPointer * 3 + 1] = 0;
				positions[vertexPointer * 3 + 2] = (float)y * distance;

				normals[vertexPointer * 3] = 0.0f;
				normals[vertexPointer * 3 + 1] = 1.0f;
				normals[vertexPointer * 3 + 2] = 0.0f;

				textureCoords[vertexPointer * 2] = (float)x / ((float)VERTEX_COUNT - 1);
				textureCoords[vertexPointer * 2 + 1] = (float)y / ((float)VERTEX_COUNT - 1);
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

		renderable = htnew Renderable();
		renderable->loadRawModel(model);
		renderable->addTexture(API::loadTextureFromFile("res/grass.jpg"));
		scale(1.0, 1.0, 1.0);
	}

	Terrain::~Terrain() {
	}

	void Terrain::prepare() const {
		renderable->prepare();
		program->start();
	}

	void Terrain::setModelMatrix() const {
		mat4 model = getModelMatrix();
		program->uniformMat4("modelMatrix", model);
		program->stop();
	}

	void Terrain::setProjection(mat4 projection) const {
		program->start();
		program->uniformMat4("projectionMatrix", projection);
	}

	void Terrain::setViewMatrix(const Camera *camera) const {
		program->uniformMat4("viewMatrix", camera == nullptr ? mat4::createIdentity() : camera->generateViewMatrix());
	}

	void Terrain::render() const {
		renderable->render();
		program->stop();
		renderable->end();
	}

	void Terrain::addBlendMap(Texture* texture) {
		renderable->addTexture(texture);
	}

	void Terrain::addTerrainTextures(Texture* textures, short count) {
		for (short i = 0; i < count < 31 ? count : 31; i++) 
			renderable->addTexture(&textures[i]);
	}

} }
