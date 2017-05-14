#include "ForwardRenderer.h"

namespace ht { namespace graphics {
	using namespace maths;
	using namespace utils;

	String ForwardRenderer::vertexShader = 
		#include "shaders/ForwardRendererBasic.vert"
		;

	String ForwardRenderer::fragmentDirectional =
		#include "shaders/ForwardRendererDirectionalLight.frag"
		;

	String ForwardRenderer::fragmentPoint = 
		#include "shaders/ForwardRendererPointLight.frag"
		;

	String ForwardRenderer::fragmentSpot =
		#include "shaders/ForwardRendererSpotLight.frag"
		;

	ForwardRenderer::ForwardRenderer(Camera* camera)
		: Renderer(camera, nullptr) {
		uint32 directionalID = ShaderManager::Get()->loadProgram(vertexShader, fragmentDirectional, false);
		uint32 pointID = ShaderManager::Get()->loadProgram(vertexShader, fragmentPoint, false);
		uint32 spotID = ShaderManager::Get()->loadProgram(vertexShader, fragmentSpot, false);

		directional = ShaderManager::Get()->getProgram(directionalID);
		point = ShaderManager::Get()->getProgram(pointID);
		spot = ShaderManager::Get()->getProgram(spotID);
	}

	ForwardRenderer::~ForwardRenderer() {}

	void ForwardRenderer::submit(const Entity* entity) {
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
			HT_FATAL("[ForwardRenderer] Entity type not supported!");
		}
	}

	void ForwardRenderer::prepare() {
		//lololololololo
	}

	void ForwardRenderer::render() {
		mat4 cameraMatrix = mat4();
		if (camera)
			cameraMatrix = camera->generateViewMatrix();

		for (uint32 i = 0; i < stack->size(); i++) {
			if (i == 1) {
				glDepthFunc(GL_EQUAL);
				glEnable(GL_BLEND);
				glBlendFunc(GL_ONE, GL_ONE);
			}
			Light* light = (*stack)[i];

			ShaderProgram* curr = nullptr;

			switch (light->getLightType()) {
			case LIGHT_TYPE_DIRECTIONAL:
				curr = directional;
				break;
			case LIGHT_TYPE_POINT:
				curr = point;
				break;
			case LIGHT_TYPE_SPOT:
				curr = spot;
				break;
			}
			curr->start();
			light->uniform("light", curr);

			curr->uniformMat4("viewMatrix", cameraMatrix);

			if (!curr->hasProjection())
				curr->setProjection("projectionMatrix", projectionMatrix);

			if (!dynamicEntities.empty())
				for (auto& entry : dynamicEntities) {
					entry.first->prepare();
					for (Entity& entity : entry.second) {
						curr->uniformMat4("modelMatrix", entity.getModelMatrix());
						entry.first->render();
					}
					entry.first->end();
				}
			if(!staticEntities.empty())
				for (uint32 i = 0; i < staticEntities.size(); i++) {
					const StaticEntity* sEntity = staticEntities[i];
					sEntity->prepare();
					if (!sEntity->hasOwnShader()) {
						curr->uniformMat4("modelMatrix", sEntity->getModelMatrix());
						sEntity->render();
						sEntity->end();
					}
					
				}
		}

		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);

		if (!staticEntities.empty())
			for (uint32 i = 0; i < staticEntities.size(); i++) {
				const StaticEntity* sEntity = staticEntities[i];
				sEntity->prepare();
				if (sEntity->hasOwnShader()) {
					sEntity->setProjection(projectionMatrix);
					sEntity->setViewMatrix(cameraMatrix);
					sEntity->render();
					sEntity->end();
				}
			}
	}

	void ForwardRenderer::reloadTextures() {
		int32 texIDs[] = {
			0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31
		};

		directional->start();
		directional->uniform1iv("textures", texIDs, 32);

		point->start();
		point->uniform1iv("textures", texIDs, 32);

		spot->start();
		spot->uniform1iv("textures", texIDs, 32);
	}

	void ForwardRenderer::cleanUP() {
		dynamicEntities.clear();
	}

	void ForwardRenderer::forceCleanUP() {
		staticEntities.clear();
	}
} }