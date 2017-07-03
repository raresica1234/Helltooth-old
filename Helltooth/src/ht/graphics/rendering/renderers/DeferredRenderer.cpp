#include "DeferredRenderer.h"

namespace ht { namespace graphics {
	using namespace utils;
	using namespace maths;

	String DeferredRenderer::geometryPassVertex =
		#include "shaders/DeferredRendererGeometryPass.vert"
		;

	String DeferredRenderer::geometryPassFragment = 
		#include "shaders/DeferredRendererGeometryPass.frag"
		;

	String DeferredRenderer::basicProgramVert =
		#include "shaders/DeferredRendererBasic.vert"
		;

	String DeferredRenderer::directionalLightFrag =
		#include "shaders/DeferredRendererDirectionalLight.frag"
		;

	String DeferredRenderer::pointLightFrag =
		#include "shaders/DeferredRendererPointLight.frag"
		;

	String DeferredRenderer::spotLightFrag =
		#include "shaders/DeferredRendererSpotLight.frag"
		;

	DeferredRenderer::DeferredRenderer(Camera* camera) 
		: Renderer(camera, ShaderManager::Get()->loadProgram(geometryPassVertex, geometryPassFragment, false)), w(WindowManager::Get()->getWindow(0)) {
		Window* w = WindowManager::Get()->getWindow(0);
		gbuffer = htnew GBuffer();

		uint32 dirID = ShaderManager::Get()->loadProgram(basicProgramVert, directionalLightFrag, false);
		uint32 pointID = ShaderManager::Get()->loadProgram(basicProgramVert, pointLightFrag, false);
		uint32 spotID = ShaderManager::Get()->loadProgram(basicProgramVert, spotLightFrag, false);
		directional = ShaderManager::Get()->getProgram(dirID);
		point = ShaderManager::Get()->getProgram(pointID);
		spot = ShaderManager::Get()->getProgram(spotID);

		Quad* quadModel = htnew Quad();
		quad = htnew Renderable();
		quad->loadRawModel(quadModel->getModel());

		del quadModel;
		this->reloadTextures();
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
			HT_FATAL("[DeferredRenderer] Entity type not supported!");
		}
	}

	void DeferredRenderer::prepare() {
		//lololololo
	}

	void DeferredRenderer::render() {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		gbuffer->bind();
		program->start();
		mat4 cameraMatrix = mat4();
		if (camera)
			cameraMatrix = camera->generateViewMatrix();
		program->uniformMat4("viewMatrix", cameraMatrix);

		mat4 pv = projectionMatrix * cameraMatrix;

		program->setProjection("projectionViewMatrix", pv);

		if (!dynamicEntities.empty()) {
			for (auto& entry : dynamicEntities) {
				entry.first->prepare();
				for (Entity& entity : entry.second) {
					program->uniformMat4("modelMatrix", entity.getModelMatrix());
					entry.first->render();
				}
			}
			
		}

		if (!staticEntities.empty())
			for (uint32 i = 0; i < staticEntities.size(); i++) {
				const StaticEntity* sEntity = staticEntities[i];
				sEntity->prepare();
				if (sEntity->hasOwnShader()) {
					sEntity->setProjection(projectionMatrix);
					sEntity->setViewMatrix(cameraMatrix);
					sEntity->render();
				}
				else {
					program->uniformMat4("modelMatrix", sEntity->getModelMatrix());
				}
			}
		
		gbuffer->unbind(w->getWidth(), w->getHeight());
		quad->prepare();
		
		gbuffer->bindTextures();
		
		for (uint32 i = 0; i < stack->size(); i++) {
			if (i == 1) {
				glDepthFunc(GL_EQUAL);
				glEnable(GL_BLEND);
				glBlendFunc(GL_ONE, GL_ONE);
			}
			Light* light = stack->operator[](i);
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
			quad->render();
		}
		
		glDisable(GL_BLEND);
		glDepthFunc(GL_LESS);
		glDisable(GL_CULL_FACE);
	}

	void DeferredRenderer::cleanUP() {
		dynamicEntities.clear();
	}

	void DeferredRenderer::forceCleanUP() {
		staticEntities.clear();
	}

	void DeferredRenderer::reloadTextures() {
		Renderer::reloadTextures();
		int32 texIDs[] = {
			0,  1,  2
		};

		directional->start();
		directional->uniform1iv("textures", texIDs, 3);

		point->start();
		point->uniform1iv("textures", texIDs, 3);

		spot->start();
		spot->uniform1iv("textures", texIDs, 3);
	}
} }