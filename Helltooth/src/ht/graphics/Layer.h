#pragma once

#include <vector>

#include "Camera.h"

#include "shaders/ShaderProgram.h"
#include "shaders/ShaderManager.h"

#include "rendering/Entity.h"
#include "rendering/Renderable.h"

#include "rendering/renderers/Renderer.h"
#include "rendering/renderers/SimpleRenderer.h"

#include "rendering/types/DynamicEntity.h"
#include "rendering/types/StaticEntity.h"

#include "../maths/mat4.h"

#include "../utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	class Layer {
	protected:
		maths::mat4 projectionMatrix;
		ShaderProgram* shader;
		Renderer* renderer;
		Camera* camera;

	public:
		Layer(unsigned int shader, Camera* camera = nullptr);
		Layer(ShaderProgram* shader, Camera* camera = nullptr);

		~Layer();

		virtual void setMatrix(maths::mat4 &projectionMatrix);

		__forceinline void submit(Entity* e) {
			renderer->submit(e);
		}

		virtual void init() {}
		virtual void load(bool &loaded) { loaded = true; }

		virtual void render() {
			renderer->prepare();
			shader->start();
			renderer->render();
			shader->stop();
		}

		virtual void update() {
			if (camera)
				camera->update();
			if (!shader->hasProjection())
				setMatrix(projectionMatrix);
		}

		virtual void tick() {}

		void cleanUP();
		void forceCleanUP();
		virtual void reloadTextures();

	protected:
		virtual void defaultRenderer();
	};
} }
