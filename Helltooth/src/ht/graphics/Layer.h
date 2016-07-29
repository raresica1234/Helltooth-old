#pragma once

#include "Camera.h"
#include "shaders/ShaderProgram.h"
#include "shaders/ShaderManager.h"
#include "rendering/EntityRenderer3D.h"
#include "rendering/Entity3D.h"
#include "rendering/Renderable.h"
#include "../maths/mat4.h"

#include "../utils/memory/MemoryManager.h"

#include <vector>

namespace ht { namespace graphics {

	class Layer {
	private:
		maths::mat4 projectionMatrix;
		ShaderProgram* shader;
		EntityRenderer3D* renderer;
		Camera* camera;

	public:
		Layer(unsigned int shader, Camera* camera = nullptr);
		~Layer();

		void setMatrix(maths::mat4 &projectionMatrix);

		void submit(Renderable* renderable, Entity3D &entity);
		void submit(Renderable* renderable, std::vector<Entity3D> entityList);
		void render();
		void update();

		void cleanUP();
		void reloadTextures();
	};

} }
