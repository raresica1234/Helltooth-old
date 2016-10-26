#pragma once
#include <vector>
#include "EntityRenderer3D.h"

#include "../types/DynamicEntity.h"
#include "../types/StaticEntity.h"

#include "../../../utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	class MasterRenderer {
	private:
		EntityRenderer3D* eRenderer;
		std::vector<const StaticEntity*> staticEntities;
		std::vector<const DynamicEntity*> dynamicEntities;

		ShaderProgram* program;
		mat4 projectionMatrix;
		Camera* camera = nullptr;

	public:
		MasterRenderer(unsigned int shaderProgram, Camera* camera);

		~MasterRenderer();

		void submit(const DynamicEntity* dynamicEntity);
		void submit(const StaticEntity* staticEntity);
		void submit(const Renderable* renderable, const Entity3D &entity);
		void submit(const Renderable* renderable, const std::vector<Entity3D>entities);

		void prepare();
		void render();
		void cleanUP();
		void forceCleanUP();
		void setProjectionMatrix(mat4 projectionMatrix);

	};


} }
