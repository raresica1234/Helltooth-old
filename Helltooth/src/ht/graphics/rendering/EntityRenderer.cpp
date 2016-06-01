#include "EntityRenderer.h"

namespace ht { namespace graphics {

	EntityRenderer::EntityRenderer(ShaderProgram* program)
		: program(program) {

	}

	EntityRenderer::~EntityRenderer() {
		delete program;
	}


	void EntityRenderer::pushEntity(Renderable* renderable, const Entity3D &entity) {
		entities[renderable].push_back(entity);
	}

	void EntityRenderer::pushEntityList(Renderable* renderable, const std::vector<Entity3D>entities) {
		this->entities[renderable] = entities;
	}

	void EntityRenderer::render() {
		program->start();
		program->uniformMat4("viewMatrix", camera->generateViewMatrix());
		for (auto& entry : entities) {
			entry.first->prepare();
			for (Entity3D entity : entry.second) {
				program->uniformMat4("modelMatrix", entity.generateModelMatrix());
				entry.first->render();
			}
			entry.first->end();
		}
		program->stop();
	}

	void EntityRenderer::cleanUP() {
		entities.clear();
	}

} }