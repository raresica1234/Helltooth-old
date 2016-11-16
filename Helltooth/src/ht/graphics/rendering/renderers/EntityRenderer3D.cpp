#include "EntityRenderer3D.h"

namespace ht { namespace graphics {

	EntityRenderer3D::EntityRenderer3D(unsigned int program) {
		this->program = ShaderManager::getProgram(program);
	}

	EntityRenderer3D::~EntityRenderer3D() { }


	void EntityRenderer3D::submit(const Renderable* renderable, const Entity3D &entity) {
		dynamicEntities[renderable].push(entity);
	}

	void EntityRenderer3D::submit(const Renderable* renderable, const List<Entity3D> entities) {
		if (dynamicEntities.size() == 0)
			this->dynamicEntities[renderable] = entities;
		else
			for (int i = 0; i < entities.size; i++)
				submit(renderable, entities[i]);
	}

	void EntityRenderer3D::submit(const DynamicEntity* e) {
		dynamicEntities[e->getRenderable()].push((Entity3D)*e);
	}

	void EntityRenderer3D::submit(List<const DynamicEntity*> entities) {
		for (int i = 0; i < entities.size;i++) {
			submit(entities[i]);
		}
	}

	void EntityRenderer3D::render() {
		if (camera)
			program->uniformMat4("viewMatrix", camera->generateViewMatrix());
		for (int i = 0; i < dynamicEntities.size(); i ++) {
			auto entry = dynamicEntities.find(i);
			for (int i = 0; i < entry.value.size; i ++) {
				Entity3D entity = entry.value[i];
				program->uniformMat4("modelMatrix", entity.getModelMatrix());
				entry.key->render();
			}
			entry.key->end();
		}
	}

	void EntityRenderer3D::cleanUP() {
		dynamicEntities.clear();
	}

} }