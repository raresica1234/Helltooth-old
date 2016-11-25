#pragma once

#include "Camera.h"
#include "shaders/ShaderProgram.h"
#include "shaders/ShaderManager.h"
#include "rendering/renderers/MasterRenderer.h"
#include "rendering/Entity3D.h"
#include "rendering/Renderable.h"
#include "../maths/mat4.h"

#include "rendering/types/DynamicEntity.h"
#include "rendering/types/StaticEntity.h"

#include "../utils/memory/MemoryManager.h"

#include <vector>

namespace ht { namespace graphics {

	class Layer {
	private:
		maths::mat4 projectionMatrix;
		ShaderProgram* shader;
		MasterRenderer* renderer;
		Camera* camera;

	public:
		Layer(unsigned int shader, Camera* camera = nullptr);
		~Layer();

		void setMatrix(maths::mat4 &projectionMatrix);

		void submit(Renderable* renderable, Entity3D &entity);
		void submit(Renderable* renderable, const std::vector<Entity3D> entityList);
		void submit(const StaticEntity *entity);
		void submit(const DynamicEntity *entity);

		void render();
		void update();

		void cleanUP();
		void forceCleanUP();
		void reloadTextures();
	};
} }
