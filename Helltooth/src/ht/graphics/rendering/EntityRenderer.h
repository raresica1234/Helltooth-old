#pragma once

#include "Renderer.h"

#include <map>
#include <vector>

#include "../shaders/ShaderProgram.h"

#include "../../utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

#define MAX_ENTITY_COUNT 2500

	class EntityRenderer : public Renderer {
	private:
		std::map<Renderable*, std::vector<Entity3D>> entities;

		ShaderProgram* program;

	public:
		EntityRenderer(ShaderProgram* program);
		~EntityRenderer();

		void pushEntity(Renderable* renderable, const Entity3D &entity) override;

		void pushEntityList(Renderable* renderable, const std::vector<Entity3D>entities);

		void render() override;

	private:
		void cleanUP();

	};



} }
