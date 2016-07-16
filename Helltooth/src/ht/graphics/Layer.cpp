#include "Layer.h"

namespace ht { namespace graphics { 

	Layer::Layer(ShaderProgram* shader, Camera* camera)
		: shader(shader), camera(camera){
		renderer = new EntityRenderer3D(this->shader);
		renderer->setCamera(camera);
	}

	Layer::~Layer() {
		delete shader;
		delete renderer;
		delete camera;
	}

	void Layer::setMatrix(maths::mat4 &projectionMatrix) {
		this->projectionMatrix = projectionMatrix;
		shader->start();
		shader->uniformMat4("projectionMatrix", projectionMatrix);
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
	}

} }