#include "EntityRenderer3D.h"

namespace ht { namespace graphics {

	EntityRenderer3D::EntityRenderer3D(unsigned int program) {
		this->program = ShaderManager::getProgram(program);
	}

	EntityRenderer3D::~EntityRenderer3D() { }


	void EntityRenderer3D::submit(const Renderable* renderable, const Entity3D &entity) {
		dynamicEntities[renderable].push_back(entity);
	}

	void EntityRenderer3D::submit(const Renderable* renderable, const std::vector<Entity3D>entities) {
		if (dynamicEntities.size() == 0)
			this->dynamicEntities[renderable] = entities;
		else
			for (Entity3D entity : entities)
				submit(renderable, entity);
	}

	void EntityRenderer3D::submit(const DynamicEntity* e) {
		dynamicEntities[e->getRenderable()].push_back((Entity3D)*e);
	}

	void EntityRenderer3D::submit(std::vector<const DynamicEntity*> entities) {
		for (const DynamicEntity* entity : entities) {
			submit(entity);
		}
	}

	//void EntityRenderer3D::submit(const StaticEntity* e) {
	//	staticEntities[e->getRenderable()].push_back((Entity3D)*e);
	//}

	void EntityRenderer3D::render() {
		if (camera)
			program->uniformMat4("viewMatrix", camera->generateViewMatrix());
		for (auto& entry : dynamicEntities) {
			entry.first->prepare(program);
			for (Entity3D entity : entry.second) {
				program->uniformMat4("modelMatrix", entity.getModelMatrix());
				entry.first->render();
			}
			entry.first->end();
		}
		/*for (auto& entry : staticEntities) {
			entry.first->prepare(program);
			for (Entity3D entity : entry.second) {
				program->uniformMat4("modelMatrix", entity.getModelMatrix());
				entry.first->render();
			}
			entry.first->end();
		}*/
	}

	void EntityRenderer3D::cleanUP() {
		dynamicEntities.clear();
	}

} }