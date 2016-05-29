#pragma once


#include <unordered_map>
#include <vector>

#include "Entity3D.h"
#include "Renderable.h"
#include "../shaders/ShaderProgram.h"
#include "../Camera.h"
#include "../../utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

#define MAX_ENTITY_COUNT 2500

	class EntityRenderer{
	private:
		std::unordered_map<Renderable*, std::vector<Entity3D>> entities;

		ShaderProgram* program;

		const Camera* camera;

	public:
		EntityRenderer(ShaderProgram* program);
		~EntityRenderer();

		void pushEntity(Renderable* renderable, const Entity3D &entity);

		void pushEntityList(Renderable* renderable, const std::vector<Entity3D>entities);

		void render();

		inline void setCamera(const Camera* camera) { this->camera = camera; }

	private:
		void cleanUP();

	};



} }
