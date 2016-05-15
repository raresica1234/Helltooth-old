#include "BatchRenderer.h"

#include "../../../ht/utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	BatchRenderer::BatchRenderer(Renderable *object, ShaderProgram *program)
	{
		this->object = object;
		this->program = program;

		//Handle the positions -> convert them into vec3s
		const GLfloat *positions = object->getPositions();
		objectPositionCount = object->getVertexSize() / 3;
		objectPositions = new vec3[objectPositionCount];
		for (GLsizei i = 0; i < objectPositionCount; i++) {
			objectPositions[i] = vec3(positions[i * 3 + 0], positions[i * 3 + 1], positions[i * 3 + 2]);
		}

		//Handle indices
		objectIndices = object->getIndices();
	}


	BatchRenderer::~BatchRenderer()
	{
		renderable->unbindVAO();
		program->stop();
	}

	void BatchRenderer::addEntity(Entity3D entity)
	{
		entities.push_back(entity);
		changed = true;
		entityCount++;
	}

	void BatchRenderer::deleteEntity(Entity3D entity)
	{
		for (unsigned int i = 0; i < entities.size(); i++)
		{
			if (entities[i] == entity)
			{
				entities.erase(entities.begin() + i);
				break;
			}
		}
		changed = true;
		entityCount--;
	}

	void BatchRenderer::prepare()
	{
		if (changed) reInit();

		program->start();
		renderable->bindVAO();
	}

	void BatchRenderer::reInit()
	{
		delete renderable;
		renderable = new Renderable();

		//CALCULATE THE VBO OF ALL OF THE ENTITIES USING THE MATRICES
		positions = new GLfloat[entityCount * objectPositionCount * 3];
		indices = new GLint[entityCount * object->getIndicesCount()];
		int currentEntity = 0;
		positionSize = 0;
		indicesSize = 0;
		for (Entity3D entity : entities)
		{
			//Calculate the vbo of positions
			currentEntity++;
			mat4 model = entity.generateModelMatrix();
			for (GLsizei i = 0; i < objectPositionCount; i++)
			{
				vec3 current = objectPositions[i];
				current = model * current;
				positions[currentEntity * objectPositionCount + i + 0] = current.x;
				positions[currentEntity * objectPositionCount + i + 1] = current.y;
				positions[currentEntity * objectPositionCount + i + 2] = current.z;
				positionSize += 3;
			}
			//Calculate the indices
			for (GLsizei i = 0; i < object->getIndicesCount(); i++)
			{
				indices[currentEntity * object->getIndicesCount() + i] = currentEntity * objectIndices[i];
				indicesSize++;
			}
		}

		renderable->bindVAO();
		renderable->addBufferData(positions, positionSize * sizeof(GLfloat), RENDERABLE_COORDS);
		renderable->addBufferData(indices, indicesSize * sizeof(GLint));

		changed = false;
	}

	void BatchRenderer::render() const
	{
		mat4 model;
		renderable->flush();
	}

} }
