#include "Layer.h"

namespace ht { namespace graphics { 

	Layer::Layer(unsigned int shader, Camera* camera)
		: shader(ShaderManager::getProgram(shader)), camera(camera){
		renderer = new EntityRenderer3D(shader);
		renderer->setCamera(camera);
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
		delete renderer;
		delete camera;
	}

	void Layer::setMatrix(maths::mat4 &projectionMatrix) {
		this->projectionMatrix = projectionMatrix;
		shader->start();
		shader->setProjection("projectionMatrix", projectionMatrix);
		shader->stop();
	}

	void Layer::submit(Renderable* renderable, Entity3D &entity) {
		renderer->submit(renderable, entity);
	}
	void Layer::submit(Renderable* renderable, const std::vector<Entity3D> entityList) {
		renderer->submit(renderable, entityList);
	}

	void Layer::render() {
		shader->start();
		renderer->render();
		shader->stop();
		renderer->cleanUP();
	}

	void Layer::update() {
		camera->update();
		if (!shader->hasProjection())
			setMatrix(projectionMatrix);
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