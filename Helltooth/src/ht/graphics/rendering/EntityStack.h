#pragma once

#include <map>
#include "Entity3D.h"


namespace ht{ namespace graphics {

	class EntityStack {
	private:
		std::map<unsigned int, Entity3D> entities;

		unsigned int size;

	public:
		EntityStack();
		~EntityStack() {

		}

		int addEntity(const Entity3D &entity);

		void removeEntity(const unsigned int id);

		Entity3D getEntity(const unsigned int &id);
	};


} }
