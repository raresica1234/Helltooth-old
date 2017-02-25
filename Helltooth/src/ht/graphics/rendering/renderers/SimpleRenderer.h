#pragma once
#include <vector>
#include "Renderer.h"

#include "../../Camera.h"

#include "../types/DynamicEntity.h"
#include "../types/StaticEntity.h"

#include "../../shaders/ShaderProgram.h"
#include "../../shaders/ShaderManager.h"

#include "utils/Log.h"
#include "utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	class SimpleRenderer: public Renderer {
	private:
		std::vector<const StaticEntity*> staticEntities;
		std::unordered_map<const Renderable*, std::vector<Entity>> dynamicEntities;

	public:
		SimpleRenderer(unsigned int programID, Camera* camera);
		SimpleRenderer(ShaderProgram* program, Camera* camera);

		~SimpleRenderer();

		void submit(const Entity* entity) override;

		void prepare() override;
		void render() override;
		void cleanUP() override;
		void forceCleanUP() override;
	};


} }
