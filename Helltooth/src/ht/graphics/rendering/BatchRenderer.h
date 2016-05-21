#pragma once

#include <vector>
#include <GL/glew.h>

#include "model/RawModel.h"
#include "Renderable.h"
#include "Entity3D.h"
#include "EntityStack.h"
#include "../../utils/memory/MemoryManager.h"

#include "../shaders/ShaderProgram.h"

namespace ht { namespace graphics {

	class BatchRenderer {
	private:
		const RawModel *object; // This is the original object which contains the raw mesh of vertices

		RawModel *model; // This is the model where all the Entities's objects are going to be stored after calculating positions

		Renderable* renderable; // Renderable object which will just render

		EntityStack* entities; // A stack of entities so i can store entities;
		std::vector<unsigned int> entitiesID; // a list of entities's id which i can get from the entitystack

		const ShaderProgram* program;

		unsigned int entityCount;

		bool changed; //keeps track if the entitystack has been changed
		//if the entitystack is changed the model will be remade
		//if the entitystack hasn't change, the batch renderer will render normally

	public:
		BatchRenderer(const RawModel *object, const ShaderProgram *program);
		~BatchRenderer();

		//Entity Stack:
		void addEntity(const Entity3D &entity);
		void removeEntity(const unsigned int id);
		Entity3D getEntity(const unsigned int &id);

		inline const ShaderProgram* getProgram() { return program; }

		//BatchRendering things
		void init();
		void render() const;

	};


} }
