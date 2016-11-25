#include "MasterRenderer.h"

namespace ht { namespace graphics {
	using namespace maths;

	MasterRenderer::MasterRenderer(unsigned int shaderProgram, Camera* camera = nullptr)
		: camera(camera) {
		eRenderer = htnew EntityRenderer3D(shaderProgram);
		this->program = ShaderManager::Get()->getProgram(shaderProgram);
		if(camera)
			eRenderer->setCamera(camera);
	}

	MasterRenderer::~MasterRenderer() {
		del eRenderer;
	}

	void MasterRenderer::submit(const DynamicEntity* dynamicEntity) {
		dynamicEntities.push_back(dynamicEntity);
	}

	void MasterRenderer::submit(const StaticEntity* staticEntity) {
		staticEntity->setProjection(projectionMatrix);
		staticEntity->setModelMatrix();
		staticEntities.push_back(staticEntity);
	}

	void MasterRenderer::submit(const Renderable* renderable, const Entity3D &entity) {
		eRenderer->submit(renderable, entity);
	}

	void MasterRenderer::submit(const Renderable* renderable, const std::vector<Entity3D> entities) {
		eRenderer->submit(renderable, entities);
	}

	void MasterRenderer::prepare() {
		eRenderer->submit(dynamicEntities);
	}

	void MasterRenderer::render() {
		eRenderer->render();
		for (unsigned int i = 0; i < staticEntities.size(); i++ ) {
			const StaticEntity* sEntity = staticEntities[i];
			sEntity->prepare();
			if (sEntity->hasOwnShader()) {
				if(camera)
					sEntity->setViewMatrix(camera);
				sEntity->render();
			}
			else {
				program->start();
				if (camera)
					program->uniformMat4("viewMatrix", camera->generateViewMatrix());
				program->setProjection("projectionMatrix", projectionMatrix);
				program->uniformMat4("modelMatrix", sEntity->getModelMatrix());
				sEntity->render();
				program->stop();
				sEntity->end();
			}
		}
	}

	void MasterRenderer::cleanUP() {
		eRenderer->cleanUP();
		dynamicEntities.clear();
	}

	void MasterRenderer::forceCleanUP() {
		staticEntities.clear();
	}

	void MasterRenderer::setProjectionMatrix(mat4 projectionMatrix) {
		this->projectionMatrix = projectionMatrix;
	}

} }