#pragma once

#include <vector>

#include "Camera.h"

#include "shaders/ShaderProgram.h"
#include "shaders/ShaderManager.h"

#include "rendering/Entity.h"
#include "rendering/Renderable.h"

#include "rendering/renderers/Renderer.h"
#include "rendering/renderers/ForwardRenderer.h"
#include "rendering/renderers/DeferredRenderer.h"

#include "rendering/types/DynamicEntity.h"
#include "rendering/types/StaticEntity.h"

#include "maths/mat4.h"

#include "utils/memory/MemoryManager.h"
#include "utils/input/Input.h"

namespace ht { namespace graphics {

	class Layer {
	protected:
		maths::mat4 projectionMatrix;
		Renderer* renderer;
		Camera* camera;
		bool deferred = false;

	public:
		Layer(Camera* camera = nullptr, bool deferred = false);

		~Layer();

		virtual void setMatrix(maths::mat4 &projectionMatrix);

		__forceinline void submit(Entity* e) {
			renderer->submit(e);
		}

		virtual void init() {}
		virtual void load(bool &loaded) { loaded = true; }

		virtual void render() {
			renderer->prepare();
			renderer->render();
		}

		__forceinline virtual void update(const utils::Event& e) {
			if (camera)
				camera->update(e);
		}

		__forceinline virtual void tick() {}

		__forceinline void cleanUP() {
			renderer->cleanUP();
		}

		__forceinline void forceCleanUP() {
			renderer->forceCleanUP();
		}

		__forceinline virtual void reloadTextures() {
			renderer->reloadTextures();
		}

		__forceinline virtual void pushLight(Light* light) { renderer->addLight(light); }
		__forceinline virtual void popLight() { renderer->popLight(); }
	protected:
		__forceinline virtual void defaultRenderer() {
			if (deferred)
				renderer = htnew DeferredRenderer(camera);
			else 
				renderer = htnew ForwardRenderer(camera);
		}
	};
} }
