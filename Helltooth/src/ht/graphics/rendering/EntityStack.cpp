#include "EntityStack.h"

namespace ht { namespace graphics {

	EntityStack::EntityStack() {
		size = 0;
	}

	int EntityStack::addEntity(const Entity3D &entity) {
		entities[size] = entity;
		return size++;
	}

	void EntityStack::removeEntity(const unsigned int id) {
		entities.erase(id);
	}


	Entity3D EntityStack::getEntity(const unsigned int &id) {
		return entities[id];
	}

} }
