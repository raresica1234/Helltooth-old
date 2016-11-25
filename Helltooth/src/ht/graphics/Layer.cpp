#include "Layer.h"

namespace ht { namespace graphics { 

	Layer::Layer(unsigned int shader, Camera* camera)
		: shader(ShaderManager::Get()->getProgram(shader)), camera(camera){
		renderer = htnew MasterRenderer(shader, camera);

		this->shader->start();
		GLint texIDs[] = {
			0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31
		};
		this->shader->uniform1iv("textures", texIDs, 32);
	}

	Layer::~Layer() {
		del renderer;
		del camera;
	}

	void Layer::setMatrix(maths::mat4 &projectionMatrix) {
		this->projectionMatrix = projectionMatrix;
		shader->start();
		shader->setProjection("projectionMatrix", projectionMatrix);
		renderer->setProjectionMatrix(projectionMatrix);
		shader->stop();
	}

	void Layer::submit(Renderable* renderable, Entity3D &entity) {
		renderer->submit(renderable, entity);
	}
	void Layer::submit(Renderable* renderable, const std::vector<Entity3D> entityList) {
		renderer->submit(renderable, entityList);
	}

	void Layer::submit(const StaticEntity *entity) {
		renderer->submit(entity);
	}
	void Layer::submit(const DynamicEntity *entity) {
		renderer->submit(entity);
	}
	void Layer::render() {
		renderer->prepare();
		shader->start();
		renderer->render();
		shader->stop();
	}

	void Layer::update() {
		if(camera)
			camera->update();
		if (!shader->hasProjection())
			setMatrix(projectionMatrix);
	}

	void Layer::cleanUP() {
		renderer->cleanUP();
	}

	void Layer::forceCleanUP() {
		renderer->forceCleanUP();
	}

	void Layer::reloadTextures() {
		this->shader->start();
		GLint texIDs[] = {
			0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31
		};
		this->shader->uniform1iv("textures", texIDs, 32);
	}
} }