#include "BatchRenderer.h"

namespace ht { namespace graphics {

	BatchRenderer::BatchRenderer(Renderable *renderable, ShaderProgram *program) {
		this->renderable = renderable;
		this->program = program;
	}


	BatchRenderer::~BatchRenderer() {
		renderable->unbindVAO();
		program->stop();
	}

	void BatchRenderer::addEntity(Entity3D entity) {
		entities.push_back(entity);
	}

	void BatchRenderer::deleteEntity(Entity3D entity) {
		for (unsigned int i = 0; i < entities.size(); i++) {
			if (entities[i] == entity) {
				entities.erase(entities.begin() + i);
				break;
			}
		}
	}

	void BatchRenderer::prepare() {
		program->start();
		renderable->bindVAO();
	}

	void BatchRenderer::render() const {
		mat4 model;
		for(Entity3D entity:entities){
			model = entity.generateModelMatrix();
			program->uniformMat4("modelMatrix", model);
			renderable->flush();
		}

	}


} }
