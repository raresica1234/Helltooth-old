#include "BatchRenderer.h"

namespace ht { namespace graphics {

	BatchRenderer::BatchRenderer(const RawModel *object, const ShaderProgram *program)
		: changed(false), entityCount(0){
		this->object = object;
		this->program = program;
		entities = new EntityStack();
		renderable = new Renderable();
	}

	BatchRenderer::~BatchRenderer() {
		delete object;
		delete model;
		delete renderable;
		delete entities;
		delete program;
	}

	void BatchRenderer::addEntity(const Entity3D &entity) {
		unsigned int id = entities->addEntity(entity);
		entitiesID.push_back(id);
		entityCount++;
	}

	void BatchRenderer::removeEntity(const unsigned int id) {
		entities->removeEntity(id);

		for (unsigned int i = 0; i < entitiesID.size(); i++)
		{
			if (entitiesID[i] == id)
			{
				entitiesID.erase(entitiesID.begin() + i);
				entityCount--;
				break;
			}
		}
	}

	Entity3D BatchRenderer::getEntity(const unsigned int &id) {
		return entities->getEntity(id);
	}

	void BatchRenderer::init() {
		if (changed) {
			if(model != nullptr)
				delete model;

			std::vector<vec3> positions;
			const GLfloat* objPositions;
			objPositions = object->getPositions();
			for (unsigned int i = 0; i < ((object->getPositionSize() / sizeof(GLfloat)) / 3); i++) {
				positions.push_back(vec3(objPositions[i * 3], objPositions[i * 3 + 1], objPositions[i * 3 + 2]));
			}

			std::vector<vec3> finalPositions;

			for (unsigned int entityID : entitiesID) {
				Entity3D entity = getEntity(entityID);

				for (vec3 vector : positions) {
					finalPositions.push_back(entity.generateModelMatrix() * vector);
				}

			}

			GLfloat* modelPositions = new GLfloat[finalPositions.size() * 3];

			unsigned int i = 0;
			for (vec3 vector : finalPositions) {
				modelPositions[i++] = vector.x;
				modelPositions[i++] = vector.y;
				modelPositions[i++] = vector.z;
			}

			model = new RawModel(modelPositions, finalPositions.size() * 3 * sizeof(GLfloat));

			delete[] modelPositions;

			const GLuint* objIndices;
			objIndices = object->getIndices();

			std::vector<GLuint> indices;
			for (unsigned int current = 0; current <= entityCount; current++) {
				for (unsigned int j = 0; j < object->getIndexSize() / sizeof(GLuint); j++) {
					indices.push_back(objIndices[j] * (current + 1));
				}
			}

			GLuint *finalIndices = new GLuint[indices.size()];

			for (int i = 0; i < indices.size(); i++) {
				finalIndices[i] = indices[i];
			}

			model->storeData(finalIndices, indices.size() * sizeof(GLuint));

			delete[] finalIndices;

			delete renderable;

			renderable = new Renderable();
			renderable->loadRawModel(model);

			changed = false;
		}
	}

	void BatchRenderer::render() const {
		renderable->render();
	}


} }