#include "DeferredRenderer.h"

namespace ht { namespace graphics {
	using namespace utils;
	using namespace maths;

	String DeferredRenderer::geometryPassVertex;
	String DeferredRenderer::geometryPassFragment;

	DeferredRenderer::DeferredRenderer(Camera* camera) 
		:Renderer(camera, ShaderManager::Get()->loadProgram(geometryPassVertex, geometryPassFragment, false)), w(WindowManager::Get()->getWindow(0)) {
		Window* w = WindowManager::Get()->getWindow(0);
		gbuffer = htnew GBuffer();
	}

	DeferredRenderer::~DeferredRenderer() {
		del gbuffer;
	}

	void DeferredRenderer::submit(const Entity* entity) {
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

	void DeferredRenderer::prepare() {
		program->start();
		if (!program->hasProjection())
			program->setProjection("projectionMatrix", projectionMatrix);
	}

	void DeferredRenderer::render() {
		gbuffer->bind;
		program->start();
		mat4 cameraMatrix = mat4();
		if (camera)
			cameraMatrix = camera->generateViewMatrix();
		program->uniformMat4("viewMatrix", cameraMatrix);
		if (!dynamicEntities.empty())
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

		if (!staticEntities.empty())
			for (unsigned int i = 0; i < staticEntities.size(); i++) {
				const StaticEntity* sEntity = staticEntities[i];
				sEntity->prepare();
				if (sEntity->hasOwnShader()) {
					sEntity->setProjection(projectionMatrix);
					sEntity->setViewMatrix(cameraMatrix);
					sEntity->render();
					sEntity->end();
				}
				else {
					program->uniformMat4("modelMatrix", sEntity->getModelMatrix());
				}
			}

		program->stop();
		gbuffer->unbind(w->getWidth(), w->getHeight());
	}

	void DeferredRenderer::cleanUP() {
		dynamicEntities.clear();
	}

	void DeferredRenderer::forceCleanUP() {
		staticEntities.clear();
	}
} }