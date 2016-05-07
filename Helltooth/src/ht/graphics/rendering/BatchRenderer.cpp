#include "BatchRenderer.h"

namespace ht { namespace graphics {

	BatchRenderer::BatchRenderer(Renderable *renderable, ShaderProgram *program) {
		this->program = program;
	}


	BatchRenderer::~BatchRenderer() {
		renderable->unbindVAO();
		program->stop();
		
		delete program;
		delete renderable;
	}

	void BatchRenderer::addEntity(Entity3D entity) {
		entities.push_back(entity);
	}

	void BatchRenderer::deleteEntity(Entity3D entity) {
		
	}

	void BatchRenderer::prepare() {
		program->start();
		renderable->bindVAO;
	}

	void BatchRenderer::render() const {
		for(Entity3D entity:entities){
			mat4 model = entity.generateModelMatrix();
			program->uniformMat4("modelMatrix", model);
			renderable->flush();
		}

	}


} }
