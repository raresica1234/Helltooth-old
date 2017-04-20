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

	String DeferredRenderer::basicProgramFrag =
		#include "shaders/DeferredRendererBasic.frag"
		;

	DeferredRenderer::DeferredRenderer(Camera* camera) 
		: Renderer(camera, ShaderManager::Get()->loadProgram(geometryPassVertex, geometryPassFragment, false)), w(WindowManager::Get()->getWindow(0)) {
		Window* w = WindowManager::Get()->getWindow(0);
		gbuffer = htnew GBuffer();

		unsigned int lightingPassID = ShaderManager::Get()->loadProgram(basicProgramVert, basicProgramFrag, false);

		lightingPass = ShaderManager::Get()->getProgram(lightingPassID);

		Quad* quadModel = htnew Quad();
		quad = htnew Renderable();
		quad->loadRawModel(quadModel->getModel());
		del quadModel;
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
		program->start();
		if (!program->hasProjection())
			program->setProjection("projectionMatrix", projectionMatrix);
	}

	void DeferredRenderer::render() {
		gbuffer->bind();
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

		//lightingPass->start();
		//quad->prepare();
		//for (int i = 0; i < 4; i++) {
		//	glActiveTexture(GL_TEXTURE0 + i);
		//	glBindTexture(GL_TEXTURE_2D, (*gbuffer)[i]->getID());
		//}
		//
		//quad->render();
		//lightingPass->stop();
		//quad->end();
	}

	void DeferredRenderer::cleanUP() {
		dynamicEntities.clear();
	}

	void DeferredRenderer::forceCleanUP() {
		staticEntities.clear();
	}

	void DeferredRenderer::reloadTextures() {
		Renderer::reloadTextures();
		GLint texIDs[] = {
			0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31
		};
		lightingPass->start();
		lightingPass->uniform1iv("textures", texIDs, 32);
	}
} }