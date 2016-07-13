#include "EntityRenderer3D.h"

namespace ht { namespace graphics {

	EntityRenderer3D::EntityRenderer3D(ShaderProgram* program)
		: program(program) {

	}

	EntityRenderer3D::~EntityRenderer3D() {
		delete program;
	}


	void EntityRenderer3D::submit(const Renderable* renderable, const Entity3D &entity) {
		entities[renderable].push_back(entity);
	}

	void EntityRenderer3D::submitList(const Renderable* renderable, const std::vector<Entity3D>entities) {
		this->entities[renderable] = entities;
	}

	void EntityRenderer3D::render() {
		program->start();
		program->uniformMat4("viewMatrix", camera->generateViewMatrix());
		for (auto& entry : entities) {
			entry.first->prepare();
			for (Entity3D entity : entry.second) {
				program->uniformMat4("modelMatrix", entity.getModelMatrix());
				entry.first->render();
			}
			entry.first->end();
		}
		program->stop();
	}

	void EntityRenderer3D::cleanUP() {
		entities.clear();
	}

} }