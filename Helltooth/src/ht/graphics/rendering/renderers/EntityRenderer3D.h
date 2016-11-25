#pragma once

#include "../Entity3D.h"
#include "../Renderable.h"

#include "../../shaders/ShaderProgram.h"
#include "../../shaders/ShaderManager.h"
#include "../../Camera.h"
#include "../../../utils/memory/MemoryManager.h"

#include "../types/DynamicEntity.h"
#include "../types/StaticEntity.h"

#include <unordered_map>
#include <vector>

namespace ht { namespace graphics {

	class EntityRenderer3D {
	private:
		//map of Renderables and entites list
		std::unordered_map<const Renderable*, std::vector<Entity3D>> dynamicEntities;

		//ShaderProgram
		ShaderProgram* program;

		//Camera
		const Camera* camera = nullptr;

	public:
		
		//Constructor takes in ShaderProgram
		EntityRenderer3D(unsigned int program);
		~EntityRenderer3D();

		//Push entity (Renderable, entity)
		void submit(const Renderable* renderable, const Entity3D &entity);

		//Push vector of entities (Renderable, std::vector<Entity3D>)
		void submit(const Renderable* renderable, const std::vector<Entity3D> entities);

		void submit(const DynamicEntity* e);
		//void submit(const StaticEntity* e);

		void submit(std::vector<const DynamicEntity*> entities);

		//Render
		void render();

		//set the camera (Should be done only once)
		inline void setCamera(const Camera* camera) { this->camera = camera; }

		//cleaning up at the end of the frame
		void cleanUP();

	};
} }
