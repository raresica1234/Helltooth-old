#pragma once

#include <vector>
#include <GL/glew.h>

#include "model/RawModel.h"
#include "Renderable.h"
#include "Entity3D.h"
#include "EntityStack.h"

namespace ht { namespace graphics {

	class BatchRenderer {
	private:
		RawModel *model;

		Renderable* renderable;

		EntityStack* entities;
		std::vector<unsigned int> entitiesID;

		
	public:
		BatchRenderer();
		~BatchRenderer();

		//Entity Stack:
		int addEntity(const Entity3D &entity);
		void removeEntity(const unsigned int id);
		Entity3D getEntity(const unsigned int &id);

		//BatchRendering things
		void init();
		void render();


	};


} }
