#include "SimpleRenderer.h"

namespace ht { namespace graphics {
	using namespace maths;

	SimpleRenderer::SimpleRenderer(unsigned int programID, Camera* camera)
		: Renderer(camera, ShaderManager::Get()->getProgram(programID)) { }

	SimpleRenderer::SimpleRenderer(ShaderProgram* program, Camera* camera)
		: Renderer(camera, program) {}

	SimpleRenderer::~SimpleRenderer() {}

	void SimpleRenderer::submit(const Entity* entity) {
		if (entity->getType() == DYNAMIC_ENTITY) {
			DynamicEntity* dynamicEntity = (DynamicEntity*)entity;
			dynamicEntities[dynamicEntity->getRenderable()].push_back(*entity);
			return;
		}
		else if (entity->getType() == STATIC_ENTITY) {
			StaticEntity* staticEntity = (StaticEntity*)entity;
			staticEntity->setProjection(projectionMatrix);
			staticEntity->setModelMatrix();
			staticEntities.push_back(staticEntity);
			return;
		}
		else {
			HT_FATAL("[MasterRenderer] Entity type not supported!");
		}
	}

	void SimpleRenderer::prepare() {
		if (camera)
			program->uniformMat4("viewMatrix", camera->generateViewMatrix());
	}

	void SimpleRenderer::render() {
		if (!program->hasProjection())
			program->setProjection("projectionMatrix", projectionMatrix);
		mat4 cameraMatrix;
		if (camera) {
			cameraMatrix = camera->generateViewMatrix();
		}
		else {
			cameraMatrix = mat4::createIdentity();
		}
		program->uniformMat4("viewMatrix", cameraMatrix);
		if(!dynamicEntities.empty())
			for (auto& entry : dynamicEntities) {
				entry.first->prepare();
				for (Entity& entity : entry.second) {
					program->uniformMat4("modelMatrix", entity.getModelMatrix());
					if (!program->hasProjection())
						program->setProjection("projectionMatrix", projectionMatrix);
					entry.first->render();
				}
				entry.first->end();
			}

		if(!staticEntities.empty())
			for (unsigned int i = 0; i < staticEntities.size(); i++ ) {
				const StaticEntity* sEntity = staticEntities[i];
				sEntity->prepare();
				if (sEntity->hasOwnShader()) {
					sEntity->setProjection(projectionMatrix);
					sEntity->setViewMatrix(cameraMatrix);
					sEntity->render();
					sEntity->end();
				}
				else {
					program->uniformMat4("viewMatrix", cameraMatrix);
					program->uniformMat4("modelMatrix", sEntity->getModelMatrix());
				}
			}
	}

	void SimpleRenderer::cleanUP() {
		dynamicEntities.clear();
	}

	void SimpleRenderer::forceCleanUP() {
		staticEntities.clear();
	}

} }